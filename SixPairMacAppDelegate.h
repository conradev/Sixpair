//
//  SixPairMacAppDelegate.h
//  SixPairMac
//
//  Created by Conrad on 8/20/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "PairingController.h"

@interface SixPairMacAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
	PairingController *pairingController;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet PairingController *pairingController;

@end
