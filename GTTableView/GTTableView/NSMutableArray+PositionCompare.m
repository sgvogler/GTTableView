//
//  PositionCompare.m
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 16/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import "NSMutableArray+PositionCompare.h"


@implementation NSMutableArray (PositionCompare)
- (void)addObjectsFromArray:(NSArray*)anArray withIdenticalObjectsAtIdenticalIndexesInArray:(NSArray*)otherArray;
{
    int count = MIN([anArray count],[otherArray count]);
    for (int i = 0; i < count; i++)
    {
        if ([anArray objectAtIndex:i] == [otherArray objectAtIndex:i]) 
        {
            [self addObject:[anArray objectAtIndex:i]];
        }
    }
}
@end
