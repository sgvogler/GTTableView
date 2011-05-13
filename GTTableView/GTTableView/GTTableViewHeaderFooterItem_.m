//
//  GTTableViewHeaderFooterItem_.m
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 3/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import "GTTableViewHeaderFooterItem_.h"
#import "GTTableView.h"
@interface GTTableViewHeaderFooterItem_ ()
- (void) setup_;
@property (nonatomic, assign) GTTableView *tableView;
@end

@implementation GTTableViewHeaderFooterItem_
@synthesize tableView;
#pragma mark - Accessors -
@synthesize view = view_;
@synthesize text = text_;
@synthesize height = height_;

- (CGFloat)height {
    if (height_ != GTTableViewHeaderFooterDefaultHeight)
        return height_;
    if (view_)
        return view_.frame.size.height;
    return GTTableViewHeaderFooterDefaultHeight;
}
#pragma mark - Object Lifecylce -

- (void)awakeFromNib
{
    [self setup_];   
}
- (id)init
{
    self = [super init];
    if (self)
    {
        [self setup_];
    }
    return self;
}

- (void)setup_
{
    height_ = GTTableViewHeaderFooterDefaultHeight;
}

- (void)dealloc {
    [view_ release];
    [text_ release];
    [super dealloc];
}

@end
