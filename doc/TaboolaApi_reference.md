# Taboola API SDK iOS Reference

> **Note**: if you haven't been specifically instructed by your Taboola account manager to use this section of TaboolaApi, you should probably use [TaboolaView](http://github.com/taboola/taboola-ios) which is faster and more simple to integrate.  

# TaboolaApi
### `+ (instancetype) sharedInstance`
#### **Returns:**
* a singleton instance of the SDK

### `- (void)startWithPublisherID:(NSString *)publisherId andApiKey:(NSString *)apiKey`
Initializes TaboolaApi. Must be called before any other method of the SDK. Typically you would want to do it in you AppDelegate class in application:didFinishLaunchingWithOptions: method.

#### **Parameters:**
* `publisherId` — The publisher id in the Taboola system
* `apiKey` — The API key that was provided by Taboola for the application

### `- (void)fetchRecommendations:(TBRecommendationRequest *)recommendationsRequest onSuccess:(TBRecommendationRequestSuccessCallback)onSuccess onFailure:(TBRecommendationRequestFailureCallback)onFailure`
Requests recommendation items.

#### **Parameters:**
* `recommendationsRequest` — `TBRecommendationRequest` with at least one `TBPlacementRequest`
* `onSuccess` — success callback block
* `onFailure` —  failure callback block 

### `- (void)getNextBatchForPlacement:(TBPlacement *)placement itemsCount:(NSInteger)count onSuccess:(TBRecommendationRequestSuccessCallback)onSuccess onFailure:(TBRecommendationRequestFailureCallback)onFailure`
Used for implementing pagination or infinite scroll (load more items as the user scrolls down).
The method gets the next batch of recommendation items for a specified placement. The name of the returned Placement will have a "counter" added as a suffix. For example, if the original placement name was "article" the new name will be "article 1", next one "article 2", and so on. The counter is incremented on each successful fetch.

#### **Parameters:**
* `placement` — placement to request next recommendation items for
* `count` — number of items
* `onSuccess` — success callback block
* `onFailure` —  failure callback block 

### `- (void)handleAttributionClick`
Shows a standard popup with attribution, ad-choices and opt-out data.

This method **MUST** be called when the user clicks on the attribution view ("By Taboola" text or the ad-choices icon).

### `- (void)setOnClickIgnorePeriod:(NSTimeInterval) ignorePeriod`
To avoid accidental user clicks, the TB views will ignore clicks that were done immediately after the view became visible.

**DON’T CHANGE THIS VALUE** without consulting your Taboola account manager.

#### **Parameters:**
* `ignorePeriod ` — time in seconds

### `- (void)setOnClickIgnorePeriod:(NSTimeInterval) ignorePeriod`
To avoid accidental user clicks, the TB views will ignore clicks that were done immediately after the view became visible.

### `id<TaboolaApiClickDelegate> clickDelegate`
TaboolaApi delegate is used to intercept recommendation clicks and block default click handling for organic items. 

### `NSString *apiKey`
**Read Only**
API key used by the SDK.

### `NSString *publisherId`
Publisher ID used by the SDK.
# TaboolaApiClickDelegate
### `- (BOOL)onItemClick:(NSString *)placementName withItemId:(NSString *)itemId withClickUrl:(NSString *)clickUrl isOrganic:(BOOL)organic`
Delegate method is called on every touch on the Placement.

#### **Parameters:**
* `placementName ` — placement name
* `itemId ` —  item identifier
* `clickUrl` — item URL
* `organic` — indicates whether the item clicked was an organic content recommendation or not. Best practice would be to suppress the default behavior for organic items, and instead open the relevant screen in your app which shows that piece of content.

#### **Returns:**
* `BOOL` — Return `false` to abort the default behaviour, the app should display the recommendation content on its own (for example, using an in-app browser). (Aborts only for organic items!)
Return `true` - this will allow the app to implement a click-through and continue to the default behaviour.


# TBRecommendationRequest
### `+ (instancetype)new`
Initializes a Recommendation request. Parameters and Placements must be added to the request after initialization in order to fetch recommendations.

