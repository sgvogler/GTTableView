//
//  GTTableViewItem.m
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 3/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import "GTTableViewItem.h"
#import "GTTableViewCell.h"
#import "GTTableView.h"

@interface GTTableViewItem ()

- (BOOL)hasKeyBeenSet_:(NSString*)key;
- (void)resetKey_:(NSString*)key;

- (BOOL)boolForKey_:(NSString*)key;
- (void)setBool:(BOOL)aBool forKey_:(NSString*)key;

- (NSInteger)intForKey_:(NSString*)key;
- (void)setInt:(NSInteger)anInt ForKey_:(NSString*)key;

- (double)doubleForKey_:(NSString*)key;
- (void)setDouble:(double)aDouble forKey_:(NSString*)key;

- (id)objectForKey_:(NSString*)key;
- (void)setObject:(id)anObject ForKey_:(NSString*)key;

@end

@implementation GTTableViewItem
#pragma mark - Accessors -
- (GTTableViewCell *)cell {
    return (GTTableViewCell*)[tableView cellForRowAtIndexPath:[tableView indexPathForItem:self]];
}

#pragma mark selected
 NSString  * const kSelectedKey = @"kSelectedKey";
- (BOOL)isSelected {
    if ([self hasKeyBeenSet_:kSelectedKey])
        return [self boolForKey_:kSelectedKey];
    return NO;
}
- (void)setSelected:(BOOL)selected {
    [self setSelected:selected animated:NO];
}
- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [self setBool:selected forKey_:kSelectedKey];
    if (self.cell)
        [self.cell setSelected:selected animated:animated];
}
- (void)resetSelected {
    [self resetSelectedAnimated:NO];
}
- (void)resetSelectedAnimated:(BOOL)animated {
    [self resetKey_:kSelectedKey];
    if (self.cell)
        [self.cell setSelected:[self isSelected] animated:animated];
}

#pragma mark canEdit
NSString * const kCanEditKey = @"kCanEditKey";
- (BOOL)canEdit {
    if ([self hasKeyBeenSet_:kCanEditKey])
        return [self boolForKey_:kCanEditKey];
    return [tableView defaultCellCanEdit];
}
- (void)setCanEdit:(BOOL)canEdit {
    [self setBool:canEdit forKey_:kCanEditKey];
}
- (void)resetCanEdit {
    [self resetKey_:kCanEditKey];
}

#pragma mark canMove
NSString * const kCanMoveKey = @"kCanMoveKey";
- (BOOL)canMove {
    if ([self hasKeyBeenSet_:kCanMoveKey])
        return [self boolForKey_:kCanMoveKey];
    return [tableView defaultCellCanMove];
}
- (void)setCanMove:(BOOL)canMove {
    [self setBool:canMove forKey_:kCanMoveKey];
}
- (void)resetCanMove {
    [self resetKey_:kCanMoveKey];
}

#pragma mark visible
NSString * const kVisibleKey = @"kVisibleKey";
- (BOOL)isVisible {
    if (visibleSet_)
        return visible_;
    return [tableView defaultItemIsVisible];
}
- (void)setVisible:(BOOL)visible {
    [self setVisible:visible animation:UITableViewRowAnimationNone];
}
- (void)setVisible:(BOOL)willBeVisible animation:(UITableViewRowAnimation)animation {
    BOOL wasVisible =  [self isVisible];
    /**
     We have to update the table view rows if the cells are visible. The order of setting the variable and getting the index path counts. 
     */
    if (wasVisible && !willBeVisible) {
        NSIndexPath *indexPath = [tableView indexPathForItem:self];
        visible_ = YES;
        visibleSet_ = YES;
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:animation];
    }
    else if (!wasVisible && willBeVisible) {
        visible_ = NO;
        visibleSet_ = YES;
        NSIndexPath *indexPath = [tableView indexPathForItem:self];
        [tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:animation];
    }
    
}
- (void) resetVisible {
    [self resetVisibleAnimation:UITableViewRowAnimationNone];
}
- (void)resetVisibleAnimation:(UITableViewRowAnimation)animation {
    BOOL wasVisible = [self isVisible];
    BOOL willBeVisible = [tableView defaultItemIsVisible];
    if (wasVisible && !willBeVisible) {
        NSIndexPath *indexPath = [tableView indexPathForItem:self];
        visibleSet_ = NO;
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:animation];
    }
    else if (!wasVisible && willBeVisible) {
        visibleSet_ = NO;
        NSIndexPath *indexPath = [tableView indexPathForItem:self];
        [tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:animation];
    }
}


