#include <iostream>
#include "DotifyApp.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // New instance of Dotify App
    DotifyApp myDotifyApp;
    
    // Attempts to load from commandline arguments
    myDotifyApp.load(argc, argv);
    
    // Runs Dotify
    myDotifyApp.run();
    
    return 0;
}
