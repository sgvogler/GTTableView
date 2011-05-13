//
//  UILabel+CopyStyle.m
//  GTTableView
//
//  Created by Andrew Mackenzie-Ross on 10/05/11.
//  Copyright 2011 mackross.net. All rights reserved.
//

#import "UILabel+CopyStyle.h"


@implementation UILabel (CopyStyle)
- (void)copyStyleFromLabel:(UILabel *)aLabel
{
    if (!aLabel) return;
    
    /** Accessing the Text Attributes. */
    if (aLabel.font)
        self.font =  aLabel.font;
    if (aLabel.textColor)
        self.textColor = aLabel.textColor;
    self.textAlignment = aLabel.textAlignment;
    self.lineBreakMode = aLabel.lineBreakMode;
    self.enabled = aLabel.enabled;
    
    /** Sizing the Label's Text. */
    self.adjustsFontSizeToFitWidth = aLabel.adjustsFontSizeToFitWidth;
    self.baselineAdjustment = aLabel.baselineAdjustment;
    self.minimumFontSize = aLabel.minimumFontSize;
    self.numberOfLines = aLabel.numberOfLines;
    
    /** Managing Highlight Values. */
    if (aLabel.highlightedTextColor)
        self.highlightedTextColor = aLabel.highlightedTextColor;
    self.highlighted = aLabel.highlighted;
    
    /** Drawing a Shadow. */
    if (aLabel.shadowColor)
        self.shadowColor = aLabel.shadowColor;
    self.shadowOffset = aLabel.shadowOffset;
    
    /** Setting and Getting Attributes. */
    self.userInteractionEnabled = aLabel.userInteractionEnabled;
    if (aLabel.backgroundColor)
        self.backgroundColor = aLabel.backgroundColor;
}
@end