#pragma mark height
NSString * const kHeightKey = @"kHeightKey";
- (CGFloat)height {
    if ([self hasKeyBeenSet_:kHeightKey])
        return [self doubleForKey_:kHeightKey];
    return [tableView defaultCellHeight];
}
- (void)setHeight:(CGFloat)height {
    [self setDouble:height forKey_:kHeightKey];
}
- (void)resetHeight {
    [self resetKey_:kHeightKey];
}

#pragma mark indentationWidth
NSString * const kIndentationWidthKey = @"kIndentationWidthKey";
- (CGFloat)indentationWidth {
    if ([self hasKeyBeenSet_:kIndentationWidthKey])
        return [self doubleForKey_:kIndentationWidthKey];
    return [tableView defaultCellIndentationWidth];
}
- (void)setIndentationWidth:(CGFloat)indentationWidth {
    [self setDouble:indentationWidth forKey_:kIndentationWidthKey];
    if (self.cell)
        [self.cell setIndentationWidth:indentationWidth];
}
- (void)resetIndentationWidth {
    [self resetKey_:kIndentationWidthKey];
    if (self.cell)
        [self.cell setIndentationWidth:[self indentationWidth]];
}

#pragma mark shouldIndentWhileEditing
NSString * const kShouldIndentWhileEditingKey = @"kShouldIndentWhileEditingKey";
- (BOOL)shouldIndentWhileEditing {
    if ([self hasKeyBeenSet_:kShouldIndentWhileEditingKey])
        return [self boolForKey_:kShouldIndentWhileEditingKey];
    return [tableView defaultCellShouldIndentWhileEditing];
}
- (void)setShouldIndentWhileEditing:(BOOL)shouldIndentWhileEditing {
    [self setBool:shouldIndentWhileEditing forKey_:kShouldIndentWhileEditingKey];
    if (self.cell)
        [self.cell setShouldIndentWhileEditing:shouldIndentWhileEditing];
}
- (void)resetShouldIndentWhileEditing {
    [self resetKey_:kShouldIndentWhileEditingKey];
    if (self.cell)
        [self.cell setShouldIndentWhileEditing:[self shouldIndentWhileEditing]];
}

#pragma mark shouldShowReoderControl
NSString * const kShouldShowReoderControlKey = @"kShouldShowReoderControlKey";
- (BOOL)shouldShowReorderControl {
    if ([self hasKeyBeenSet_:kShouldShowReoderControlKey])
        return [self boolForKey_:kShouldShowReoderControlKey];
    return [tableView defaultCellShouldShowReorderControl];
}
- (void)setShouldShowReorderControl:(BOOL)shouldShowReorderControl {
    [self setBool:shouldShowReorderControl forKey_:kShouldShowReoderControlKey];
    if (self.cell)
        [self.cell setShowsReorderControl:shouldShowReorderControl];
}
- (void)resetShouldShowReorderControl {
    [self resetKey_:kShouldShowReoderControlKey];
    if (self.cell)
        [self.cell setShowsReorderControl:[self shouldShowReorderControl]];
}

