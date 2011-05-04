//
//  GTTableView.m
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 2/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import "GTTableView.h"
#import "GTTableViewItem.h"
#import "GTTableViewCell.h"
#import "GTTableViewHeaderFooterItem_.h"

@interface GTTableViewCell (Link)
@property (nonatomic, assign) GTTableView *tableView;
@end
@implementation GTTableViewCell (Link)
@synthesize tableView;
@end

@interface GTTableViewItem (Link)
@property (nonatomic, assign) GTTableView *tableView;
@end
@implementation GTTableViewItem (Link)
@synthesize tableView;
@end

@interface GTTableViewHeaderFooterItem_ (Link)
@property (nonatomic, assign) GTTableView *tableView;
@end
@implementation GTTableViewHeaderFooterItem_ (Link)
@synthesize tableView;
@end


@interface GTTableView ()
- (void)setup_;
- (void)updateCachedIndexPaths;
- (void)notifyTableViewItemsOfIndexPathChangeForAllItemsAfterIndexPath:(NSIndexPath*)indexPath;
- (void)tearDownItems_;
- (void)tearDownHeaderItems_;
- (void)teardownFooterItems_;
- (void)tearDownCells_;
@end

@implementation GTTableView
#pragma mark - Accesssors -
@synthesize GTTableViewDelegate = GTTableViewDelegate_;
@synthesize defaultCellCanEdit = defaultCellCanEdit_;
@synthesize defaultCellCanMove = defaultCellCanMove_;
@synthesize defaultItemIsVisible = defaultItemIsVisible_;
@synthesize defaultCellHeight = defaultCellHeight_;
@synthesize defaultCellIndentationWidth = defaultCellIndentationWidth_;
@synthesize defaultCellShouldIndentWhileEditing = defaultCellShouldIndentWhileEditing_;
@synthesize defaultCellShouldShowReorderControl = defaultCellShouldShowReorderControl_;
@synthesize defaultCellDeleteConfirmationButtonTitle = defaultCellDeleteConfirmationButtonTitle_;
@synthesize defaultCellStyle = defaultCellStyle_;
@synthesize defaultCellEditingStyle = defaultCellEditingStyle_;
@synthesize defaultCellAccessoryType = defaultCellAccessoryType_;
@synthesize defaultCellEditingAccessoryType = defaultCellEditingAccessoryType_;
@synthesize defaultCellSelectionStyle = defaultCellSelectionStyle_;
@synthesize defaultCellIndentationLevel = defaultCellIndentationLevel_;
@synthesize defaultCellLabel = defaultCellLabel_;
@synthesize defaultCellSubtitleLabel = defaultCellSubtitleLabel_;
@synthesize defaultCellBackgroundColor = defaultCellBackgroundColor_;
@synthesize defaultCellSelectionBackgroundColor = defaultCellSelectionBackgroundColor_;
@synthesize defaultHeaderItemHeight = defaultHeaderItemHeight_;
@synthesize defaultFooterItemHeight = defaultFooterItemHeight_;
@synthesize sectionIndexTitlesForTableView = sectionIndexTitlesForTableView_;

#pragma mark - Object Lifecycle -
- (void)awakeFromNib 
{
    [self setup_];
}

- (id)initWithFrame:(CGRect)frame style:(UITableViewStyle)style 
{
    self = [super init];
    if (self) {
        [self setup_];
    }
    return self;
}

- (void)setup_ 
{
    self.delegate = self;
    self.dataSource = self;
    defaultCellCanEdit_ = YES;
    defaultCellCanMove_ = YES;
    defaultItemIsVisible_ = YES;
    defaultCellHeight_ = 44.0;
    defaultCellIndentationWidth_ = 10.0;
    defaultCellShouldIndentWhileEditing_ = YES;
    defaultCellShouldShowReorderControl_ = NO;
    defaultCellStyle_ = UITableViewCellStyleDefault;
    defaultCellEditingStyle_ = UITableViewCellEditingStyleDelete;
    defaultCellAccessoryType_ = UITableViewCellAccessoryNone;
    defaultCellEditingAccessoryType_ = UITableViewCellAccessoryNone;
    defaultCellSelectionStyle_ = UITableViewCellSelectionStyleBlue;
    defaultCellIndentationLevel_ = 0;
    defaultHeaderItemHeight_ = self.sectionHeaderHeight;
    defaultFooterItemHeight_ = self.sectionFooterHeight;
    items_ = [[NSMutableArray alloc] init];
    cachedIndexPaths_ = [[NSMutableArray alloc] init];
    cachedVisibleIndexPaths_ = [[NSMutableArray alloc] init];
    headerItems_ = [[NSMutableArray alloc] init];
    footerItems_ = [[NSMutableArray alloc] init];
    cells_ = [[NSMutableSet alloc] init];
}

