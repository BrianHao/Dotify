/**************/
/** PLAYLIST **/
/**************/
// A Playlist contains an unordered_map of Library Song pointers, using its identifier as the key
// It also catains its own name and rating, as well as functions to interface with the playlist

#ifndef PLAYLIST_CPP
#define PLAYLIST_CPP

#include "Playlist.h"
using namespace std;

// Removes a song with the identifier provided
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

