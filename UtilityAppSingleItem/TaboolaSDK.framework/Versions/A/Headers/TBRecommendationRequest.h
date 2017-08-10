//
//  TBRecommendationRequest.h
//  TaboolaView
//
//  Copyright © 2017 Taboola. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TBPlacementRequest.h"

typedef enum {
    TBSourceTypeVideo,
    TBSourceTypeText,
    TBSourceTypePhoto,
    TBSourceTypeHome,
    TBSourceTypeSection,
    TBSourceTypeSearch
} TBSourceType;

@interface TBRecommendationRequest : NSObject

@property (nonatomic) TBSourceType sourceType;
@property (nonatomic, copy) NSString *sourceUrl;
@property (nonatomic, copy) NSString *sourceId;
@property (nonatomic) NSInteger batchCount;

- (NSDictionary *)parameters;
- (void)addPlacementRequest:(TBPlacementRequest *)parameters error:(NSError **)error;

- (instancetype)createNextBatchRequest:(NSString *)placementName itemsCount:(NSUInteger)itemsCount;

@end
