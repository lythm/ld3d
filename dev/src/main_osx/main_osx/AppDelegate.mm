//
//  AppDelegate.m
//  main_osx
//
//  Created by 佟 生悦 on 13-8-20.
//  Copyright (c) 2013年 ld3d. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "AppDelegate.h"


#include "MainApp.h"


NSTimer*			g_pTimer;

MainApp*			g_pApp	= nullptr;
@implementation AppDelegate



- (void)timerFired:(id)sender
{
    // It is good practice in a Cocoa application to allow the system to send the -drawRect:
    // message when it needs to draw, and not to invoke it directly from the timer.
    // All we do here is tell the display it needs a refresh
    
	[self.window update];
}




- (void)applicationWillUpdate:(NSNotification *)aNotification
{
	if(g_pApp)
		g_pApp->Update();
}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    
	
	g_pTimer = [NSTimer timerWithTimeInterval:1.0f/60.0f   //a 1ms time interval
										  target:self
										selector:@selector(timerFired:)
										userInfo:nil
										 repeats:YES];
	
    [[NSRunLoop currentRunLoop] addTimer:g_pTimer
								 forMode:NSDefaultRunLoopMode];
  	
	
    NSSize size;
    
    size.width = 800;
    size.height = 600;
    
    [self.window setContentSize:size];
    
    [self.window center];
    
	
	g_pApp = new MainApp();
	
	if(false == g_pApp->Init((__bridge void*)self.window))
	{
		exit(0);
	}
}

-(void)applicationWillTerminate:(NSNotification *)notification
{
	g_pApp->Release();
    
}
-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}
@end
