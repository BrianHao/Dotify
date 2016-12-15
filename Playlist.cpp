#ifndef PLAYLIST_CPP
#define PLAYLIST_CPP

#include "Playlist.h"
using namespace std;

void Playlist::removeSong(unsigned int identifier) {
    myPlaylist.erase(identifier);
    
    for (int i = 0; i < myPlaylistVec.size(); i++) {
        if (myPlaylist.at(i)->getIdentifier() == identifier) {
            myPlaylistVec.erase(myPlaylistVec.begin()+i);
            break;
        }
    }
}


#endif

