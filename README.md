# Taboola API iOS SDK (TaboolaApi)
![Platform](https://img.shields.io/badge/Platform-iOS-green.svg)
[![Version](https://img.shields.io/cocoapods/v/TaboolaSDK.svg?label=Version)](https://github.com/taboola/taboola-ios-api)
[![License](https://img.shields.io/badge/License%20-Taboola%20SDK%20License-blue.svg)](https://github.com/taboola/taboola-ios-api/blob/master/LICENSE)


## Table Of Contents
1. [Getting Started](#1-getting-started)
2. [Example Apps](#2-example-apps)
3. [SDK Reference](#3-sdk-reference)
4. [License](#4-license)

## Basic concepts
The TaboolaApi allows you to get Taboola recommendations to display in your app. 
For each recommendation item TaboolaApi will provide pre-populated views, which you can style to match your app look and feel and place where needed within your app.
The views will automatically handle evertything else: click handling, reporting visiblity back to Taboola's server and more.

Browse through the sample apps in this repository to see how the TaboolaApi can be implemented in different types of apps.
## 1. Getting Started


### 1.1. Minimum requirements

* Build against Base SDK `7.0` or later. Deployment target: iOS `6.0` or later.
* Use `Xcode 5` or later.

### 1.2. Incorporating the SDK

#### Installation with CocoaPods

[CocoaPods](http://cocoapods.org) is a dependency manager for Objective-C, which automates and simplifies the process of using 3rd-party libraries like Taboola in your projects.

You can install it with the following command:

```bash
$ gem install cocoapods
```

##### Podfile

To integrate Taboola into your Xcode project using CocoaPods, specify it in your `Podfile`:

* Objective-C

   ```
   pod 'TaboolaSDK'
   ```

* Swift

   ```
   use_frameworks!
   pod 'TaboolaSDK'
   ```

Then, run the following command:

```bash
$ pod install
``` 

### 1.3. Initialize TaboolaApi

Beofre loading Taboola recommendations, apps should initialize TaboolaApi. Add the following call in your `AppDelegate` class, `didFinishLaunchingWithOptions` method:

```objc
[[TaboolaApi sharedInstance] startWithPublisherID:@"my-publisher-id" 
	andApiKey:@"my-api-key"];
```
### 1.4. Construct your request for recommendations

Make the recommendations requests in your view controller, right before you show the Taboola recommendations. Do this as close as possible to when the recommendations are going to be displayed, avoid getting recommendations for screens which the app user might not view.



Create a `TBPlacementRequest` for each placement (You can do this in your `ViewController`code)

```java
TBPlacementRequest *placementReq = [TBPlacementRequest new];
placementReq.name = @"below-article";  //replace this with your actual placement name
placementReq.recCount = 4;  //replace this with the actual number of items required in your placement
   
[placementReq.recCount setThumbnailSize: CGSizeMake(10,10)] //Optionally, set an explicit required thumbnail size to get from Taboola server (to optimize bandwidth)   
```
Create A `TBRecommendationsRequest` and add all of the previously created `TBPlacementRequest` objects to it

```objc
TBRecommendationRequest *recomendationRequest = [TBRecommendationRequest new];
recomendationRequest.sourceType = TBSourceTypeText; //replace this with your page actual source type
recomendationRequest.sourceId = @"my-source-id";  //replace this with your page actual source id
recomendationRequest.sourceUrl = @"http://www.example.com";  //replace this with your page actual source URL

// Add maximum of 12 placement requests per recommendation request
[recomendationRequest addPlacementRequest:placementReq];
```

> **NOTICE: Maximum 12 `TBPlacementRequest` per one `TBRecommendationsRequest`**

### 1.5. Fetch Taboola recommendations
Execute the `fetchRecommendations` method of the singleton TaboolaApi object with your `TBRecommendationsRequest` object. provide callback methods for `onSuccess` and `onFailure` events.

The code in the `onSuccess` callback should handle adding the items onto the view controller.

```
[[TaboolaApi sharedInstance] fetchRecommendations:recomendationRequest 
onSuccess:^(TBRecommendationResponse *response) {

	// Iterate over the placements from the response. In this specific example we only have a single placement
	TBPlacement *placement = response.placements.firstObject;
	
	//Get the list of items from each placments and add them to your view controller
	[self yourOwnMethodToAddTaboolaItemsToView withListOfItems:placement.listOfItems];
        
} onFailure:^(NSError *error) {
	// Handle errors here
	NSLog(@"Something went wrong");
}];

```

### 1.6. Displaying Taboola recommendations
The `TBItem`s from the result `TBPlacment` should be added onto the screen in order to be visible.
Each `TBItem` contains a few UI elements:

1. `TBImageView` - holds the item thumbnail image
2. `TBTitleLabel` - holds the item title text label
3. `TBBrandingLabel` - holds the item branding text label (may not exist in all items)
4. `TBDescriptionLabel` - holds the item description text label (may not exist in all items)

The `TBItem` also contains `NSDictionary` element:
- `extraDataDictionary` - holds extra data (categories, created, duration, type, views)


For each item, all available UI elements should be added to the screen.
The UI elements can be placed on screen either via interface builder (storyboard) or manually via code.
Use the correct `TBItem` method to initialize the UI element based on how you chose to add it to the screen.

#### When using interface builder
Assuming we have these properties defined as outels for interface builder UI elements:

```
@property (weak, nonatomic) IBOutlet TBImageView *tbImageView;
@property (weak, nonatomic) IBOutlet TBTitleLabel *titleView;
@property (weak, nonatomic) IBOutlet TBBrandingLabel *brandingView;
@property (weak, nonatomic) IBOutlet TBDescriptionLabel *descriptionView;

```
In our view controller code, we can initialize the UI items from a `TBItem` like that:

```
TBItem *myTBItem = placement.listOfItems[currItemIndex];

if (myTBItem != nil) {
	[myTBItem initThumbnailView:tbImageView];
	[myTBItem initTitleView:titleView];
	[myTBItem initBrandingView:brandingView];
	[myTBItem initDescriptionView:descriptionView];
}
```

#### When creating UI elements manually in code
Get the UI elements from the `TBItem` and add them to the view.

```
TBItem *myTBItem = placement.listOfItems[currItemIndex];

if (myTBItem != nil) {
	[self.view addSubview:[myTBItem thumbnailView]];
	[self.view addSubview:[myTBItem titleView]];

	TBBrandingLabel *brandingLabel = [myTBItem brandingView]; 
	if (brandingLabel != nil){
		[self.view addSubview:brandingLabel];
	}
	
	TBDescriptionLabel *descriptionLabel = [myTBItem descriptionView]; 
	if (descriptionLabel != nil){
		[self.view addSubview:descriptionLabel];
	}
}

```


### 1.7. Supply your own implementation of the attribution view
Taboola widgets should have an attribution/disclosure UI element on their top or bottom.
This UI element usually includes some variation of the text "By Taboola" or "Sponsored content" and optinally the Taboola logo. It's the responsibilty of the app developer to add this UI element. Consult your Taboola account manager regarding what should be placed in your application.

Clicks on this UI element should be handled by Taboola, for that call `handleAttributionClick` every time this view is clicked by the user

```
[[TaboolaApi sharedInstance] handleAttributionClick]
```

### 1.8 Request next batch of the recommendations for placement
Used for implementing pagination or infinite scroll (load more items as the user scrolls down). The method gets the next batch of recommendation items for a specified placement. The name of the returned placement will have a "counter" added as a suffix. For example, if the original placement name was "article" the new name will be "article 1", next one "article 2", and so on. The counter is incremented on each successful fetch.


```
// Get extra 3 items for an existing placement
[[TaboolaApi sharedInstance] getNextBatchForPlacement:placement itemsCount:3 onSuccess:^(TBRecommendationResponse *response) {
		// onSuccess: add those extra items on screen
		// keep the response placements in case you'll need to get more items for these placments.
    
    } onFailure:^(NSError *error) {
    	// handle errors
    }];

```


### 1.9. Intercepting recommendation clicks

TaboolaApi, by default, will try to open clicks in `SFSafariViewController`.
On older iOS versions, where `SFSafariViewController` is not supported, the clicks will be opened in an in-app browser window.

TaboolaApi allows app developers to intercept recommendation clicks in order to create a click-through or to override the default way of opening the recommended article. For example, for opening organic items as a deeplink into the relevant app screen instead of showing it as a web content.

In order to intercept clicks, you should implement the `TaboolaApiClickDelegate` and set it in the sdk.

For example, you may choose to implement `TaboolaApiClickDelegate` in your view controller

```
@interface MyViewController () <TaboolaApiClickDelegate>
.
.
.
@implementation MyViewController
.
.
.
#pragma mark - TaboolaApiClickDelegate

- (BOOL)onItemClick:(NSString *)placemetName withItemId:(NSString *)itemId withClickUrl:(NSString *)clickUrl isOrganic:(BOOL)organic {

	 // Write click handling code here
    return true;
}

```

Set the delegate correctly on the TaboolaApi SharedInstance:

```   
[TaboolaApi sharedInstance].clickDelegate = self;
```

The `onItemClick` method will be called every time a user clicks a recommendation, right before triggering the default behavior. You can block default click handling for organic items by returning `false`.

* Return **`false`** - abort the default behavior, the app should display the recommendation content on its own (for example, using an in-app browser). **NOTICE: Aborts only for organic items!**
* Return **`true`** - this will allow the app to implement a click-through and continue to the default behaviour.

`isOrganic` indicates whether the item clicked was an organic content recommendation or not.

**Best practice would be to suppress the default behavior for organic items, and instead open the relevant screen in your app which shows that content.**

## 2. Example App
This repository includes an example Android app which uses the `TaboolaApi`.

## 4. SDK Reference
[TaboolaApi Reference](doc/TaboolaApi_reference.md)

## 5. License
This program is licensed under the Taboola, Inc. SDK License Agreement (the “License Agreement”).  By copying, using or redistributing this program, you agree to the terms of the License Agreement.  The full text of the license agreement can be found at [https://github.com/taboola/taboola-ios-api/blob/master/LICENSE](https://github.com/taboola/taboola-ios-api/blob/master/LICENSE).
Copyright 2017 Taboola, Inc.  All rights reserved.
