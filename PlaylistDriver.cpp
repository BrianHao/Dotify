#ifndef PLAYLISTDRIVER_CPP
#define PLAYLISTDRIVER_CPP

#include "PlaylistDriver.h"
using namespace std;

void PlaylistDriver::renamePlaylist(string curTitle, string newTitle) {
    shared_ptr<Playlist> tempPlaylist = playlistMap[curTitle];
    removePlaylist(curTitle);
    tempPlaylist->setName(newTitle);
    addPlaylist(tempPlaylist);
}

vector<shared_ptr<Playlist>> PlaylistDriver::getListOfPlaylistsSorted() {
    SortedVector<shared_ptr<Playlist>, Playlist::playlistComparator> sortedVec;
    
    for(auto i : playlistMap){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}


#endif
