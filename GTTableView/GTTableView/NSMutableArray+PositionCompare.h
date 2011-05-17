//
//  PositionCompare.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 16/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSMutableArray (PositionCompare)
- (void)addObjectsFromArray:(NSArray*)anArray withIdenticalObjectsAtIdenticalIndexesInArray:(NSArray*)otherArray;
@end
