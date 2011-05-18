//
//  GTTableViewViewController.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 2/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GTTableViewController.h"
@interface DemoViewController : GTTableViewController  {
    
    UILabel *titleLabel;
}
@property (nonatomic, retain) IBOutlet UILabel *titleLabel;

@end
