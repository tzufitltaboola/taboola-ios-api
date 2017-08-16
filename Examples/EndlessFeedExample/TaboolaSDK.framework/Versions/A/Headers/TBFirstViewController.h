//
//  TBFirstViewController.h
//  TaboolaDemoApp


#import <UIKit/UIKit.h>
#import "TaboolaView.h"

@interface TBFirstViewController : UIViewController <TaboolaViewDelegate>{
	IBOutlet TaboolaView *mTaboolaView;
	IBOutlet UIScrollView *mScrollView;
	IBOutlet UILabel *mTextLabel;
}

@end
