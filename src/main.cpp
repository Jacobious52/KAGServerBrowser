#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024, 614, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}


/*-----------------------------------TODO---------------------------------

        {Try fix loading avatars..}
        cache images
 
        {chat log}
        async telnet to server ip:port
 
        {pretty things up.}
        optimize
        use smaller images for less memory footprint
 
        {async single reload in KServer}

 

-------------------------------------------------------------------------*/