- (void)dealloc 
{
    GTTableViewDelegate_ = nil;
    self.delegate = nil;
    self.dataSource = nil;
    
    [self tearDownHeaderItems_];
    [self teardownFooterItems_];
    [self tearDownItems_];
    [self tearDownCells_];
    
    [defaultCellDeleteConfirmationButtonTitle_ release];
    [defaultCellLabel_ release];
    [defaultCellSubtitleLabel_ release];
    [defaultCellBackgroundColor_ release];
    [defaultCellSelectionBackgroundColor_  release];
    [sectionIndexTitlesForTableView_ release];
    
    [items_ release];
    [headerItems_ release];
    [footerItems_ release];
    [cachedIndexPaths_ release];
    [cachedVisibleIndexPaths_ release];
    [cells_ release];
    [super dealloc];
    
    
}

- (void)tearDownItems_
{
    for (NSArray *sectionItems in items_) 
    {
        for (GTTableViewItem *item in sectionItems)
        {
            [item setTableView:nil];
        }
    }
    
}
- (void)tearDownHeaderItems_
{
    for (GTTableViewHeaderItem *headerItem in [headerItems_ allValues]) 
    {
        [headerItem setTableView:nil];
    }
}

- (void)teardownFooterItems_
{
    for (GTTableViewFooterItem *footerItem in [headerItems_ allValues]) 
    {
        [footerItem setTableView:nil];
    }
}

- (void)tearDownCells_
{
    for (GTTableViewCell *cell in cells_)
    {
        [cell setTableView:nil];
    }
}
#pragma mark - GTTableView Methods -
- (void)updateCachedIndexPaths 
{
    [cachedIndexPaths_ removeAllObjects];
    [cachedVisibleIndexPaths_ removeAllObjects];
    
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    NSInteger section = 0;
    for (NSArray *sectionItems in items_) 
    {
        NSMutableArray *visibleRows = [NSMutableArray array];
        NSMutableArray *rows = [NSMutableArray array];
        NSInteger row = 0;
        NSInteger visibleRow = 0;
        for (GTTableViewItem *item in sectionItems)
        {
            [rows addObject:[NSIndexPath indexPathForRow:row inSection:section]];
            row++;
            if ([item isVisible]) 
            {
                [visibleRows addObject:[NSIndexPath indexPathForRow:row inSection:section]]; 
                visibleRow++;
            }
        }
        [cachedIndexPaths_ addObject:rows];
        [cachedVisibleIndexPaths_ addObject:visibleRows];
        section++;
    }
    
    [pool drain];
}

- (NSInteger)numberOfItemSections
{
    return [cachedVisibleIndexPaths_ count];
    
}
- (NSInteger)numberOfItemsInSection:(NSInteger)section onlyVisible:(BOOL)visible {
    NSInteger numberOfItems = 0;
    if (visible) {
        if (section  < [cachedVisibleIndexPaths_ count]) {
            numberOfItems = [(NSMutableArray*)[cachedVisibleIndexPaths_ objectAtIndex:section] count]
        }
    }
    else {
        if (section < [cachedIndexPaths_ count]) {
            numberOfItems = [(NSMutableArray*)[cachedIndexPaths_ objectAtIndex:section] count]
        }
        
    }
    return numberOfItems;
}
- (NSInteger)numberOfItemsInSection:(NSInteger)section {
    return [self numberOfItemsInSection:section onlyVisible:YES];
}

#pragma mark Header & Footer Items
/**
 For the header items we are using NSNull as place holders. This allows these items to be set at any time.
 Nonetheless, the following methods work just like normal accessors.
 */
- (GTTableViewHeaderItem*)tableViewHeaderItemForSection:(NSInteger)section
{
    GTTableViewHeaderItem * headerItem =  (section < [headerItems_ count]) ? [headerItems_ objectAtIndex:section] : nil;
    return (headerItem != [NSNull null]) ? headerItem : nil;
}

- (GTTableViewFooterItem*)tableViewFooterItemForSection:(NSInteger)section
{
    GTTableViewFooterItem *footerItem = (section < [footerItems_ count]) ? [footerItems_ objectForKey:[NSNumber numberWithInt:section]] : nil;
    return (footerItem != [NSNull null]) ? footerItem : nil;
}

