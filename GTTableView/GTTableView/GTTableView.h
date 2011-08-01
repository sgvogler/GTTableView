//
//  GTTableView.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 2/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

/**
 * Move tableview to support keyboard
 * If tableview is scrolled dismiss keyboard
 * Pull-to-something top and  Pull-to-something bottom support
 * Refactor the internal indexing system for performance
 */
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

typedef enum {
    GTTableViewAutoFocusScrollPositionProportional, /// This proportinally moves the first responder an amount proportinal to it's position in the table view.
    GTTableViewAutoFocusScrollPositionBottom, /// This is the default behaviour that UITableViewController implements.
    GTTableViewAutoFocusScrollPositionTop, // This forces the first responder to the top even if the content offset is out of bounds
    GTTableViewAutoFocusScrollPositionNone, // This doesn't change the content offset but changes the frame so that the entire frame is accessible.
} GTTableViewAutoFocusScrollPosition;

@class GTTableView;
/**
 This protocol allows [GTTableViewItem](GTTableViewItem)s to use their navigationController property. It does not need to be implemented unless a [GTTableViewItem](GTTableViewItem) need to access this property. [GTTableViewController](GTTableViewController) implements this protocol.
 */
@protocol GTTableViewDelegate <NSObject>
@optional
/** This should return the navigation controller that [GTTableViewItem](GTTableViewItem)s can push view controllers to. */
- (UINavigationController*) navigationControllerForTableView:(GTTableView*)tableView; 
@end

@class GTTableViewItem;
@class GTGradientView_;
@class GTTableViewHeaderItem;
@class GTTableViewFooterItem;
/**
 GTTableView is a subclass of UITableView that makes customisation of cells very easy.
 It uses the model-view-controller design pattern on a per cell basis. Typically a subclass of GTTableViewItem and GTTableViewCell will be used for cell.
 
 The GTTableViewItem subclass should override [reuseIdentifier](GTTableViewItem reuseIdentifier) and return a custom NSString identifier.
 If a nib file containing one GTTableViewCell or GTTableViewCell subclass is named the same as the returned [reuseIdentifier](GTTableViewItem reuseIdentifier) it will be loaded. If this method is use be sure to set the reuse identifier for the cell in the nib to the same as the reuse identifier returned by [reuseIdentifier](GTTableViewItem reuseIdentifier).
 
 A GTTableViewItem instance has access to a cell if a cell is current visible on screen through its [cell](GTTableViewItem cell) property. Conversely a GTTableViewCell has access to it's backing data instance through its [item](GTTableViewCell item) property.
 
 The GTTableView also supports hidden items. Each item has a visible property. One issue with having hidden items is that when a new item is inserted where should it be inserted in relation to hidden items. To solve this some methods have a `onlyVisible:` flag that when set to `NO` will allow direct access to all items, including hidden ones.
 
In addition subclasses of GTTableViewItem can override [selectNewIndexPathFromIndexPaths:](GTTableViewItem selectNewIndexPathFromIndexPaths:] and return the appropriate position they should be inserted.
 
 GTTableView allows quick default customisation through all the properties beginning with the prefix default.
 
 */
@interface GTTableView : UITableView <UITableViewDelegate,UITableViewDataSource,UIScrollViewDelegate> 
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
    
    GTGradientView_ *headerGradientTop_;
    GTGradientView_ *headerGradientBottom_;
    GTGradientView_ *footerGradientTop_;
    GTGradientView_ *footerGradientBottom_;
    CGFloat headerPadding_;
    CGFloat footerPadding_;
    CGFloat headerGap_;
    CGFloat footerGap_;

    
    NSMutableArray *updates_;
    NSMutableSet *itemsMadeVisible_;
    NSMutableSet *itemsMadeHidden_;
    NSMutableIndexSet *deletedSections_;
    NSMutableIndexSet *insertedSections_;
    
    
    // keyboard handling
    UITapGestureRecognizer *tapGestureRecognizer_;
}

///---------------------------------
/// @name Keyboard Monitoring 
///---------------------------------

/// Typically this is a GTTableViewController.
@property (nonatomic, assign) IBOutlet id<GTTableViewDelegate> GTTableViewDelegate; 

/// Returns `YES` if the GTTableView is beteween beginItemUpdates and endItemUpdates.
@property (nonatomic, readonly, getter=isUpdating) BOOL updating; 