### `- (void)setPageUrl:(NSString*)url`
#### **Parameters:**
* `url` — a fully qualified (http:// or https://) publicly accessible URL that contains the content and/or meta data for the current source item (the piece of content the recommendations are going to be placed next to).

### `- (void)setSourceId:(NSString *)sourceId `
#### **Parameters:**
* `sourceType` — the type of the content the recommendations will be placed next to.

### `- (void)setUserReferrer:(NSString*) referrer `
#### **Parameters:**
* `referrer ` — the referrer (HTTP header) from the request that led to the current page.

### `- (void)setUnidiedId:(NSString*) unifiedId `
#### **Parameters:**
* `unifiedId` — an opaque, anonymized and unique identifier of the user in the publisher’s eco-system. This identifier should be identical cross application and device (e.g. hashed e-mail, or login).

### `TBSourceType sourceType`
The type of the content the recommendations will be placed next to. The following values are supported:
```
typedef enum {
    TBSourceTypeVideo, //should be passed when the recommendations are placed near a video
    TBSourceTypeText, // near a textual piece such as an article / story
    TBSourceTypePhoto, // near a photo or gallery
    TBSourceTypeHome, // on the app entry (home) screen
    TBSourceTypeSection, // on a screen representing a “section front” or “topic”
    TBSourceTypeSearch // on a search results page
} TBSourceType;
```

###  `NSString *targetType`
Type of recommended organic content to return.
**Note**: this parameter does not influence the type of sponsored content returned – the mix of the sponsored content types is currently determined by a server side configuration.
###  `NSString *targetType`
Type of recommended organic content to return.
**Note**: this parameter does not influence the type of sponsored content returned – the mix of the sponsored content types is currently determined by a server side configuration.

###  `NSDictionary *parameters`
Recommendation request parameters.

### `- (void)addPlacementRequest:(TBPlacementRequest *)parameters error:(NSError **)error`
Adds a `TBPlacementRequest` to the `TBRecommendationRequest`. Up to 12 `TBPlacementRequest` per `TBRecommendationRequest` are allowed. All placements must have unique names.

#### **Parameters:**
* `placementRequest` — placement to be added
* `error` — error object

### `- (instancetype)createNextBatchRequest:(NSString *)placementName itemsCount:(NSUInteger)itemsCount`
Adds a `TBPlacementRequest` to the `TBRecommendationRequest`. Up to 12 `TBPlacementRequest` per `TBRecommendationRequest` are allowed. All placements must have unique names.

#### **Parameters:**
* `placementName ` — placement name for the `TBRecommendationRequest`
* `itemsCount` — number of items in the Placement

# TBPlacementRequest

### `+ (instancetype)new`
Initializes a `TBPlacementRequest` . Name and number of items must be added to the request after initialization. Creates request for a specific placement.

### `NSString* name`
A text string, uniquely identifying the placement

### `NSUInteger recCount`
A non-negative integer specifying how many recommendations are requested.
The API will not return more recommendations than this, though if there are
not enough good quality recommendations to satisfy the request,
fewer items might be returned.

### `-(void)setThumbnailSize:(CGSize)size`
Sets the size (in pixels) of the thumbnails returned for recommendations. Both parameters (height and width) should either appear together or not appear at all.

In case the thumbnail size parameters are specified, the thumbnail would always preserve its original aspect ratio – it will be scaled to the required size, centered and cropped if needed.

In addition, in case the thumbnail contains a face, we will detect that face by default and ensure it is contained within the generated thumbnail.

#### **Parameters:**
* `size` — size of the thumbnail

### `CGFloat width`
**Read Only**
Thumbnails width.

### `CGFloat height`
**Read Only**
Thumbnails height.

# TBPlacement
### `NSArray<TBItem *> *listOfItems`
Name of this placement.

### `NSString *placementName`
Placement name.

### `NSString *placementId`
Placement identifier.

# TBItem
#### **Returns:**
* a TBItem object configured with specified TBItemModel.

### `- (TBImageView *)thumbnailView`
Returns TBImageView that contains the thumbnail image of the recommendation item.
#### **Returns:**
* a TBImageView object configured with thumbnail image.

### `- (TBTitleLabel *)titleView`
Returns a TBTextView which contains the title of the recommended item.
#### **Returns:**
* a TBImageView object configured with thumbnail image.

### `- (TBBrandingLabel *)brandingView`
**Optional**
If branding text is available for the current recommendation item, returns a TBBrandingLabel which contains the branding text for the item. In case branding text is not available returns nil.
#### **Returns:**
* a TBBrandingLabel object configured with branding text.
 
### `- (void)initTitleView:(TBTitleLabel *)titleLabel`
Initializes a title label (TBTitleLabel instance) with the receiving TBItem object.

#### **Parameters:**
* `titleLabel` — TBTitleLabel object to be configured

### `- (void)initBrandingView:(TBBrandingLabel *)brandingLabel`
Initializes a branding label (TBBrandingLabel instance) with the receiving TBItem object. 

#### **Parameters:**
* `brandingLabel` — TBBrandingLabel object to be configured

### `- (void)initThumbnailView:(TBImageView *)imageView`
Initializes an TBImageView instance with the receiving TBItem object.

#### **Parameters:**
* `imageView` — TBImageView object to be configured
 

# TBImageView
TBImageView is subclass of UIImageView capable  of loading and displaying thumbnail images. Detects touches.

# TBTextView
TBTextView - subclass of UILabel for displaying TBItem title. Detects touches.

# TBBrandingView
TBBrandingView - subclass of UILabel for displaying TBItem branding text. Detects touches.
