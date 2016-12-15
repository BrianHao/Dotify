#ifndef LIBRARYSONG_CPP
#define LIBRARYSONG_CPP

#include "LibrarySong.h"
using namespace std;

unsigned int LibrarySong::createIdentifier(string inString) {
    unsigned int identifier = 0;
    
    for (int i = 0; i < inString.size(); i++) {
        identifier += inString[i]*(i+1);
    }
    
    return identifier;
}

#endif
