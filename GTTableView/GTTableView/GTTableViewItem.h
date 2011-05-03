//
//  GTTableViewItem.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 3/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GTTableView+GTTableViewCell.h"

@class GTTableView;
@class GTTableViewCell;
@interface GTTableViewItem : NSObject {
@protected
    GTTableView *tableView; /**< Subclasses should use this to access the current GTTableView. */
@private
    
    /**
     All other properties when set will be saved to this dictionary to save memory.
     If properties are not set the default from the tableview will be used.
     */
     NSMutableDictionary *properties_;
    
    /**
     visible property will be set with iVars as it'll be hit often when calculating index paths.
     */
    BOOL visible_;
    BOOL visibleSet_;
}
@property (nonatomic, readonly) GTTableViewCell *cell;

/**
 Setting properteis overrides the default value set by the GTTableView.
 Resetting properties makes them take on the default value set by the GTTableView.
 */
@property (nonatomic, assign, getter = isSelected) BOOL selected;

- (void)resetSelected;
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;
- (void)resetSelectedAnimated:(BOOL)animated;
@property (nonatomic, assign) BOOL canEdit;
- (void)resetCanEdit;
@property (nonatomic, assign) BOOL canMove;
- (void)resetCanMove;
@property (nonatomic, assign, getter = isVisible) BOOL visible; /**< Be sure to call beginUpdates and endUpdates on the tableView when chaning this value. */
- (void)resetVisible;
- (void)setVisible:(BOOL)willBeVisible animation:(UITableViewRowAnimation)animation;
- (void)resetVisibleAnimation:(UITableViewRowAnimation)animation;
@property (nonatomic, assign) CGFloat height; /**< Be sure to call beginUpdates and endUpdates to get tableview to updatde height. */
- (void)resetHeight;
@property (nonatomic, assign) CGFloat indentationWidth; 
- (void)resetIndentationWidth;
@property (nonatomic, assign) BOOL shouldIndentWhileEditing; /**< Be sure to call beginUpdates and endUpdates to get tableview to updatde height. */
- (void)resetShouldIndentWhileEditing;
@property (nonatomic, assign) BOOL shouldShowReorderControl; 
- (void)resetShouldShowReorderControl;
@property (nonatomic, copy) NSString *deleteConfirmationTitle; /**< Be sure to call beginUpdates and endUpdates to get tableview to updatde height. */
- (void)resetDeleteConfirmationTitle;
@property (nonatomic, assign) UITableViewCellStyle style; /**< Be sure to call reloadData as all cells have to be regenerated. */
- (void)resetStyle;
@property (nonatomic, assign) UITableViewCellEditingStyle editingStyle; /**< Be sure to call beginUpdates and endUpdates to get tableview to updatde height. */
- (void)resetEditingStyle;
@property (nonatomic, assign) UITableViewCellAccessoryType accessoryType;
- (void)resetAccessoryType;
@property (nonatomic, assign) UITableViewCellAccessoryType editingAccessoryType;
- (void)resetEditingAccessoryType;
@property (nonatomic, assign) UITableViewCellSelectionStyle selectionStyle;
- (void)resetSelectionStyle;
@property (nonatomic, assign) NSInteger indentationLevel;
- (void)resetIndentationLevel;
@property (nonatomic, retain) UILabel *labelStyle;
- (void)resetLabelStyle;
@property (nonatomic, retain) UILabel *subtitleLabelStyle;
- (void)resetSubtitleLabelStyle;
@property (nonatomic, retain) UIColor *backgroundColor;
- (void)resetBackgroundColor;
@property (nonatomic, retain) UIColor *selectionBackgroundColor;
- (void)resetSelectionBackgroundColor;

- (id)item;
@end