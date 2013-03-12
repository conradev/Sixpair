//
//  PairingController.h
//  SixPairMac
//
//  Created by Conrad on 8/20/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "iDeviceFinder.h"
#import "SixaxisController.h"

@interface PairingController : NSObject <iDeviceFinderDelegate, SixaxisControllerDelegate> {
	iDeviceFinder *deviceFinder;
	iDevice *currentDevice;
	SixaxisController *sixController;
	
	NSTextField   *deviceLabel;
	NSTextField   *controllerLabel;
	NSButton      *pairButton;
	
	BOOL ideviceConnected;
	BOOL sixaxisConnected;
    BOOL sixaxisPaired;
}

@property (nonatomic, retain) iDeviceFinder *deviceFinder;
@property (nonatomic, retain) SixaxisController *sixController;
@property (nonatomic, retain) IBOutlet NSTextField *deviceLabel;
@property (nonatomic, retain) IBOutlet NSTextField *controllerLabel;
@property (nonatomic, retain) IBOutlet NSTextField *successLabel;
@property (nonatomic, retain) IBOutlet NSButton *pairButton;

+ (PairingController *)sharedInstance;

- (IBAction)pairDevices;

@end
