//
//  AppDelegate.m
//  main_osx
//
//  Created by 佟 生悦 on 13-8-20.
//  Copyright (c) 2013年 ld3d. All rights reserved.
//

#import "AppDelegate.h"


#include "MainApp.h"




MainApp*			g_pApp	= nullptr;
@implementation AppDelegate




- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    
    NSSize size;
    
    size.width = 800;
    size.height = 600;
    
    [self.window setContentSize:size];
    
    [self.window center];
    
	
	g_pApp = new MainApp();
	
	g_pApp->Init();

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
