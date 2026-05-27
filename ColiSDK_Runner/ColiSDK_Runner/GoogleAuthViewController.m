//
//  GoogleAuthViewController.m
//  ColiSDK_Runner
//
//  Created by 林观鸿 on 2019/11/17.
//  Copyright © 2019 林观鸿. All rights reserved.
//

#import "GoogleAuthViewController.h"
#import <ColiSDK/ColiSDK.h>
#import <Photos/Photos.h>
#import <AudioToolbox/AudioToolbox.h>
#import "iossupport.h"

@interface GoogleAuthViewController ()

@end

@implementation GoogleAuthViewController
{
    int _vibrateDuration;
    NSTimer* _vibrateTimer;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [[ColiSDK sharedInstance] setPresentingViewController:self];
}

- (void)viewDidAppear:(BOOL)animated {
    
}

- (IBAction)onGoogleLogin:(id)sender {
    ColiSDKAuthGoogleOptions* options = [ColiSDKAuthGoogleOptions
                                         optionsWithClientID: @"930656381843-7b5f18h8mvs3s73rhqaajpr2e5fuis0f.apps.googleusercontent.com"];
    id<ColiSDKAuthDelegate> delegate = [[ColiSDKAuth sharedInstance] getAuth:options];
    [delegate setLoginCallback:^(NSInteger resultCode, NSString* data){
        if (resultCode == kColiSDKAuthCodeSuccess) {
            NSLog(@"Google 登录成功 %@", data);
        } else {
            NSLog(@"Google 登录失败 %@", data);
        }
    }];
    
    if ([delegate hasPreviousLogin] == YES) {
        [delegate restorePreviousLogin];
    } else {
        [delegate login];
    }
}

- (void)onGoogleLogout:(id)sender {
    ColiSDKAuthGoogleOptions* options = [[ColiSDKAuthGoogleOptions alloc] init];
    id<ColiSDKAuthDelegate> delegate = [[ColiSDKAuth sharedInstance] getAuth:options];
    [delegate setLogoutCallback:^{
        NSLog(@"Google 登出");
    }];
    [delegate logout];
}

- (void)onFacebookLogin:(id)sender {
    ColiSDKAuthFacebookOptions* options = [[ColiSDKAuthFacebookOptions alloc] init];
    id<ColiSDKAuthDelegate> delegate = [[ColiSDKAuth sharedInstance] getAuth:options];
    [delegate setLoginCallback:^(NSInteger resultCode, NSString* data){
        if (resultCode == kColiSDKAuthCodeSuccess) {
            NSLog(@"Facebook 登录成功 %@", data);
        } else {
            NSLog(@"Facebook 登录失败 %@", data);
        }
    }];
    [delegate login];
}

- (void)onFacebookLogout:(id)sender {
    ColiSDKAuthFacebookOptions* options = [[ColiSDKAuthFacebookOptions alloc] init];
    id<ColiSDKAuthDelegate> delegate = [[ColiSDKAuth sharedInstance] getAuth:options];
    [delegate setLogoutCallback:^{
        NSLog(@"Facebook 登出");
    }];
    [delegate logout];
}

- (void)onPayment6:(id)sender {
//    [[ColiSDKPayment sharedInstance] setPaymentCallback:^(NSInteger resultCode, NSString *data) {
//        NSLog(@"result %lu %@", resultCode, data);
//    }];
//    [[ColiSDKPayment sharedInstance] paymentWithProductID:@"com.dzproj.pay0001" andExtraParams:@""];
//    [[ColiSDKAds sharedIntance] showRewardedAdWithType:kColiSDKAdTypeFacebook];
    [[ColiSDKAds sharedIntance] showRewardedAdWithType:kColiSDKAdTypeGoogle];
}

