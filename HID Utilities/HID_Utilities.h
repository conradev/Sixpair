//
//	File:		HID_Utilities.h
//
//	Contains: 	Implementation of the HID configuration utilities
//
//	Copyright:  Copyright (c) 2007 Apple Inc., All Rights Reserved
//
//	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by
//				Apple Inc. ("Apple") in consideration of your agreement to the
//				following terms, and your use, installation, modification or
//				redistribution of this Apple software constitutes acceptance of these
//				terms.  If you do not agree with these terms, please do not use,
//				install, modify or redistribute this Apple software.
//
//				In consideration of your agreement to abide by the following terms, and
//				subject to these terms, Apple grants you a personal, non-exclusive
//				license, under Apple's copyrights in this original Apple software (the
//				"Apple Software"), to use, reproduce, modify and redistribute the Apple
//				Software, with or without modifications, in source and/or binary forms;
//				provided that if you redistribute the Apple Software in its entirety and
//				without modifications, you must retain this notice and the following
//				text and disclaimers in all such redistributions of the Apple Software.
//				Neither the name, trademarks, service marks or logos of Apple Inc.
//				may be used to endorse or promote products derived from the Apple
//				Software without specific prior written permission from Apple.  Except
//				as expressly stated in this notice, no other rights or licenses, express
//				or implied, are granted by Apple herein, including but not limited to
//				any patent rights that may be infringed by your derivative works or by
//				other works in which the Apple Software may be incorporated.
//
//				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE
//				MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
//				THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
//				FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND
//				OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
//
//				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
//				OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//				SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//				INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
//				MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED
//				AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
//				STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE
//				POSSIBILITY OF SUCH DAMAGE.
//
#ifndef __HID_UTILITIES___
#define __HID_UTILITIES___

#if 0000	// Do we need any of this?

//*****************************************************
#pragma mark - includes & imports
//-----------------------------------------------------
#include <AvailabilityMacros.h>

#include "IOHIDLib_.h"
#include "HID_Utilities_External.h"

//*****************************************************
#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_IMPORT
#pragma import on
#endif

#if PRAGMA_STRUCT_ALIGN
#pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
#pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
#pragma pack(2)
#endif

//*****************************************************
#pragma mark - typedef's, struct's, enums, defines, etc.
//-----------------------------------------------------

typedef struct hu_InfoRec_t {
	long actionCookie;
	// device
	struct {
		long vendorID;
		long productID;
		long locID;
		uint32_t usagePage;
		uint32_t usage;
	} device;
	// elements
	struct {
		uint32_t usagePage;
		uint32_t usage;
		long	type;
		void * cookie;
	} element;
} hu_InfoRec_t;

//*****************************************************
#pragma mark - exported globals
//-----------------------------------------------------

extern IOHIDManagerRef gIOHIDManagerRef;
extern CFMutableArrayRef gDeviceCFArrayRef;
extern CFArrayRef gElementCFArrayRef;

//*****************************************************
#pragma mark - exported function prototypes
//-----------------------------------------------------

//*************************************************************************
//
// HIDBuildMultiDeviceList( inUsagePages, inUsages, inNumDeviceTypes )
//
// Purpose:	builds list of devices with elements
//
// Inputs:	inUsagePages		- inNumDeviceTypes sized array of matching usage pages
//			inUsages			- inNumDeviceTypes sized array of matching usages
//			inNumDeviceTypes	- number of usage pages & usages
//
// Returns:	Boolean				- if successful
//
extern Boolean HIDBuildMultiDeviceList( UInt32 inUsagePages[], UInt32 inUsages[], UInt32 inNumDeviceTypes );

//*************************************************************************
//
// HIDRebuildDevices(  )
//
// Purpose:	rebuilds the (internal) list of IOHIDDevices
//
// Inputs:	none
//
// Returns:	none
//

extern void HIDRebuildDevices( void );

