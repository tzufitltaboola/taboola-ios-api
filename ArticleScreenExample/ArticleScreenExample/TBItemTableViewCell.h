//
//  TBItemTableViewCell.h
//  ArticleScreenExample
//
//  Created by Vasyl Human on 8/3/17.
//  Copyright © 2017 Vasyl Human. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <TaboolaApi.h>

@interface TBItemTableViewCell : UITableViewCell

@property (weak, nonatomic) IBOutlet TBImageView *tbImageView;
@property (weak, nonatomic) IBOutlet TBTitleLabel *titleView;
@property (weak, nonatomic) IBOutlet TBBrandingLabel *brandingView;

@end
