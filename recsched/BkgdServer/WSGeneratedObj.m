/*-
 * WSGeneratedObj.m
 *
 *  Version 0.11
 *
 * This class was automatically generated by WSMakeStubs, part of the
 * WebServicesCore framework.
 * It implements a generic object layer on top of the primitive WebServicesCore API.
 *
 */

#include "WSGeneratedObj.h"

@implementation WSGeneratedObj

- (id)init
{
  if ((self = [super init]) != NULL) {
    fRef = NULL;
    fResult = NULL;
    fAsyncTarget = NULL;
    fAsyncSelector = NULL;
                fParams = NULL;
                fParamOrder = NULL;
  }
  return self;
}

- (void) dealloc
{
  if (fRef) {
    CFRelease(fRef);
    fRef = NULL;
  }
  [fResult release];
  fResult = NULL;
        [fParams release];
        fParams = NULL;
        [fParamOrder release];
        fParamOrder = NULL;
  [super dealloc];
}

- (void) gotResults:(CFDictionaryRef) outRef
{
  if (fResult == NULL)
    fResult = [(NSDictionary*) outRef retain];

  id target = fAsyncTarget;
  SEL sel = fAsyncSelector;

  fAsyncTarget = NULL;
  fAsyncSelector = NULL;

  if (target != NULL) {
    [target performSelector:sel withObject: self];
  }
}


static void __async_callback(WSMethodInvocationRef invocation, void* info, CFDictionaryRef outRef)
{
  WSGeneratedObj* obj = info;
  if (obj) {
    [obj gotResults: outRef];
    CFRelease(outRef);
  }
}


  // Return (possibly creating) the WSMethodInvocationRef
- (WSMethodInvocationRef) getRef
{
  if (fRef == NULL)
    fRef = [self genCreateInvocationRef];
  return fRef;
}

  // Return the Result object.  If it hasn't
  // been fetched yet, this will asynchronously block
- (NSDictionary*) getResultDictionary
{
  if (fResult == NULL) {
    if (fAsyncTarget != NULL) {
      fAsyncTarget = NULL;
      fAsyncSelector = NULL;
    }

    if (fResult == NULL) {
      WSMethodInvocationRef invocation = [self getRef];
      CFStringRef wsGeneratedMode = CFSTR("NS-WSSYNC");

      WSMethodInvocationScheduleWithRunLoop(invocation, CFRunLoopGetCurrent(), wsGeneratedMode);

      while (fResult == NULL)
        CFRunLoopRunInMode(wsGeneratedMode, -1.0, true);

      WSMethodInvocationUnscheduleFromRunLoop(invocation, CFRunLoopGetCurrent(), wsGeneratedMode);
    }

    if (fResult == NULL) {
      [self handleError:@"WSMethodInvocationInvoke failed in getResultDictionary" errorString:NULL errorDomain:kCFStreamErrorDomainMacOSStatus errorNumber:paramErr];
    }
  }
  return fResult;
}

  // Reset the invocation.  The next attempt to get the
  // value will re-issue the request
- (void) reset
{
  if (fResult) {
    [fResult autorelease];
    fResult = NULL;
  }
}

  // Returns true if the Result is a fault
- (BOOL) isFault
{
  NSDictionary* rr = [self getResultDictionary];
  if (rr == NULL)
    return false;
  return WSMethodResultIsFault((CFDictionaryRef) rr);
}

  // Check if the invocation is complete - that is,
  // if it will not re-issue the request to get the result.
- (BOOL) isComplete
{
  return fResult != NULL;
}

  // Returns the return Value associated with this method.
- (id) getValue
{
  return [[self getResultDictionary] objectForKey: (id) kWSMethodInvocationResult];
}


- (void) handleError:(NSString*) stubError errorString:(NSString*) errorString errorDomain:(int) errorDomain errorNumber:(int) errorNumber
{
  NSLog(@"WSGeneratedObj handleError:\n -> %@\n -> %@\n -> %d / %d", stubError, errorString, errorDomain, errorNumber);
}

  // Utility function to set the parameter list for the invocation
- (void) setParameters:(int) count values:(id*) values names:(NSString**) names
{
  fParams = [[NSDictionary alloc] initWithObjects:values forKeys: names count: count];
  fParamOrder = [[NSArray alloc] initWithObjects: names count: count];
}

- (NSDictionary*) copyHeaderDictionary:(int) count extraVals: (NSString**) extraVals extraKeys: (NSString**) extraKeys
{
  return [[NSDictionary dictionaryWithObjects:extraVals forKeys: extraKeys count: count] retain];
}

  // Utility function called by the generated code to create the invocation
- (WSMethodInvocationRef) createInvocationRef:(NSString*) endpoint
                   methodName:(NSString*) methodName
                   protocol:(NSString*) protocol
                    style:(NSString*) style
                   soapAction:(NSString*) soapAction
                methodNamespace:(NSString*) methodNamespace
{
  WSMethodInvocationRef ref = NULL;
  NSURL* url = [NSURL URLWithString: endpoint];
  if (url == NULL) {
    [self handleError: @"NSURL URLWithString failed in createInvocationRef" errorString:NULL errorDomain:kCFStreamErrorDomainMacOSStatus errorNumber: paramErr];
  } else {
    ref = WSMethodInvocationCreate((CFURLRef) url, (CFStringRef) methodName, (CFStringRef) protocol);

    if (ref == NULL)
      [self handleError: @"WSMethodInvocationCreate failed in createInvocationRef" errorString:NULL errorDomain:kCFStreamErrorDomainMacOSStatus errorNumber: paramErr];
    else {
      WSMethodInvocationSetProperty(ref, kWSSOAPBodyEncodingStyle, style);

      NSString* soapActionStr = @"SOAPAction";
      NSDictionary* headers = [self copyHeaderDictionary:1 extraVals:&soapAction extraKeys:&soapActionStr];
      WSMethodInvocationSetProperty(ref, kWSHTTPExtraHeaders, headers);
      [headers release];

      WSMethodInvocationSetProperty(ref, kWSSOAPMethodNamespaceURI, methodNamespace);

      WSClientContext context = { 0,
                    (void*) self,
                    (WSClientContextRetainCallBackProcPtr) CFRetain,
                    (WSClientContextReleaseCallBackProcPtr) CFRelease,
                    (WSClientContextCopyDescriptionCallBackProcPtr) CFCopyDescription
      };
      WSMethodInvocationSetCallBack(ref, __async_callback, &context);
    }
  }

  return ref;
}

  // Must be implemented by client
- (WSMethodInvocationRef) genCreateInvocationRef
{
  return NULL;
}

- (void) setCallBack:(id) target selector:(SEL) selector
{
  fAsyncTarget = [target retain];
  fAsyncSelector = selector;
}

- (void) scheduleOnRunLoop:(NSRunLoop*) runloop mode:(NSString*) mode
{
  WSMethodInvocationScheduleWithRunLoop([self getRef], (CFRunLoopRef) runloop, (CFStringRef) mode);
}

- (void) unscheduleFromRunLoop:(NSRunLoop*) runloop mode:(NSString*) mode
{
  WSMethodInvocationUnscheduleFromRunLoop([self getRef], (CFRunLoopRef) runloop, (CFStringRef) mode);
}

@end

