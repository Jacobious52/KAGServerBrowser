// boo windows
#ifdef _WIN32
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( )
{
	ofSetupOpenGL(1024, 614, OF_WINDOW);			// <-------- setup the GL context

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