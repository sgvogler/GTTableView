//
//  GTTableViewController.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 18/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//
/**
 ** A very simple UIViewController subclass it; 
 - assigns itself as the GTTableView delegate and implments the GTTableViewDelegate protocol.
 - creates a GTTableView instance if none is already assigned in the nib and assigns it to the property tableView.
 - fowards viewDidAppear: and viewWillDisappear: messages to tableView.
 */
#import <UIKit/UIKit.h>
#import "GTTableView.h"
@interface GTTableViewController : UIViewController <GTTableViewDelegate> {
    GTTableView *tableView_;
}
@property (nonatomic, retain) IBOutlet GTTableView *tableView;
@end
