// The main.cpp's only function will be to create an instance of a DotifyApp,
// and then call DotifyApp.run()

#include <iostream>
#include "DotifyApp.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // New instance of Dotify App
    DotifyApp myDotifyApp;
    
    // Runs Dotify, passing along any commandline arguments for loading
    myDotifyApp.run(argc, argv);
    
    return 0;
}
