//
//  GoogleAuthViewController.h
//  ColiSDK_Runner
//
//  Created by 林观鸿 on 2019/11/17.
//  Copyright © 2019 林观鸿. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface GoogleAuthViewController : UIViewController<UINavigationControllerDelegate, UIImagePickerControllerDelegate>

- (IBAction)onGoogleLogin:(id)sender;
- (IBAction)onGoogleLogout:(id)sender;

- (IBAction)onFacebookLogin:(id)sender;
- (IBAction)onFacebookLogout:(id)sender;

- (IBAction)onPayment6:(id)sender;
- (IBAction)onFBShare:(id)sender;

- (IBAction)appLinkTapped:(UIButton *)sender;
- (IBAction)onVibrate:(id)sender;

@end

NS_ASSUME_NONNULL_END
