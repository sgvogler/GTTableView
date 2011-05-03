//
//  GTTableView.m
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 2/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import "GTTableView.h"

@interface GTTableView ()
- (void)setup_;
- (void)updateCachedIndexPaths;
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
    headerItems_ = [[NSMutableArray alloc] init];
    footerItems_ = [[NSMutableArray alloc] init];
    cells_ = [[NSMutableArray alloc] init];
}

- (void)dealloc 
{
    GTTableViewDelegate_ = nil;
    self.delegate = nil;
    self.dataSource = nil;
    [super dealloc];
    
    [defaultCellDeleteConfirmationButtonTitle_ release];
    [defaultCellLabel_ release];
    [defaultCellSubtitleLabel_ release];
    [defaultCellBackgroundColor_ release];
    [defaultCellSelectionBackgroundColor_  release];
    [sectionIndexTitlesForTableView_ release];
    [self tearDownItems_];
    [self tearDownCells_];
    [items_ release];
    [headerItems_ release];
    [footerItems_ release];
    [cells_ release];
    
}

- (void)tearDownItems_
{
    
}

- (void)tearDownHeaderItems_
{
    
}

- (void)teardownFooterItems_
{
    
}

- (void)tearDownCells_
{
    
}
#pragma mark - TableView Datasource -

#pragma mark - TableView Delegate -


@end