/// Turn on if the GTTableView should monitor for the keyboard. Default value is `NO`.
@property (nonatomic, assign, getter = isMonitoringKeyboard) BOOL monitoringKeyboard; 

@property (nonatomic, assign) GTTableViewAutoFocusScrollPosition autoFocusScrollPosition;

/// If monitoringKeyboard is enabled this will dismiss the keyboard for all touches in the GTTableView that are not on a touch handler.
@property (nonatomic, assign) BOOL dismissKeyboardOnTouchOutside; 

/// If monitoringKeyboard is enabled this will dismiss the keyboard when the GTTableView is scrolled.
@property (nonatomic, assign) BOOL dismissKeyboardOnScroll; 

/**
 Forces the GTTableView to focus on a subview using the specified scrollPosition.
 @param view A subview of the GTTableView.
 @param scrollPosition the specified position the view should be focused to.
 */
- (void)autoFocusOnView:(UIView*)view WithAutoScrollPosition:(GTTableViewAutoFocusScrollPosition)scrollPosition; 

///---------------------------------
/// @name View Transitions
///---------------------------------

/**
 This method sets up the keyboard monitoring and flashes teh scroll view indicators.
 If items are selected it deselects them.
 @param animated If `YES` this will animate the deselection of any rows that were previously selected.
 @warning If GTTableView is reloaded prior to this method its selection will be cleared. Therefore please be sure to reselect a cell after the reload, if you wish to have the deselect animation occur or perhaps use refreshVisibleCells.
 */
- (void) viewDidAppear:(BOOL)animated; 
- (void) viewWillDisappear:(BOOL)animated; /// Stops keyboard monitoring. These methods must be called if keyboard monitoring is used. Failure to use these could result in a crash.

///---------------------------------
/// @name TableView Visible Properties
///---------------------------------

/// The backgroundColor property on UITTableView. Default is the `super` implementation.
@property (nonatomic, retain) UIColor *backgroundColor; 


/**
 Easy method to setup a gradient attached to the bottom of a the table view's footer.
 @param height The height of the gradient.
 @param colors _Optional_ array parameter for specifing the colors of a gradient.
 @param locations _Optional_ array parameter for specifing the locations of a gradient.
 Must have the same number of elements as the colors array.
 @param padding Any padding the gradient should have from the bottom of the table views footer.
 */
- (void) setBottomGradientHeaderViewWithHeight:(CGFloat)height colors:(NSArray*)colors locations:(NSArray*)locations padding:(CGFloat)padding; 

/**
 Easy method to setup a gradient attached to the bottom of a table view's container.
 @param height The height of the gradient.
 @param colors _Optional_ array parameter for specifing the colors of a gradient.
 @param locations _Optional_ array parameter for specifing the locations of a gradient.
 Must have the same number of elements as the colors array.
 @param padding Any padding the gradient should have from the bottom of the table views footer.
 */
- (void) setTopGradientFooterViewWithHeight:(CGFloat)height colors:(NSArray*)colors locations:(NSArray*)locations padding:(CGFloat)padding;

/**
 Easy method to setup a gradient attached to the top of the table view's container.
 @param height The height of the gradient.
 @param colors _Optional_ array parameter for specifing the colors of a gradient.
 @param locations _Optional_ array parameter for specifing the locations of a gradient.
 Must have the same number of elements as the colors array.
 @param padding Any padding the gradient should have from the bottom of the table views header.
 */
- (void) setTopGradientHeaderViewWithHeight:(CGFloat)height colors:(NSArray *)colors locations:(NSArray *)locations;

/**
 Easy method to setup a gradient attached to the top of the table view's header.
 @param height The height of the gradient.
 @param colors _Optional_ array parameter for specifing the colors of a gradient.
 @param locations _Optional_ array parameter for specifing the locations of a gradient.
 Must have the same number of elements as the colors array.
 @param padding Any padding the gradient should have from the bottom of the table views header.
 */
- (void) setBottomGradientFooterViewWithHeight:(CGFloat)height colors:(NSArray*)colors locations:(NSArray*)locations; 

/**
 When set to `NO` the bottom gradients will have a minimum padding of the height of the tableview. This results in the bottom gradients not being visible if the tableview cells do not fill the tableview frame and the tableview has not been scrolled.
 When set to `YES` the bottom gradients will be visible if the tableview cells do not fill the tableview frame and the tableview has not been scrolled.
 
 Default value is `NO`.
 */
