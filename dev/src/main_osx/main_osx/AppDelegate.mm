//
//  AppDelegate.m
//  main_osx
//
//  Created by 佟 生悦 on 13-8-20.
//  Copyright (c) 2013年 ld3d. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    
    NSSize size;
    
    size.width = 800;
    size.height = 600;
    
    [self.window setContentSize:size];
    
    [self.window center];
    

}

-(void)applicationWillTerminate:(NSNotification *)notification
{
    
}
-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}
@end
