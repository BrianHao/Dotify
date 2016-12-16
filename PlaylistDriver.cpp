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

vector<string> PlaylistDriver::playlistsContainingSong(unsigned int identifier) {
    vector<string> playlistsContainingSong;
    
    // Iterate through playlists
    // If playlist contains song, add the name of that playlist to the vector
    for(auto i : playlistMap){
        if (i.second->contains(identifier)) {
            playlistsContainingSong.push_back(i.second->getName());
        }
    }
    
    return playlistsContainingSong;
}

#endif
