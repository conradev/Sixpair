//
//  SixaxisController.m
//  SixPairMac
//
//  Created by Conrad on 8/20/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "SixaxisController.h"

@implementation SixaxisController

@synthesize delegate;

typedef struct	BluetoothDeviceAddress		BluetoothDeviceAddress;
struct	BluetoothDeviceAddress
{
	UInt8		data[ 6 ];
};

static SixaxisController *sharedInstance;

static IOHIDDeviceRef gIOHIDDeviceRef = NULL;

long IOHIDDevice_GetVendorID(IOHIDDeviceRef inIOHIDDeviceRef);
long IOHIDDevice_GetProductID(IOHIDDeviceRef inIOHIDDeviceRef);

static IOReturn Set_DeviceFeatureReport(IOHIDDeviceRef inIOHIDDeviceRef, CFIndex inReportID, void* inReportBuffer, CFIndex inReportSize) {
	
	IOReturn result = paramErr;
	
	if (inIOHIDDeviceRef && inReportSize && inReportBuffer) {
		result = IOHIDDeviceSetReport(inIOHIDDeviceRef, kIOHIDReportTypeFeature, inReportID, inReportBuffer, inReportSize);
		
		if (noErr != result) {
			printf("%s, IOHIDDeviceSetReport error: %ld (0x%08lX ).\n", __PRETTY_FUNCTION__, (long int) result, (long int) result);
		}
	}
	return(result);
}


static IOReturn PS3_SetMasterBluetoothAddress(IOHIDDeviceRef inIOHIDDeviceRef, BluetoothDeviceAddress inBluetoothDeviceAddress) {
	
	printf("%s(%p)\n", __PRETTY_FUNCTION__, inIOHIDDeviceRef);
	
	uint8_t report[8];
	report[0] = 0x01; report[1] = 0x00;
	memcpy(&report[2], &inBluetoothDeviceAddress, sizeof(inBluetoothDeviceAddress));
	return(Set_DeviceFeatureReport(inIOHIDDeviceRef, 0xF5, report, sizeof(report)));
	
}
static void Handle_DeviceMatchingCallback(void* inContext, IOReturn inResult, void* inSender, IOHIDDeviceRef inIOHIDDeviceRef) {
	
	// Device VendorID/ProductID:   0x054C/0x0268   (Sony Corporation)
	long vendorID = IOHIDDevice_GetVendorID(inIOHIDDeviceRef);
	long productID = IOHIDDevice_GetProductID(inIOHIDDeviceRef);
	
	if ((0x054C != vendorID) || (0x0268 != productID)) {
		return;
	}
	NSLog(@"Found PS3 Controller!");
	gIOHIDDeviceRef = inIOHIDDeviceRef;
	if ([sharedInstance delegate] && [[sharedInstance delegate] respondsToSelector:@selector(ps3ControllerDidConnect)]) {
		[[sharedInstance delegate] ps3ControllerDidConnect];
	}
}
static void Handle_RemovalCallback(void* inContext, IOReturn inResult, void* inSender, IOHIDDeviceRef inIOHIDDeviceRef) {
	
	if (gIOHIDDeviceRef == inIOHIDDeviceRef) {
		if ([sharedInstance delegate] && [[sharedInstance delegate] respondsToSelector:@selector(ps3ControllerDidDisconnect)]) {
			[[sharedInstance delegate] ps3ControllerDidDisconnect];
		}
		gIOHIDDeviceRef = NULL;
	}
	
}
- (id)init {
	self = [super init];	
	if (self != nil) {
		hidManagerRef = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
		if (hidManagerRef) {
			IOHIDManagerSetDeviceMatching(hidManagerRef, NULL);
			
			IOHIDManagerRegisterDeviceMatchingCallback(hidManagerRef, Handle_DeviceMatchingCallback, nil);
			IOHIDManagerRegisterDeviceRemovalCallback(hidManagerRef, Handle_RemovalCallback, nil);
			
			// schedule us with the runloop
			IOHIDManagerScheduleWithRunLoop(hidManagerRef, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
			
			IOHIDManagerOpen(hidManagerRef, kIOHIDOptionsTypeNone);
		}
	}
	sharedInstance = self;
	return self;
}
- (void)setBluetoothAddress:(NSString *)address {
	if (!gIOHIDDeviceRef) return;
	
	NSArray *parts = [address componentsSeparatedByString:@":"];
	
	BluetoothDeviceAddress newBTMaster;
	for (int x = 0; (x < [parts count] && x < 6); x++) {
		unsigned value;
		[[NSScanner scannerWithString:[parts objectAtIndex:x]] scanHexInt:&value];
		newBTMaster.data[x] = value;
	}

	PS3_SetMasterBluetoothAddress(gIOHIDDeviceRef, newBTMaster);
}

@end
