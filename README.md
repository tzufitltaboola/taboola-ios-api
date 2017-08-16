# Taboola Native iOS SDK (TaboolaApi)
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
```ruby
pod 'TaboolaSDK'
```

* Swift
```ruby
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

*** TODO FROM HERE ***

```objc
TBRecommendationRequest *recomendationRequest = [TBRecommendationRequest new];
recomendationRequest.sourceType = TBSourceTypeText; //replace this with your page actual source type
recomendationRequest.sourceId = @"my-source-id";  //replace this with your page actual source id
recomendationRequest.sourceUrl = @"http://www.example.com";  //replace this with your page actual source URL
```

Create A `TBPlacementRequest` for each placement (You can do this in your `Activity` or `Fragment` code)

```java
   String placementName = "article";
   int recCount = 5; //  how many recommendations should be returned
   
   TBPlacementRequest placementRequest = new TBPlacementRequest(placementName, recCount)
           .setThumbnailSize(400, 300) // ThumbnailSize is optional
           .setTargetType("mix"); // TargetType is optional
```
Create A `TBRecommendationsRequest` and add all of the previously created `TBPlacementRequest` objects to it

```java
   String pageUrl = "http://example.com";
   String sourceType = "text";
           
   TBRecommendationsRequest recommendationsRequest =
           new TBRecommendationsRequest(pageUrl, sourceType)
                   .setUserReferrer("<UserReferrer>") // optional
                   .setUserUnifiedId("<UnifiedId>") // optional
                   .addPlacementRequest(placementRequest)
                   .addPlacementRequest(placementRequest2)
                   .addPlacementRequest(placementRequest3);
```

(Maximum 12 `TBPlacementRequest` per one `TBRecommendationsRequest`) 

### 1.5. Fetch Taboola recommendations
```java
   TaboolaApi.getInstance().fetchRecommendations(recommendationsRequest, new TBRecommendationRequestCallback() {
       @Override
       public void onRecommendationsFetched(TBRecommendationsResponse response) {
           // map where a Key is the Placements name (you can store it as a member variable for convenience)
           Map<String, TBPlacement> placementsMap = response.getPlacementsMap();
       }
                           
       @Override
       public void onRecommendationsFailed(Throwable throwable) {
           // todo handle error
           Toast.makeText(MainActivity.this, "Failed: " + throwable.getMessage(),
                   Toast.LENGTH_LONG).show();
       }
   });
```

### 1.6. Displaying Taboola recommendations
```java
   TBPlacement placement = placementsMap.get(placementName);
   TBRecommendationItem item = placement.getItems().get(0);
                
   mAdContainer.addView(item.getThumbnailView(MainActivity.this));
   mAdContainer.addView(item.getTitleView(MainActivity.this));
   mAdContainer.addView(item.getBrandingView(MainActivity.this));
```

### 1.7. Supply your own implementation of the attribution view
Attribution view is a view with localized "By Taboola" text and icon.
Call `handleAttributionClick()` every time this view is clicked 
```java
   public void onAttributionClick() {
       TaboolaApi.getInstance().handleAttributionClick(MainActivity.this);
   }
```

### 1.8 Request next batch of the recommendations for placement
Used for implementing pagination or infinite scroll (load more items as the user scrolls down). The method gets the next batch of recommendation items for a specified placement. The name of the returned Placement will have a "counter" added as a suffix. For example, if the original placement name was "article" the new name will be "article 1", next one "article 2", and so on. The counter is incremented on each successful fetch.


```Java
   TaboolaApi.getInstance().getNextBatchForPlacement(mPlacement, optionalCount, new TBRecommendationRequestCallback() {
           @Override
           public void onRecommendationsFetched(TBRecommendationsResponse response) {
               TBPlacement placement = response.getPlacementsMap().values().iterator().next(); // there will be only one placement
               // todo do smth with new the Items
           }

           @Override
           public void onRecommendationsFailed(Throwable throwable) {
               Toast.makeText(MainActivity.this, "Fetch failed: " + throwable.getMessage(),
                       Toast.LENGTH_LONG).show();
           }
 });
```


### 1.9. Intercepting recommendation clicks

The default click behavior of TaboolaWidget is as follows:

* On devices where Chrome custom tab is supported - open the recommendation in a chrome custom tab (in-app)
* Otherwise - open the recommendation in the system default web browser (outside of the app) 

TaboolaApi allows app developers to intercept recommendation clicks in order to create a click-through or to override the default way of opening the recommended article. 

In order to intercept clicks, you should implement the interface `com.taboola.android.api.TaboolaOnClickListener` and set it in the sdk.

```java
   TaboolaApi.getInstance().setOnClickListener(new TaboolaOnClickListener() {
       @Override
       public boolean onItemClick(String placementName, String itemId, String clickUrl, boolean isOrganic) {
           return false;
       }
   });

```

This method will be called every time a user clicks a recommendation, right before triggering the default behavior. You can block default click handling for organic items by returning `false` in `onItemClick()` method.

* Return **`false`** - abort the default behavior, the app should display the recommendation content on its own (for example, using an in-app browser). (Aborts only for organic items!)
* Return **`true`** - this will allow the app to implement a click-through and continue to the default behaviour.

`isOrganic` indicates whether the item clicked was an organic content recommendation or not.
**Best practice would be to suppress the default behavior for organic items, and instead open the relevant screen in your app which shows that piece of content.**

## 2. Example App
This repository includes an example Android app which uses the `TaboolaApi`.

## 4. SDK Reference
[TaboolaApi Reference](doc/TaboolaApi_reference.md)

## 5. License
This program is licensed under the Taboola, Inc. SDK License Agreement (the “License Agreement”).  By copying, using or redistributing this program, you agree to the terms of the License Agreement.  The full text of the license agreement can be found at [https://github.com/taboola/taboola-android/blob/master/LICENSE](https://github.com/taboola/taboola-android/blob/master/LICENSE).
Copyright 2017 Taboola, Inc.  All rights reserved.
