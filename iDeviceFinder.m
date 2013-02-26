//
//  iPhoneSixPair.m
//  SixPairMac
//
//  Created by Conrad on 8/20/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "iDeviceFinder.h"

static iDeviceFinder *sharedInstance;

@implementation iDeviceFinder

@synthesize delegate;

static void device_notification_callback(am_device_notification_callback_info *info, void *foo) {
    if(info->msg != ADNCI_MSG_CONNECTED) return;
	
    AMDeviceConnect(info->dev);
    if (AMDeviceIsPaired(info->dev)) {
		if (!AMDeviceValidatePairing(info->dev)) {
			if (!AMDeviceStartSession(info->dev)) {
			
				am_device *dev = info->dev;
				iDevice *deviceFound = [[iDevice alloc] init];
				deviceFound.type = (NSString *)AMDeviceCopyValue(dev, 0, CFSTR("ProductType"));
				deviceFound.name = (NSString *)AMDeviceCopyValue(dev, 0, CFSTR("DeviceName"));
				deviceFound.version = (NSString *)AMDeviceCopyValue(dev, 0, CFSTR("ProductVersion"));
				deviceFound.btaddr = (NSString *)AMDeviceCopyValue(dev, 0, CFSTR("BluetoothAddress"));
				
				
				if ([sharedInstance delegate] && [[sharedInstance delegate] respondsToSelector:@selector(didFindiDevice:)]) {
					[[sharedInstance delegate] didFindiDevice:deviceFound];
				}
			}
		}
	}
}
- (id)init {
	self = [super init];
	if (self != nil) {
		sharedInstance = self;
	}
	return self;
}

- (int)registerForNewDeviceNotifications {
    am_device_notification *notif;
    return AMDeviceNotificationSubscribe(device_notification_callback, 0, 0, NULL, &notif);	
}

@end
