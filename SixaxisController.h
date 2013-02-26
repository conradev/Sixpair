//
//  SixaxisController.h
//  SixPairMac
//
//  Created by Conrad on 8/20/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <IOKit/hid/IOHIDLib.h>

@protocol SixaxisControllerDelegate <NSObject>

- (void)ps3ControllerDidConnect;
- (void)ps3ControllerDidDisconnect;

@end

@interface SixaxisController : NSObject {
	IOHIDManagerRef hidManagerRef;
	id<SixaxisControllerDelegate> delegate;
}

@property (nonatomic, assign) id<SixaxisControllerDelegate> delegate;

- (void)setBluetoothAddress:(NSString *)address;

@end