#pragma mark deleteConfirmationTitle
NSString * const kDeleteConfirmationTitleKey = @"kDeleteConfirmationTitleKey";
- (NSString *)deleteConfirmationTitle {
    if ([self hasKeyBeenSet_:kDeleteConfirmationTitleKey])
        return [self objectForKey_:kDeleteConfirmationTitleKey];
    return nil;
}
- (void)setDeleteConfirmationTitle:(NSString *)deleteConfirmationTitle {
    [self setObject:deleteConfirmationTitle ForKey_:kDeleteConfirmationTitleKey];
}
- (void)resetDeleteConfirmationTitle {
    [self resetKey_:kDeleteConfirmationTitleKey];
}

#pragma mark style
NSString * const kStyleKey = @"kStyleKey";
- (UITableViewCellStyle)style {
    if ([self hasKeyBeenSet_:kStyleKey])
        return (UITableViewCellStyle*)[self intForKey_:kStyleKey];
    return [tableView defaultCellStyle];
}
- (void)setStyle:(UITableViewCellStyle)style {
    [self setInt:(NSInteger)style ForKey_:kStyleKey];
}
- (void)resetStyle {
    [self resetKey_:kStyleKey];
}

#pragma mark editingStyle
NSString * const kEditingStyle = @"kEditingStyle";
- (UITableViewCellEditingStyle)editingStyle {
    if ([self hasKeyBeenSet_:kEditingStyle])
        return (UITableViewCellEditingStyle)[self intForKey_:kEditingStyle];
    return [tableView defaultCellEditingStyle];
}
- (void)setEditingStyle:(UITableViewCellEditingStyle)editingStyle {
    [self setInt:(NSInteger)editingStyle ForKey_:kEditingStyle];
}
- (void)resetEditingStyle {
    [self resetKey_:kEditingStyle];
}

#pragma mark accessoryType
NSString * const kAccessoryType = @"kAccessoryType";
- (UITableViewCellAccessoryType)accessoryType {
    
}


#pragma mark - Object Lifecylce -
- (id)init
{
    NSLog(@"Use custom initializer initWithDefaultsFromTableView:");
    abort();
}

- (id) initWithDefaultsFromTableView:(GTTableView*)aTableView
{
    self = [super init];
    if (self) {
        [self setupFromTableView_:aTableView];
    }
    return self;
}

- (id)tableViewItemWithDefaultsFromTableView:(GTTableView *)aTableView
{
    return [[[GTTableViewItem alloc] initWithDefaultsFromTableView:aTableView] autorelease];
}

- (void) setupFromTableView_:(GTTableView*)aTableView
{
    NSParameterAssert(aTableView);
    properties_ = [[NSMutableDictionary alloc] init];
}

- (void)dealloc {
    [properties_ release];
    [super dealloc];
}
#pragma mark - Properties Accessors -
- (BOOL)hasKeyBeenSet_:(NSString*)key { return ([[properties_ allKeys] containsObject:key]); }
- (void)resetKey_:(NSString*)key { [properties_ removeObjectForKey:key]; }

- (BOOL)boolForKey_:(NSString*)key { return [[properties_ objectForKey:key] boolValue]; }
- (void)setBool:(BOOL)aBool forKey_:(NSString*)key { [properties_ setObject:[NSNumber numberWithBool:aBool] forKey:key]; }

- (NSInteger)intForKey_:(NSString*)key { return [[properties_ objectForKey:key] intValue]; }
- (void)setInt:(NSInteger)anInt ForKey_:(NSString*)key { [properties_ setObject:[NSNumber numberWithInt:anInt] forKey:key]; }

- (double)doubleForKey_:(NSString*)key { return [[properties_ objectForKey:key] doubleValue]; }
- (void)setDouble:(double)aDouble forKey_:(NSString*)key {
    [properties_ setObject:[NSNumber numberWithDouble:aDouble] forKey:key];
}

- (id)objectForKey_:(NSString*)key { return [properties_ objectForKey:key]; }
- (void)setObject:(id)anObject ForKey_:(NSString*)key { [properties_ setObject:anObject forKey:key]; }
@end
