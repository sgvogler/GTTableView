//
//  GTTableViewViewController.m
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 2/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import "DemoViewController.h"
#import "GTTableViewItem.h"
@implementation DemoViewController
@synthesize tableView;
@synthesize titleLabel;

- (void)dealloc
{
    [tableView release];
    [titleLabel release];
    [super dealloc];
}
- (void) viewDidAppear:(BOOL)animated {
    [tableView viewDidAppear:animated];
    [super viewDidAppear:animated];
}
- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
        
    // Release any cached data, images, etc that aren't in use.
}

- (void) hideItem:(GTTableViewItem*)item {
  //  [item setBackgroundColor:[UIColor redColor]];
}
#pragma mark - View lifecycle


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [self.tableView insertSectionAtIndex:0 animation:UITableViewRowAnimationNone];

    UILabel *clearBackgroundLabel = [[[UILabel alloc] init] autorelease];
    clearBackgroundLabel.backgroundColor = [UIColor clearColor];
    for (int i = 0; i < 80; i++) 
    {
        GTTableViewItem *item = [GTTableViewItem item];
        item.title = [NSString stringWithFormat:@"item %i",i];
        item.subtitle = @"Subtitle";
        item.selectionBackgroundColor = [UIColor greenColor];
        item.selectionStyle = UITableViewCellSelectionStyleNone;
        item.labelStyle = clearBackgroundLabel;
        item.target = self;
        item.action = @selector(hideItem:);
        [self.tableView insertItem:item atIndexPath:[NSIndexPath indexPathForRow:i inSection:0] animation:UITableViewRowAnimationTop onlyVisible:NO];
        
    }
    GTTableViewItem *item = [GTTableViewItem item];
    item.title = [NSString stringWithFormat:@"item inserted"];
    item.style = UITableViewCellStyleValue1;
    item.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
    item.subtitle = @"subtitle..";
    item.reuseIdentifier = @"value2";
    item.height = 44;
    item.indentationLevel = 1;
    [self.tableView insertItem:item atIndexPath:[NSIndexPath indexPathForRow:2 inSection:0] animation:UITableViewRowAnimationRight];
    [super viewDidLoad];
    [self.tableView setFinishedLoading:YES];

    [tableView setDefaultCellLabel:self.titleLabel];
    [tableView setDefaultCellHeight:100.0];
    [tableView setDefaultCellStyle:UITableViewCellStyleSubtitle];
}

- (UINavigationController *)navigationControllerForTableView:(GTTableView *)tableView {
    return self.navigationController;
}

- (void)viewDidUnload
{
    [self setTableView:nil];
    [self setTitleLabel:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return YES;
}

@end