- (void)onFBShare:(id)sender {
//    [self savePhoto];
    id<ColiSDKRewardedAdProtocol> rewardAd = [[ColiSDKAds sharedIntance] loadRewardedAdWithType:kColiSDKAdTypeFacebook withUnitId:@"VID_HD_16_9_15S_APP_INSTALL#335948950767351_335961994099380" withCustomData:@"{\"uid\": \"123\"}"];
//    id<ColiSDKRewardedAdProtocol> rewardAd = [[ColiSDKAds sharedIntance] loadRewardedAdWithType:kColiSDKAdTypeGoogle withUnitId:@"ca-app-pub-3940256099942544/1712485313" withCustomData:@"{\"uid\": \"123\"}"];
    [rewardAd setLoadCallback:^{
        NSLog(@"Load");
        [rewardAd showRewardedAd];
    }];
    
    [rewardAd setCloseCallback:^(BOOL isCompleted) {
        NSLog(@"Close %d", isCompleted);
    }];
    
    [rewardAd setCompleteCallback:^{
        NSLog(@"Completed");
    }];
}

-(NSString *)savePhoto
{
    UIImage * image = [self captureImageFromView:self.view];
    [[ColiSDKShare sharedInstance] facebookShareWithLink:@"www.baidu.com" andPhoto:image andCallback:^(NSInteger resultCode) {

    }];
//    UIImageWriteToSavedPhotosAlbum(image, self, @selector(image:didFinishSavingWithError:contextInfo:), NULL);
    return @"";
}

#pragma mark 系统的完成保存图片的方法
- (void)image: (UIImage *) image didFinishSavingWithError: (NSError *) error contextInfo: (void *) contextInfo
{
    if (error != NULL) {
    } else {
        [[ColiSDKShare sharedInstance] facebookShareWithLink:@"www.baidu.com" andPhoto:image andCallback:^(NSInteger resultCode) {

        }];
    }
}

//截图功能

-(UIImage *)captureImageFromView:(UIView *)view
{
    CGRect screenRect = [view bounds];
    UIGraphicsBeginImageContext(screenRect.size);
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    [view.layer renderInContext:ctx];

    UIImage * image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}

- (IBAction)appLinkTapped:(UIButton *)sender {

    NSLog(@"appLinkTapped");

    UIApplication *app = [UIApplication sharedApplication];
    NSString *path = @"runner://";
    NSURL *ourURL = [NSURL URLWithString:path];
    /*
    if(![app
         canOpenURL:ourURL]){
        path = @"http://watchoverme.parseapp.com/";
        ourURL = [NSURL URLWithString:path];
    }*/

    [app openURL:ourURL];
}

- (void)onVibrate:(id)sender {
    [self vibrate:5000];
}

- (NSString*) toJson:(NSDictionary *)dict {
    NSData *data =  [NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:nil];
    NSString *dataStr = [[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
    return dataStr;
}

-(void) vibrate:(int)duration {
//    _vibrateDuration = duration;
//    _vibrateTimer = [NSTimer scheduledTimerWithTimeInterval:0.01 target:self selector:@selector(doVibrate) userInfo:nil repeats:YES];
//    AudioServicesPlaySystemSound(1520);
//    UIImageJPEGRepresentation()
//    UIImagePickerController* ipc = [[UIImagePickerController alloc] init];
//    ipc.delegate = self;
//    ipc.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
//    ipc.allowsEditing = true;
//    [self presentViewController:ipc animated:YES completion:NULL];
//    [[IosSupport shareIosSupport] pickImageFromPhotoLibrary:^(UIImage* image) {
//        NSLog(@"%@", image);
//    }];
    
    NSLog(@"%@", [[IosSupport shareIosSupport] getCurrentLanguage]);
    
//    NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:@"fda", @"fds", nil];
//    [[ColiSDKAnalysis sharedInstance] addFacebookCustomEvent:@"Common_2" andParams: [self toJson:dict]];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {
    
    UIImage* img = info[UIImagePickerControllerOriginalImage];
    NSLog(@"%@", img);
    NSData* data = UIImageJPEGRepresentation(img, 90);
    NSLog(@"%lu", data.length);
    [picker dismissViewControllerAnimated:YES completion:NULL];
}

-(void)doVibrate {
    AudioServicesPlaySystemSound(1520);
    
    _vibrateDuration -= 10;
    if (_vibrateDuration <= 0) {
        [_vibrateTimer invalidate];
        _vibrateTimer = nil;
    }
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
