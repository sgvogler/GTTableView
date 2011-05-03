//
//  GTTableViewCell.m
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 3/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import "GTTableViewCell.h"
#import "GTTableView.h"

@implementation GTTableViewCell
#pragma mark - Accessors -
- (GTTableViewItem *)item {
    return [tableView itemForRowAtIndexPath:[tableView indexPathForCell:self]];
}
- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (void)dealloc
{
    [super dealloc];
}


- (UIColor *)selectionBackgroundColor {
    return [[self selectedBackgroundView] backgroundColor];
}

- (void)setSelectionBackgroundColor:(UIColor *)selectionBackgroundColor {
    if (![self selectedBackgroundView])
    {
        self.selectedBackgroundView =  [[[UIView alloc] initWithFrame:self.backgroundView.frame] autorelease];
    }
    self.selectedBackgroundView.backgroundColor = selectionBackgroundColor;
}

@end
