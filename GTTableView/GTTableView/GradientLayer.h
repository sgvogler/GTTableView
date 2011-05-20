//
//  GradientLayer.h
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 17/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>


@interface CAGradientLayer (GradientLayer)
- (void)setupGradientLayerWithColors :(NSArray *)colors direction:(CGFloat)radians frame:(CGRect)aFrame;
@end
