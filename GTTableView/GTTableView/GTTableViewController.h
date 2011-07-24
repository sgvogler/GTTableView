//
//  GTTableViewController.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 18/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//
/**
 A thin UIViewController subclass that
 
 + Creates a GTTableView instance if none is already assigned in the nib and assigns it to the property tableView.
 + Assigns itself as the GTTableView delegate and implments the GTTableViewDelegate protocol.
 + Fowards viewDidAppear: and viewWillDisappear: messages to tableView. If these are overriden in a subclass be sure to call super.
 
 @warning Call [super viewDidLoad] before implementing any of your own changes to self.tableView, if the tableview isn't already hooked up in a nib. This is where a GTTableView instance is created if none exists.
 
 */
#import <UIKit/UIKit.h>
#import "GTTableView.h"
#import "GTTableViewHeaderFooterItem_.h"
#import "GTTableViewItem.h"
#import "GTTableViewCell.h"

@interface GTTableViewController : UIViewController <GTTableViewDelegate> {
    GTTableView *tableView_;
}
@property (nonatomic, retain) IBOutlet GTTableView *tableView; /// GTTableView property that should be hooked up in a nib or prior to viewDidLoad. In viewDidLoad if no delegate is set on the tableView this class attempts to set itself as delegate.
@end
