//
//  GTTableView.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 2/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GTTableView+GTTableViewItem.h"
#import "GTTableView+GTTableViewCell.h"

@class GTTableView;
@protocol GTTableViewDelegate <NSObject>
@optional
- (UINavigationController*) navigationControllerForTableView:(GTTableView*)tableView; /**< This should return the navigation controller that GTTableViewItems can push view controllers to. */
@end

@class GTTableViewItem;
@class GTTableViewHeaderItem;
@class GTTableViewFooterItem;
@interface GTTableView : UITableView <UITableViewDelegate,UITableViewDataSource> 
{
@private
    NSMutableArray *items_;
    NSMutableArray *cachedIndexPaths_;
    NSMutableArray *cachedVisibleIndexPaths_;
    NSMutableArray *headerItems_;
    NSMutableArray *footerItems_;
    NSMutableSet *cells_;
}
@property (nonatomic, assign) id<GTTableViewDelegate> GTTableViewDelegate;

- (void) viewDidAppear:(BOOL)animated; /**< Monitors for first responders and flashes scroll bars if animated. */
- (void) viewWillDisappear:(BOOL)animated; /**< Stops keyboard monitoring. */

@property (nonatomic, retain) UIColor *backgroundColor; /**< This sets the backgroundView color. */
/**
 These are the default values. They can be overriden individually on each GTTableViewItem.
 */
// Datasource
@property (nonatomic, assign) BOOL defaultCellCanEdit; /**< Default is YES. */
@property (nonatomic, assign) BOOL defaultCellCanMove; /**< Default is YES. */
@property (nonatomic, assign) BOOL defaultItemIsVisible; /**< Default is YES. */
// Delegate
@property (nonatomic, assign) CGFloat defaultCellHeight;  /**< Default is 44.0 */
@property (nonatomic, assign) CGFloat defaultCellIndentationWidth; /**< Default is 10.0. */
@property (nonatomic, assign) BOOL defaultCellShouldIndentWhileEditing; /**< Default is YES. */
@property (nonatomic, assign) BOOL defaultCellShouldShowReorderControl; /**< Default is NO. */
@property (nonatomic, copy) NSString* defaultCellDeleteConfirmationButtonTitle; /**< Default is localized 'Delete'. */
// Cells
@property (nonatomic, assign) UITableViewCellStyle defaultCellStyle; /**< Default is the same value as style on the instance of GTTableView */
@property (nonatomic, assign) UITableViewCellEditingStyle defaultCellEditingStyle; /**< Default is UITableViewCellEditingStyleDelete. */
@property (nonatomic, assign) UITableViewCellAccessoryType defaultCellAccessoryType; /**< Default is  UITableViewCellAccessoryNone. */
@property (nonatomic, assign) UITableViewCellAccessoryType defaultCellEditingAccessoryType; /**<  Default is  UITableViewCellAccessoryNone. */
@property (nonatomic, assign) UITableViewCellSelectionStyle defaultCellSelectionStyle; /**< Default is UITableViewCellSelectionStyleBlue. */
@property (nonatomic, assign) NSInteger defaultCellIndentationLevel; /**< Default is 0. */
@property (nonatomic, retain) UILabel *defaultCellLabel; /**< Attributes are copied from this label if set. */
@property (nonatomic, retain) UILabel *defaultCellSubtitleLabel; /**< Attributes are copied from this label if set. */
@property (nonatomic, retain) UIColor *defaultCellBackgroundColor; /**< This sets the background colour of a GTTableViewCell. */
@property (nonatomic, retain) UIColor *defaultCellSelectionBackgroundColor; /**< This sets the content view background colour . */
/**
 These are the defaults for table view headers and footers. They can be overriden with GTTableViewHeaderItems and GTTableViewFooterItems.
 */
@property (nonatomic, assign) CGFloat defaultHeaderItemHeight;
@property (nonatomic, assign) CGFloat defaultFooterItemHeight;
@property (nonatomic, retain) NSArray *sectionIndexTitlesForTableView;

/**
 These methods are used for controlling the data displayed in the table view.
 */
- (NSInteger)numberOfItemSections;

- (NSInteger)numberOfItemsInSection:(NSInteger)section; /**< Does not include include items with visible set to NO. */
- (NSInteger)numberOfItemsInSection:(NSInteger)section onlyVisible:(BOOL)visible;

- (NSArray*)items; /**< Collection of all GTTableViewItem instances in all sections. Include items with visible set to NO. */
- (NSArray*)itemsOnlyVisible:(BOOL)visible;

- (NSArray*)itemsInSection:(NSInteger)section; /**< Collection of GTTableViewItem instances in section. Does not include items with visible set to NO. */
- (NSArray*)itemsInSection:(NSInteger)section onlyVisible:(BOOL)visible;

- (GTTableViewItem*)itemForRowAtIndexPath:(NSIndexPath*)indexPath; /**< Does not include include items with visible set to NO. */
- (GTTableViewItem*)itemForRowAtIndexPath:(NSIndexPath*)indexPath onlyVisible:(BOOL)visible;


- (NSIndexPath*) indexPathForItem:(GTTableViewItem*)item; /**< Does not include include items with visible set to NO. */
- (NSIndexPath*) indexPathForItem:(GTTableViewItem*)item onlyVisible:(BOOL)visible;
/**
 Call tableView beginUpdates and endUpdates before and after these methods.
 */
- (void)insertSectionAtIndex:(NSInteger)index animation:(UITableViewRowAnimation)animation;
- (void)removeSectionAtIndex:(NSInteger)section animation:(UITableViewRowAnimation)animation;

- (void)insertItem:(GTTableViewItem*) inSection:(NSInteger)section atRow:(NSInteger)row animation:(UITableViewRowAnimation)animation;
- (void)insertItem:(GTTableViewItem*) inSection:(NSInteger)section atRow:(NSInteger)row animation:(UITableViewRowAnimation)animation onlyVisible:(BOOL)visible;
- (void)removeItemInSection:(NSInteger)section atRow:(NSInteger)row animation:(UITableViewRowAnimation)animation;
- (void)removeItemInSection:(NSInteger)section atRow:(NSInteger)row animation:(UITableViewRowAnimation)animation onlyVisible:(BOOL)visible;

- (void)insertItems:(NSArray*)items inSection:(NSInteger)section atRow:(NSInteger)row animation:(UITableViewRowAnimation)animation; /**< Items should be an array of GTTableViewItem instances. */
- (void)insertItems:(NSArray*)items inSection:(NSInteger)section atRow:(NSInteger)row animation:(UITableViewRowAnimation)animation onlyVisible:(BOOL)visible; /**< Items should be an array of GTTableViewItem instances. */

- (void)removeItemsInSections:(NSInteger)section atRows:(NSIndexSet*)rows animation:(UITableViewRowAnimation)animation;
- (void)removeItemsInSections:(NSInteger)section atRows:(NSIndexSet*)rows animation:(UITableViewRowAnimation)animation onlyVisible:(BOOL)visible;

- (GTTableViewHeaderItem*)tableViewHeaderItemForSection:(NSInteger)section;
- (void)setTableViewHeaderItem:(GTTableViewHeaderItem*)item forSection:(NSInteger)section;

- (GTTableViewFooterItem*)tableViewFooterItemForSection:(NSInteger)section;
- (void)setTableViewFooterItem:(GTTableViewFooterItem*)item forSection:(NSInteger)section;
@end
