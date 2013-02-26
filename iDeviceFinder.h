//
//  iPhoneSixPair.h
//  SixPairMac
//
//  Created by Conrad on 8/20/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "mobiledevice.h"
#import "iDevice.h"

@protocol iDeviceFinderDelegate <NSObject>

- (void)didFindiDevice:(iDevice *)device;

@end

@interface iDeviceFinder : NSObject {
	id<iDeviceFinderDelegate> delegate;
}

@property (nonatomic, assign) id<iDeviceFinderDelegate> delegate;

- (int)registerForNewDeviceNotifications;

@end
