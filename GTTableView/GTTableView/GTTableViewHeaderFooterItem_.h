//
//  GTTableViewHeaderFooterItem_.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 3/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import <Foundation/Foundation.h>
static const CGFloat GTTableViewHeaderFooterDefaultHeight = DBL_MIN;
#pragma mark Abstract Parent Class -
@class GTTableView;
@interface GTTableViewHeaderFooterItem_ : NSObject {
    GTTableView *tableView;
}
@property (nonatomic, retain) UIView *view;
@property (nonatomic, copy) NSString *text;
@property (nonatomic, assign) CGFloat height;
@end

#pragma mark - Subclasses -
@interface GTTableViewHeaderItem : GTTableViewHeaderFooterItem_ {
}
@end

@interface GTTableViewFooterItem : GTTableViewHeaderFooterItem_ {
}
@end