@property (nonatomic, assign) BOOL bottomGradientShouldStartOnLastCell; 

///---------------------------------
/// @name TableView Default Item/Cell Properties
///---------------------------------

// Datasource
/**
 Whether any item's cell be edited by default.
 To customise on a per item basis set [canEdit]([GTTableViewItem canEdit]) on GTTableViewItem.
 
 Default value is `YES`.
 */
@property (nonatomic, assign) BOOL defaultCellCanEdit; 

/**
 Whether any any item's cell can move by default.
 To customise on a per item basis set [canMove:][cm] on GTTableViewItem.
 
 
 Default value is `NO`.
 
 [cm]: [GTTableViewItem canMove] 
 */
@property (nonatomic, assign) BOOL defaultCellCanMove; 
@property (nonatomic, assign) BOOL defaultItemIsVisible; 

// Delegate

/**
 The default height of any item's cell.
 To customise on a per item basis set [height]([GTTableViewItem height]) on GTTableViewItem.
 
 Default value is `44.0`.
 */
@property (nonatomic, assign) CGFloat defaultCellHeight;  

/**
 The default indentation width of any item's cell.
 To customise on a per item basis set [indentationWidth]([GTTableViewItem indentationWidth]) on GTTableViewItem.

 Default value is `10.0`.
 */
@property (nonatomic, assign) CGFloat defaultCellIndentationWidth; 

/**
 Whether any item's cell should indendt while editing by default.
 To customise on a per item basis set [shouldIdentWhileEditing]([GTTableViewItem shouldIdentWhileEditing]) on GTTableViewItem.

 Default value is `YES`.
 */
@property (nonatomic, assign) BOOL defaultCellShouldIndentWhileEditing; 

/**
 Whether any item's cell should show reorder control by default. Will only show if [canMove]([GTTableViewitem canMove])'s value is `YES` also.
 To customise on a per item basis set [shouldShowReoderControl]([GTTableViewItem shouldShowReoderControl]) on GTTableViewItem.

 
 Default value is `NO`.
 */
@property (nonatomic, assign) BOOL defaultCellShouldShowReorderControl; 


/**
 The default delete confirmation button title for any item's cell.
 To customise on a per item basis set [deleteConfirmationTitle]([GTTableViewItem deleteConfirmationTitle]) on GTTableViewItem.
 
 Default value is nil which results in a localized _Delete_ NSString.
 */
@property (nonatomic, copy) NSString* defaultCellDeleteConfirmationButtonTitle; 

// Cells

/**
 The default UITableViewCellStyle for any item's cell.  To customise on a per item basis set [style]([GTTableViewItem style]) on GTTableViewItem.

 Default value is the same as the UITableViewCellStyle GTTableView was initialized with. 
 @warning Can't be different to the UITableViewCellStyle that GTTableView was initialized with.
 */
@property (nonatomic, assign) UITableViewCellStyle defaultCellStyle; 

/**
 Default UITableViewCellEditingStyle for any item's cell.
 To customise on a per item basis set [editingStyle]([GTTableViewItem editingStyle]) on GTTableViewItem.
 
 Default value is `UITableViewCellEditingStyleDelete`.
 */
@property (nonatomic, assign) UITableViewCellEditingStyle defaultCellEditingStyle;

/**
 Default UITableViewCellAccessoryType type for any item's cell.
 To customise on a per item basis set [accessoryType]([GTTableViewItem accessoryType]) on GTTableViewItem.
 
 Default value is `UITableViewCellAccessoryNone`.

 */
@property (nonatomic, assign) UITableViewCellAccessoryType defaultCellAccessoryType; 

/**
 Default UITableViewCellAccessoryType for any item's cell when the cell is in editng moding.
 To customise on a per item basis set [editingAccessoryType]([GTTableViewItem editingAccessoryType]) on GTTableViewItem.

 Default value is `UITableViewCellAccessoryNone`.
 */
@property (nonatomic, assign) UITableViewCellAccessoryType defaultCellEditingAccessoryType; 

/**
 Default UITableViewCellSelectionStyle for any item's cell.
 To customise on a per item basis set [selectionStyle]([GTTableViewItem selectionStyle]) on GTTableViewItem.

 Default value is `UITableViewCellSelectionStyleBlue`.
 */
