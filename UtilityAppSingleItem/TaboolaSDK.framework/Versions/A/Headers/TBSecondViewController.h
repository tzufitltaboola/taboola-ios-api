//
//  TBSecondViewController.h
//  TaboolaDemoApp


#import <UIKit/UIKit.h>
#import "TaboolaView.h"

@interface TBSecondViewController : UIViewController <TaboolaViewDelegate>{
	IBOutlet TaboolaView *mTaboolaView;
	IBOutlet UIWebView *mWebView;
	IBOutlet UIScrollView *mScrollView;
	IBOutlet UILabel *mTextLabel;
}

@end
