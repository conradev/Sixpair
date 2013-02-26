//
//  iDevice.h
//  SixPairMac
//
//  Created by Conrad on 8/20/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface iDevice : NSObject {
	NSString *btaddr;
	NSString *name;
	NSString *type;
	NSString *version;
}

@property (nonatomic, retain) NSString *btaddr;
@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *type;
@property (nonatomic, retain) NSString *version;

@end
