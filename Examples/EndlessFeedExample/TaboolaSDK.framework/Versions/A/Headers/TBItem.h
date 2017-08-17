//
//  TBItem.h
//  TaboolaView
//
//  Copyright © 2017 Taboola. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TBImageView.h"
#import "TBTitleLabel.h"
#import "TBBrandingLabel.h"

@class TBItemModel;
@interface TBItem : NSObject

- (instancetype)initWithItemModel:(TBItemModel *)model;

//create UIViews manually
- (TBImageView *)thumbnailView;
- (TBTitleLabel *)titleView;
- (TBBrandingLabel *)brandingView;

//create UIViews from storyboard
- (void)initTitleView:(TBTitleLabel *)titleLabel;
- (void)initBrandingView:(TBBrandingLabel *)brandingLabel;
- (void)initThumbnailView:(TBImageView *)imageView;

@end
