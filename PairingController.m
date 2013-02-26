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

@synthesize deviceFinder, sixController, deviceLabel, controllerLabel, pairButton;

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
	}
	return self;
}
- (void)ps3ControllerDidConnect {
	sixaxisConnected = YES;
	[controllerLabel setStringValue:@"PS3 Sixaxis Controller connected"];
	[self showButton];
}
- (void)ps3ControllerDidDisconnect {
	sixaxisConnected = NO;
	[controllerLabel setStringValue:@"Connect a PS3 Controller (over USB)"];
	[self showButton];
}
- (void)dealloc {
	if (deviceFinder) [deviceFinder release];
	[super dealloc];
}
- (void)showButton {
	[pairButton setHidden:!(ideviceConnected && sixaxisConnected)];
}
- (void)didFindiDevice:(iDevice *)device {
	currentDevice = device;
	[currentDevice retain];
	NSLog(@"\nType: %@\nVersion: %@\nName: %@\nBTAddress: %@", device.type, device.version, device.name, device.btaddr);
	[deviceLabel setStringValue:[NSString stringWithFormat:@"%@ - %@", device.name, device.version]];
	ideviceConnected = YES;
	[pairButton setTitle:[NSString stringWithFormat:@"Pair Controller to %@", [currentDevice.type substringToIndex:([currentDevice.type length] - 3)]]];
	[pairButton setTarget:self];
	[pairButton setAction:@selector(pairDevices)];
	[self showButton];
}
- (IBAction)pairDevices {
	NSLog(@"Pairing devices...");
	[sixController setBluetoothAddress:currentDevice.btaddr];
}

@end
