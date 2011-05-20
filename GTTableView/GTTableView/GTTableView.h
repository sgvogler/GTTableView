//
//  GTTableView.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 2/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

/**
 ** TODO
 * Move tableview to support keyboard
 * If tableview is scrolled dismiss keyboard
 * Pull-to-something top and  Pull-to-something bottom support
 * Refactor the internal indexing system for performance
 */
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>



@class GTTableView;
@protocol GTTableViewDelegate <NSObject>
@optional
- (UINavigationController*) navigationControllerForTableView:(GTTableView*)tableView; /**< This should return the navigation controller that GTTableViewItems can push view controllers to. */
@end

@class GTTableViewItem;
@class GTGradientView_;
@class GTTableViewHeaderItem;
@class GTTableViewFooterItem;
@interface GTTableView : UITableView <UITableViewDelegate,UITableViewDataSource> 
{
@private
    NSMutableArray *items_;
    NSMutableArray *cachedIndexPaths_;
    NSMutableArray *cachedVisibleIndexPaths_;
    NSMutableDictionary *cachedIndexPathsAndItems_;
    NSMutableDictionary *cachedVisibleIndexPathsAndItems_;
    NSMutableDictionary *itemsAndCachedIndexPaths_;
    NSMutableDictionary *itemsAndCachedVisibleIndexPaths_;
    NSMutableArray *headerItems_;
    NSMutableArray *footerItems_;
    NSMutableSet *cells_;
    
   // GTGradientView_ *
    GTGradientView_ *headerGradientTop_;
    GTGradientView_ *headerGradientBottom_;
    GTGradientView_ *footerGradientTop_;
    GTGradientView_ *footerGradientBottom_;
    CGFloat headerPadding_;
    CGFloat footerPadding_;
    CGFloat headerGap_;
    CGFloat footerGap_;
    /** These are used for managing items inbetween beginUpdates and endUpdates. */
    NSMutableArray *updates_;
    NSMutableSet *itemsMadeVisible_;
    NSMutableSet *itemsMadeHidden_;
    NSMutableIndexSet *deletedSections_;
    NSMutableIndexSet *insertedSections_;
}
@property (nonatomic, assign) IBOutlet id<GTTableViewDelegate> GTTableViewDelegate;
@property (nonatomic, readonly, getter=isUpdating) BOOL updating; /**< This responds to beginUpdates and endUpdates */
- (void) viewDidAppear:(BOOL)animated; /**< Monitors for first responders and flashes scroll bars. */
- (void) viewWillDisappear:(BOOL)animated; /**< Stops keyboard monitoring. */

@property (nonatomic, retain) UIColor *backgroundColor; /**< This sets the backgroundView color. */
@property (nonatomic, assign) UITableViewRowAnimation insertAnimation; /**< default is UITableViewRowAnimationRight. */
@property (nonatomic, assign) UITableViewRowAnimation deleteAnimation; /**< default is UITTableViewRowAnimationRight. */


/** The minimum required field is height, all others just allow customizaiton. */
- (void) setBottomGradientHeaderViewWithHeight:(CGFloat)height colors:(NSArray*)colors locations:(NSArray*)locations padding:(CGFloat)padding; 
- (void) setTopGradientFooterViewWithHeight:(CGFloat)height colors:(NSArray*)colors locations:(NSArray*)locations padding:(CGFloat)padding;
- (void) setTopGradientHeaderViewWithHeight:(CGFloat)height colors:(NSArray *)colors locations:(NSArray *)locations;
- (void) setBottomGradientFooterViewWithHeight:(CGFloat)height colors:(NSArray*)colors locations:(NSArray*)locations; 

/**
 These are the default values. They can be overriden individually on each GTTableViewItem. They should all be set prior to adding items to the tableview.
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
@property (nonatomic, retain) IBOutlet UILabel *defaultCellLabel; /**< Attributes are copied from this label if set. */
@property (nonatomic, retain) IBOutlet UILabel *defaultCellSubtitleLabel; /**< Attributes are copied from this label if set. */
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


- (NSIndexPath*) indexPathForItem:(GTTableViewItem*)item; /**< Does not include include items with visible set to NO. Returns nil if item is not visible */
- (NSIndexPath*) indexPathForItem:(GTTableViewItem*)item onlyVisible:(BOOL)visible;

/**
 Call reloadData before or beginChanges and endChanges before and after using these methods unless they are called from either commitDelete or commitInsert.
 */
- (void)beginItemUpdates; /**< This calls beginUpdates on the UITableView and performs some of its own magic. */
- (void)endItemUpdates; /**< This calls endUpdates on the UITableView and performs some of its own magic. */
- (void)insertSectionAtIndex:(NSInteger)index;
- (void)removeSectionAtIndex:(NSInteger)index;
- (void)removeAllSections;

- (void)appendItem:(GTTableViewItem*)item section:(NSInteger)section;
- (void)appendItems:(NSArray*)items section:(NSInteger)section;
- (void)insertItem:(GTTableViewItem*)item atIndexPath:(NSIndexPath*)indexPath;
- (void)insertItem:(GTTableViewItem*)item atIndexPath:(NSIndexPath*)indexPath onlyVisible:(BOOL)visible;

- (void)removeItemAtIndexPath:(NSIndexPath*)indexPath;
- (void)removeItemAtIndexPath:(NSIndexPath*)indexPath onlyVisible:(BOOL)visible;


/* considering removing these
- (void)insertItems:(NSArray*)items inSection:(NSInteger)section atRow:(NSInteger)row animation:(UITableViewRowAnimation)animation; **< Items should be an array of GTTableViewItem instances. *
- (void)insertItems:(NSArray*)items inSection:(NSInteger)section atRow:(NSInteger)row animation:(UITableViewRowAnimation)animation onlyVisible:(BOOL)visible; **< Items should be an array of GTTableViewItem instances. *

- (void)removeItemsInSections:(NSInteger)section atRows:(NSIndexSet*)rows animation:(UITableViewRowAnimation)animation;
- (void)removeItemsInSections:(NSInteger)section atRows:(NSIndexSet*)rows animation:(UITableViewRowAnimation)animation onlyVisible:(BOOL)visible;
*/
- (GTTableViewHeaderItem*)tableViewHeaderItemForSection:(NSInteger)section;
- (void)setTableViewHeaderItem:(GTTableViewHeaderItem*)item forSection:(NSInteger)section;

- (GTTableViewFooterItem*)tableViewFooterItemForSection:(NSInteger)section;
- (void)setTableViewFooterItem:(GTTableViewFooterItem*)item forSection:(NSInteger)section;
@end
