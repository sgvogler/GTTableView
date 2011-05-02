//
//  GTTableViewAppDelegate.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 2/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import <UIKit/UIKit.h>

@class GTTableViewViewController;

@interface GTTableViewAppDelegate : NSObject <UIApplicationDelegate> {

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet GTTableViewViewController *viewController;

@end