@property (nonatomic, assign) UITableViewCellSelectionStyle defaultCellSelectionStyle;

/**
 Default indentation level for any item's cell.
 To customise on a per item basis set [indentationLevel]([GTTableViewItem indentationLevel]) on GTTableViewItem.

 Default value is `0`.
 @warning Call beginUpdates and endUpdates to force the tableview to refresh and reread these values.
 */
@property (nonatomic, assign) NSInteger defaultCellIndentationLevel; 

/**
 The default label for any item's cell. 
 If a regular GTTableView cell is used this label's attributes are copied to the cell.
 To customise on a per item basis set [labelStyle]([GTTableViewItem labelStyle]) on GTTableViewItem.
 
 Default value is `nil`.
 */
@property (nonatomic, retain) IBOutlet UILabel *defaultCellLabel;

/**
 The default subtitle label for any item's cell. 
 If a regular GTTableView cell is used this label's attributes are copied to the cell.
 To customise on a per item basis set [subtitleLabelStyle]([GTTableViewItem subtitleLabelStyle]) on GTTableViewItem.
 
 Default value is `nil`.
 */
@property (nonatomic, retain) IBOutlet UILabel *defaultCellSubtitleLabel;

/**
 This sets the default background colour for any item's cell.
 To customise on a per item basis set [backgroundColor]([GTTableViewItem backgroundColor]) on GTTableViewItem.

 Default value is `[UIColor white]`.
 */
@property (nonatomic, retain) UIColor *defaultCellBackgroundColor; 

/**
 This sets the default selection background colour for any item's cell.
 To customise on a per item basis set [selectionBackgroundColor]([GTTableViewItem selectionBackgroundColor]) on GTTableViewItem.
 
 Default value is set by UITableViewCell automatically.
 @warning This doens't work for every UITableViewStyle.
 */
@property (nonatomic, retain) UIColor *defaultCellSelectionBackgroundColor; 


///---------------------------------
/// @name TableView Section Properties
///---------------------------------

/**
 The default height of a section header. Override these by adding a GTTableViewHeaderItem with setTableViewHeaderItem:forSection:
 
 Default value is `0.0`.
 */
@property (nonatomic, assign) CGFloat defaultHeaderItemHeight;

/**
 The default height of a section footer. Override these by adding a GTTableViewHeaderItem with setTableViewFooterItem:forSection:
 
 Default value is `0.0`.
 */
@property (nonatomic, assign) CGFloat defaultFooterItemHeight;

/**
 The index titles that are used for a table view with an index on the right hand side.
 */
@property (nonatomic, retain) NSArray *sectionIndexTitlesForTableView;

/**
 Retrieve a GTTableViewHeaderItem item for a specific section.
 @param section The index of the section.
 @return The item for the specified section or nil if not previously set.
 */
- (GTTableViewHeaderItem*)tableViewHeaderItemForSection:(NSInteger)section;
/**
 Set a GTTableViewHeaderItem for a specific section.
 @param item The GTTableViewHeaderItem to be set.
 @param section The index of the section.
 */
- (void)setTableViewHeaderItem:(GTTableViewHeaderItem*)item forSection:(NSInteger)section;

/**
 Retrieve a GTTableViewFooterItem for a specific section.
 @param section The index of the section.
 @return The item for the specified section or nil if not previously set.
 */
- (GTTableViewFooterItem*)tableViewFooterItemForSection:(NSInteger)section;

/**
 Set a GTTableViewFooterItem for a specific section.
 @param item The GTTableViewFooterItem to be set.
 @param section The index of the section.
 */
- (void)setTableViewFooterItem:(GTTableViewFooterItem*)item forSection:(NSInteger)section;

///---------------------------------
/// @name Item & Sections
///---------------------------------

/**
 @return The number of sections.
 */
- (NSInteger)numberOfItemSections;


/**
 @param section The index of the specified section.
 @return The number of GTTableViewItem instances in specified section not including hidden items.
 @warning This does not include GTTableViewItems instances with [visible]([GTTableViewItem visible]) set to `NO`.
 */
- (NSInteger)numberOfItemsInSection:(NSInteger)section; 

/**
 @param section The index of the specified section.
 @param visible Whether the count should include only visible items. When `NO` hidden items will be included. When `YES` hidden items will not be included.
 @return The number of GTTableViewItem instances in specified section. Can be filtered to only include visible items.
 */
