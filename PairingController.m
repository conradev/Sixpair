//
//  PairingController.m
//  SixPairMac
//
//  Created by Conrad on 8/20/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "PairingController.h"

static PairingController *sharedInstance;

@implementation PairingController

@synthesize deviceFinder, sixController, deviceLabel, controllerLabel, pairButton, successLabel;

+ (PairingController *)sharedInstance {
	if (!sharedInstance){
		sharedInstance = [[self alloc] init];
	}
	return sharedInstance;
}

- (id)init {
	self = [super init];
	if (self != nil) {
		deviceFinder = [[[iDeviceFinder alloc] init] retain];
		[deviceFinder setDelegate:self];
		[deviceFinder registerForNewDeviceNotifications];
		
		sixController = [[[SixaxisController alloc] init] retain];
		[sixController setDelegate:self];
        
        [self updateButtonVisibility];
	}
	return self;
}
- (void)ps3ControllerDidConnect {
	sixaxisConnected = YES;
	[controllerLabel setStringValue:@"PS3 Sixaxis Controller connected"];
	[self updateButtonVisibility];
}
- (void)ps3ControllerDidDisconnect {
	sixaxisConnected = NO;
    sixaxisPaired = NO;
	[controllerLabel setStringValue:@"Connect a PS3 Controller (over USB)"];
	[self updateButtonVisibility];
}
- (void)dealloc {
	if (deviceFinder) [deviceFinder release];
	[super dealloc];
}
- (void)updateButtonVisibility {
	[pairButton setHidden:!(ideviceConnected && sixaxisConnected && !sixaxisPaired)];
    [successLabel setHidden:!sixaxisPaired];
}
- (void)didFindiDevice:(iDevice *)device {
	currentDevice = device;
	[currentDevice retain];
	NSLog(@"\nType: %@\nVersion: %@\nName: %@\nBTAddress: %@", device.type, device.version, device.name, device.btaddr);
	[deviceLabel setStringValue:[NSString stringWithFormat:@"%@ - %@", device.name, device.version]];
	ideviceConnected = YES;
    sixaxisPaired = NO;
    NSString * deviceType = [currentDevice.type substringToIndex:([currentDevice.type length] - 3)];
	[pairButton setTitle:[NSString stringWithFormat:@"Pair Controller to %@", deviceType]];
	[pairButton setTarget:self];
	[pairButton setAction:@selector(pairDevices)];
    [successLabel setStringValue:[NSString stringWithFormat:@"Controller paired to %@, ENJOY!", deviceType]];
	[self updateButtonVisibility];
}
- (IBAction)pairDevices {
	NSLog(@"Pairing devices...");
	[sixController setBluetoothAddress:currentDevice.btaddr];
    sixaxisPaired = YES;
    [self updateButtonVisibility];
}

@end
