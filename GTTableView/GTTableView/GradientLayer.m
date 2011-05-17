//
//  GradientLayer.m
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 17/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import "GradientLayer.h"

@implementation CAGradientLayer (GradientLayer)
+ (CAGradientLayer*)layerWithColors:(NSArray*)colors direction:(CGFloat)radians frame:(CGRect)aFrame
{
    CAGradientLayer *newLayer = [CAGradientLayer layer];
    newLayer.frame = aFrame;
    [newLayer setupGradientLayerWithColors:colors direction:radians frame:aFrame];
      return newLayer;
}
- (void)setupGradientLayerWithColors :(NSArray *)colors direction:(CGFloat)radians frame:(CGRect)aFrame 
{
    NSMutableArray *array = [NSMutableArray array];
    for (UIColor *color in colors) [array addObject:(id)[color CGColor]];

    self.frame = aFrame;
    self.colors = array;
    self.opaque = NO;
    self.startPoint = CGPointMake(cos(radians), sin(radians));
    self.endPoint = CGPointMake(-cos(radians), -sin(radians));
}
@end