- (NSInteger)numberOfItemsInSection:(NSInteger)section onlyVisible:(BOOL)visible;

/**
 @return The GTTableViewItem instances in all sections that are visible.
 */
- (NSArray*)items; 

/**
 @param visible Whether it should include only visible items. When `NO` hidden items will be included. When `YES` hidden items will not be included.
 @return The GTTableViewItem instances in a tableview. Can be filtered to only include visible items.
 */
- (NSArray*)itemsOnlyVisible:(BOOL)visible;

/**
 @param section The index of the specified section.
 @return All visible GTTableViewItem instances in the specified section.
 */
- (NSArray*)itemsInSection:(NSInteger)section; 

/**
 @param section The index of the specified section.
 @param visible Whether it should include only visible items. When `NO` hidden items will be included. When `YES` hidden items will not be included.
 @return All GTTableViewItem instances in the specified section. Can be filtered to only include visible items.
 */
- (NSArray*)itemsInSection:(NSInteger)section onlyVisible:(BOOL)visible;

/**
 @param indexPath The index path of to lookup the item.
 @return The GTTableViewItem at specified index path.
 @warning Two index paths exist for each item if there is hidden items. 
 */
- (GTTableViewItem*)itemForRowAtIndexPath:(NSIndexPath*)indexPath; 

/**
 @param indexPath The index path of to lookup the item.
 @param visible Whether it should include only visible items. When `NO` hidden items will be included. When `YES` hidden items will not be included.
 @return The GTTableViewItem at specified index path.
 @warning Two sets of index paths exist if there is hidden items. The visible parameter will specify which index path set to use.
 */
- (GTTableViewItem*)itemForRowAtIndexPath:(NSIndexPath*)indexPath onlyVisible:(BOOL)visible;

/**
 @param item The item whoms index path is to be found.
 @return The index path of the item or nil if no index path exists for item.
 @warning Two sets of index paths exist if there is hidden items. This will only search visible items. use indexPathForItem:onlyVisible: to find the index path including hidden items.
 */
- (NSIndexPath*) indexPathForItem:(GTTableViewItem*)item; 

/**
 @param item The item whoms index path is to be found.
 @param visible Whether it should include only visible items. When `NO` hidden items will be included. When `YES` hidden items will not be included.
 @return The index path of the item or nil if no index path exists for item.
 @warning Two sets of index paths exist if there is hidden items. Use visible to find the index path including hidden items.
 */
- (NSIndexPath*) indexPathForItem:(GTTableViewItem*)item onlyVisible:(BOOL)visible;


/**
 This method updates each GTTableViewCell by calling [configureCell:]([GTTableViewItem configureCell:]) on its [item]([GTTableViewCell item]) property.
 
 A good use of this might be to hook up a timer to this if a GTTableViewCell's content changes every second. It might also be implemented in viewWillAppear: to force a content update.
 */
- (void) refreshVisibleCells; 
 
/**
 The animation to use for all insert animations. This includes unhiding items with the visible property.
 
 Default value is `UITableViewRowAnimationRight`.
 */ 
@property (nonatomic, assign) UITableViewRowAnimation insertAnimation; 

/**
 The animation to use for all delete animations. This includes hiding items with the visible property.
 
 Default value is `UITableViewRowAnimationRight`.
 */ 
@property (nonatomic, assign) UITableViewRowAnimation deleteAnimation;

/**
 This calls beginUpdates on the UITableView and performs some of its own magic.
 */
- (void)beginItemUpdates; 

/**
 This calls endUpdates on the UITableView and performs some of its own magic.
 */ 
- (void)endItemUpdates; 



- (void)insertSectionAtIndex:(NSInteger)index;
- (void)removeSectionAtIndex:(NSInteger)index;
- (void)removeAllSections;

- (void)appendItem:(GTTableViewItem*)item section:(NSInteger)section;
- (void)appendItems:(NSArray*)items section:(NSInteger)section;
- (void)insertItem:(GTTableViewItem*)item atIndexPath:(NSIndexPath*)indexPath;
- (void)insertItem:(GTTableViewItem*)item atIndexPath:(NSIndexPath*)indexPath onlyVisible:(BOOL)visible;

- (void)removeItemAtIndexPath:(NSIndexPath*)indexPath;
- (void)removeItemAtIndexPath:(NSIndexPath*)indexPath onlyVisible:(BOOL)visible;



@end
