#ifndef LIBRARYSONG_CPP
#define LIBRARYSONG_CPP

#include "LibrarySong.h"
using namespace std;
const string DELIM = "|";

unsigned int LibrarySong::createIdentifier(string inString) {
    unsigned int identifier = 0;
    
    for (int i = 0; i < inString.size(); i++) {
        identifier += inString[i]*(i+1);
    }
    
    return identifier;
}

string LibrarySong::toLibraryExportFormat() {
    string expFormat = "";
    
    expFormat = libSong->getSongName() + DELIM + libSong->getSongArtist() + DELIM + libSong->getSongAlbum() +
        DELIM + to_string(numberOfPlays) + DELIM + to_string(identifier);
    
    return expFormat;
}

string LibrarySong::toPlaylistExportFormat() {
    string expFormat = "";
    
    expFormat = libSong->getSongName() + DELIM + libSong->getSongArtist() + DELIM + libSong->getSongAlbum();
    
    return expFormat;
}

#endif