- (void)setTableViewHeaderItem:(GTTableViewHeaderItem *)item forSection:(NSInteger)section
{
    for (int i = [headerItems_ count]; i <= section; i++)
    {
        [headerItems_ addObject:[NSNull null]];
    }
    if (item) {
        [headerItems_ removeObjectAtIndex:section];
        [headerItems_ insertObject:item atIndex:section];
    }
    else {
        [headerItems_ removeObjectAtIndex:section];
        [headerItems_ insertObject:[NSNull null] atIndex:section];
    }
}

- (void)setTableViewFooterItem:(GTTableViewFooterItem *)item forSection:(NSInteger)section
{
    for (int i = [footerItems_ count]; i <= section; i++)
    {
        [footerItems_ addObject:[NSNull null]];
    }
    if (item) {
        [footerItems_ removeObjectAtIndex:section];
        [footerItems_ insertObject:item atIndex:section];
    }
    else {
        [footerItems_ removeObjectAtIndex:section];
        [footerItems_ insertObject:[NSNull null] atIndex:section];
    }
}

#pragma mark - TableView Datasource -
#pragma mark Configuring a TableView

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath 
{
    
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView 
{
    return [self numberOfItemSections];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self numberOfItemsInSection:section];
}

- (NSArray *)sectionIndexTitlesForTableView:(UITableView *)tableView 
{
    if (sectionIndexTitlesForTableView_)
        return sectionIndexTitlesForTableView_;
    return nil;
}

- (NSString*)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    NSString *title = [[self tableViewHeaderItemForSection:section] text];
    if (section < [sectionIndexTitlesForTableView_ count])
        title = (title) ? title : [sectionIndexTitlesForTableView_ objectAtIndex:section];
    return title;
}

- (NSString*)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    NSString *title = [[self tableViewFooterItemForSection:section] text];
    if (section < [sectionIndexTitlesForTableView_ count])
        title = (title) ? title : [sectionIndexTitlesForTableView_ objectAtIndex:section];
    return title;
}

#pragma mark Inserting or Deleting Table Rows
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    switch (editingStyle) {
        case UITableViewCellEditingStyleDelete:
            //**< The item is responsible for making itself invislbe or removing itself or its section. */
            break;
        case UITableViewCellEditingStyleInsert:
            //**< The item is responsible for inserting a new item or section or making something visible. */
            break;
        default:
            break;
    }
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    GTTableViewItem *item = [self itemForRowAtIndexPath:indexPath];
    return [item canEdit];
}

#pragma mark Reordering Table Rows
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    GTTableViewItem *item = [self itemForRowAtIndexPath:indexPath];
    return [item canMove];  
}

- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceVisibleIndexPath toIndexPath:(NSIndexPath *)destinationVisibleIndexPath
{
    if ([sourceVisibleIndexPath compare:destinationVisibleIndexPath] == NSOrderedSame) return;
    GTTableViewItem *movingItem = [self itemForRowAtIndexPath:sourceVisibleIndexPath onlyVisible:YES];
    NSIndexPath *sourceIndexPath = [self indexPathForItem:movingItem onlyVisible:NO];
    NSIndexPath *destinationIndexPath = nil;
    GTTableViewItem *itemForCellAboveNewLocation = [self itemForRowAtIndexPath:[NSIndexPath indexPathForRow:(destinationVisibleIndexPath.row - 1) inSection:destinationVisibleIndexPath.section] onlyVisible:YES];
    GTTableViewItem *itemForCellAtNewLocation = [self itemForRowAtIndexPath:destinationVisibleIndexPath onlyVisible:YES];    
    
    /**
     This method 
     */
    NSMutableSet *possibleIndexPaths = [NSMutableSet set];
    NSInteger realRowAboveNewLocationRow = (itemForCellAboveNewLocation) ? [self indexPathForItem:itemForCellAboveNewLocation onlyVisible:NO].row + 1: 0;
    NSInteger realRowAtNewLocationRow = (itemForCellAtNewLocation) ? [self indexPathForItem:itemForCellAtNewLocation onlyVisible:NO].row : [[items_ objectAtIndex:destinationVisibleIndexPath.section] count];
    for (int i = realRowAboveNewLocationRow; i <= realRowAtNewLocationRow; i++) {
        [possibleIndexPaths addObject:[NSIndexPath indexPathForRow:i inSection:destinationVisibleIndexPath.section]];
    }
    destinationIndexPath = [movingItem moveToIndexPathFromChoiceOfIndexPaths:possibleIndexPaths];
    
    
    
}

#pragma mark - TableView Delegate -


@end
