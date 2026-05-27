//
//  AppDelegate.m
//  ColiSDK_Runner
//
//  Created by 林观鸿 on 2019/11/16.
//  Copyright © 2019 林观鸿. All rights reserved.
//

#import "AppDelegate.h"
#import <ColiSDK/ColiSDK.h>

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    [[ColiSDK sharedInstance] application:application didFinishLaunchingWithOptions:launchOptions];
    [[ColiSDKMessaging sharedInstance] application:application didFinishLaunchingWithOptions:launchOptions];
    [[ColiSDKPayment sharedInstance] start];
    return YES;
}

- (void)applicationWillTerminate:(UIApplication *)application {
    [[ColiSDKPayment sharedInstance] end];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    
}

#pragma mark - UISceneSession lifecycle


- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options {
    // Called when a new scene session is being created.
    // Use this method to select a configuration to create the new scene with.
    return [[UISceneConfiguration alloc] initWithName:@"Default Configuration" sessionRole:connectingSceneSession.role];
}


- (void)application:(UIApplication *)application didDiscardSceneSessions:(NSSet<UISceneSession *> *)sceneSessions {
    // Called when the user discards a scene session.
    // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
    // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
}

- (BOOL)application:(UIApplication *)application
              openURL:(NSURL *)url
    sourceApplication:(NSString *)sourceApplication
           annotation:(id)annotation {
  return [[ColiSDK sharedInstance] openURL:url options:nil];
}

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
    return [[ColiSDK sharedInstance] openURL:url options:options];
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
    return [[ColiSDK sharedInstance] openURL:url options:nil];
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
    [[ColiSDKMessaging sharedInstance] application:application didReceiveRemoteNotification:userInfo];
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    [[ColiSDKMessaging sharedInstance] application:application didReceiveRemoteNotification:userInfo fetchCompletionHandler:completionHandler];
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    [[ColiSDKMessaging sharedInstance] application:application didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
    [[ColiSDKMessaging sharedInstance] application:application didFailToRegisterForRemoteNotificationsWithError:error];
}

- (void)applicationWillEnterForeground:(UIApplication *)application{
    [[ColiSDKMessaging sharedInstance] applicationWillEnterForeground:application];
}

@end