//*************************************************************************
//
// HIDConfigureAction( outDeviceRef, outElementRef, inTimeout )
//
// Purpose:	polls all devices and elements for a change greater than kPercentMove.
//			Times out after given time returns 1 and pointer to device and element
//			if found; returns 0 and NULL for both parameters if not found
//
// Inputs:	outDeviceRef	- address where to store the device
//			outElementRef	- address where to store the element
//			inTimeout	- the timeout
// Returns:	Boolean		- if successful
//			outDeviceRef	- the device
//			outElementRef	- the element
//

extern Boolean HIDConfigureAction( IOHIDDeviceRef* outDeviceRef, IOHIDElementRef *outElementRef, float inTimeout );

//*************************************************************************
//
// HIDSaveElementPref( inKeyCFStringRef, inAppCFStringRef, inDeviceRef, inElementRef )
//
// Purpose:	Save the device & element values into the specified key in the specified applications preferences
//
// Inputs:	inKeyCFStringRef	- the preference key
//			inAppCFStringRef	- the application identifier
//			inDeviceRef			- the device
//			inElementRef			- the element
// Returns:	Boolean				- if successful
//

extern Boolean HIDSaveElementPref( const CFStringRef inKeyCFStringRef,
	CFStringRef inAppCFStringRef,
	IOHIDDeviceRef inDeviceRef,
	IOHIDElementRef inElementRef );

//*************************************************************************
//
// HIDRestoreElementPref( inKeyCFStringRef, inAppCFStringRef, outDeviceRef, outElementRef )
//
// Purpose:	Find the specified preference in the specified application
//
// Inputs:	inKeyCFStringRef	- the preference key
//			inAppCFStringRef	- the application identifier
//			outDeviceRef		- address where to restore the device
//			outElementRef		- address where to restore the element
// Returns:	Boolean				- if successful
//			outDeviceRef		- the device
//			outElementRef		- the element
//

extern Boolean HIDRestoreElementPref( CFStringRef inKeyCFStringRef,
	CFStringRef inAppCFStringRef,
	IOHIDDeviceRef*outDeviceRef,
	IOHIDElementRef *outElementRef );

//*************************************************************************
//
// HIDFindDeviceAndElement( inSearchInfo, outFoundDevice, outFoundElement )
//
// Purpose:	find the closest matching device and element for this action
//
// Notes:	matches device: serial, vendorID, productID, location, inUsagePage, usage
//			matches element: cookie, inUsagePage, usage,
//
// Inputs:	inSearchInfo	- the device & element info we searching for
//			outFoundDevice	- the address of the best matching device
//			outFoundElement	- the address of the best matching element
//
// Returns:	Boolean			- TRUE if we find a match
//			outFoundDevice	- the best matching device
//			outFoundElement	- the best matching element
//

extern Boolean HIDFindDeviceAndElement( const hu_InfoRec_t* inSearchInfo,
	IOHIDDeviceRef* outFoundDevice,
	IOHIDElementRef *outFoundElement );

//*************************************************************************
//
// HIDCopyUsageName( inUsagePage, inUsage )
//
// Purpose:	return a CFStringRef string for a given usage page & usage( see IOUSBHIDParser.h )
//
// Notes:	returns usage page and usage values in CFString form for unknown values
//
// Inputs:	inUsagePage	- the usage page
//			inUsage		- the usage
//
// Returns:	CFStringRef	- the resultant string
//

extern CFStringRef HIDCopyUsageName( long inUsagePage, long inUsage );

// utility routines to dump device or element info
extern void HIDDumpDeviceInfo( IOHIDDeviceRef inIOHIDDeviceRef );
extern void HIDDumpElementInfo( IOHIDElementRef inIOHIDElementRef );

//*****************************************************
#if PRAGMA_STRUCT_ALIGN
#pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
#pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
#pragma pack()
#endif

#ifdef PRAGMA_IMPORT_OFF
#pragma import off
#elif PRAGMA_IMPORT
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif

#endif	// 0000	// Do we need any of this?

#endif  // __HID_UTILITIES___
