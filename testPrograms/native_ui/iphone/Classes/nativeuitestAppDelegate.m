//
//  nativeuitestAppDelegate.m
//  nativeuitest
//
//  Created by Niklas Nummelin on 11/25/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "nativeuitestAppDelegate.h"
#import "MoSyncUISyscalls.h"

@implementation nativeuitestAppDelegate

const char* labels[] = {
		"alpha",
		"beta",
		"gamma",
		"delta",
		"epsilon",
		"zeta",
		"delta"
};

void TestApp() {
	MAHandle mainScreen = maWidgetCreate("Window");
	MAHandle tableView = maWidgetCreate("TableView");
	maWidgetAddChild(mainScreen, tableView);
	
	for(int i = 0; i < 7; i++) {
		MAHandle tableViewCell = maWidgetCreate("TableViewCell");
		//maWidgetSetProperty(tableViewCell, "text", labels[i]);
		if(i == 3) maWidgetSetProperty(tableViewCell, "backgroundColor", "#00ff00");
		maWidgetAddChild(tableView, tableViewCell);		
		
		MAHandle button = maWidgetCreate("Button");
		maWidgetSetProperty(button, "width", "80");			
		maWidgetSetProperty(button, "text", labels[i]);				
		maWidgetAddChild(tableViewCell, button);
		
		MAHandle label = maWidgetCreate("Label");
		maWidgetSetProperty(label, "left", "80");				
		maWidgetSetProperty(label, "text", labels[i]);		
		maWidgetAddChild(tableViewCell, label);
	
	}
	
	//MAHandle button = maWidgetCreate("UIButton");
	//maWidgetAddChild(tableView, button);
	
	maWidgetScreenShow(mainScreen);	
}

#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
	initMoSyncUISyscalls();
	TestApp();
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}


- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
     [super dealloc];
}


@end
