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
@synthesize titleLabel;

- (void)dealloc
{
    [titleLabel release];
    [super dealloc];
}
- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
        
    // Release any cached data, images, etc that aren't in use.
}

- (void) hideItem:(GTTableViewItem*)item {
    if ([self.tableView indexPathForItem:item].row != 0) return;
    static BOOL hidden = NO;
    [self.tableView beginUpdates];

    if (!hidden)
    {
        for (GTTableViewItem *i in [self.tableView itemsInSection:[self.tableView indexPathForItem:item].section])
            if ([self.tableView indexPathForItem:i].row != 0){

                [i setVisible:NO];
            }

    }
    else
    {
        for (GTTableViewItem *i in [self.tableView itemsInSection:[self.tableView indexPathForItem:item].section onlyVisible:NO])
            if ([self.tableView indexPathForItem:i onlyVisible:NO].row != 0)
            {
                [i setVisible:YES];
            }
    }
    
    [self.tableView endUpdates];

    hidden = !hidden;
  //  [item setBackgroundColor:[UIColor redColor]];
}
#pragma mark - View lifecycle


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [self.tableView insertSectionAtIndex:0];
    self.tableView.insertAnimation = UITableViewRowAnimationTop;
    self.tableView.deleteAnimation = UITableViewRowAnimationTop;
    UILabel *clearBackgroundLabel = [[[UILabel alloc] init] autorelease];
    clearBackgroundLabel.backgroundColor = [UIColor clearColor];
    for (int i = 0; i < 4; i++) 
    {
        GTTableViewItem *item = [GTTableViewItem item];
        item.title = [NSString stringWithFormat:@"item %i",i];
        item.subtitle = @"Subtitle";
        item.selectionBackgroundColor = [UIColor greenColor];
        item.selectionStyle = UITableViewCellSelectionStyleNone;
        //item.labelStyle = clearBackgroundLabel;
        item.target = self;
        item.action = @selector(hideItem:);
        [self.tableView insertItem:item atIndexPath:[NSIndexPath indexPathForRow:i inSection:0] onlyVisible:NO];
        
    }
    [self.tableView setBottomGradientHeaderViewWithHeight:80 colors:nil locations:nil padding:40];
    [self.tableView setTopGradientHeaderViewWithHeight:80 colors:nil locations:nil];
    [self.tableView setTopGradientFooterViewWithHeight:80 colors:nil locations:nil padding:40];
    [self.tableView setBottomGradientFooterViewWithHeight:80 colors:nil locations:nil];

    GTTableViewItem *item = [GTTableViewItem item];
    item.title = [NSString stringWithFormat:@"item inserted"];
    item.style = UITableViewCellStyleValue1;
    item.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
    item.target = self;
    item.action = @selector(hideItem:);
    item.accessoryAction = @selector(accessoryTapped:);
    item.subtitle = @"subtitle..";
    item.reuseIdentifier = @"value2";
    item.height = 44;
    item.indentationLevel = 1;
    item.visible = YES;
   //
    [self.tableView appendItem:item section:0];
    [super viewDidLoad];

    [self.tableView setDefaultCellHeight:100.0];
    [self.tableView setDefaultCellStyle:UITableViewCellStyleSubtitle];
}
- (void)accessoryTapped:(GTTableViewItem*)i
{
    GTTableViewItem *item = [GTTableViewItem item];
    item.title = [NSString stringWithFormat:@"new inserted at index 0"];
    item.style = UITableViewCellStyleValue1;
    item.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
    item.target = self;
    item.action = @selector(hideItem:);
    item.accessoryAction = @selector(accessoryTapped:);
    item.subtitle = @"subtitle..";
    item.reuseIdentifier = @"value3";
    item.height = 44;
    item.indentationLevel = 1;   
    [self.tableView beginUpdates];
    [self.tableView insertItem:item atIndexPath:[NSIndexPath indexPathForRow:0 inSection:0]];
    [self.tableView endUpdates];

}


- (void)viewDidUnload
{
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
