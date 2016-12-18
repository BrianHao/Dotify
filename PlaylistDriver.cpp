/*********************/
/** PLAYLIST_DRIVER **/
/*********************/
// A Playlist Driver contains an unordered_map of playlist pointers, using its name as the key
// It also contains functions to interface with the map of playlists

#ifndef PLAYLISTDRIVER_CPP
#define PLAYLISTDRIVER_CPP

#include "PlaylistDriver.h"
using namespace std;

// Renames a playlist by removing it and adding a new playlist with the new name
void PlaylistDriver::renamePlaylist(string curTitle, string newTitle) {
    shared_ptr<Playlist> tempPlaylist = playlistMap[curTitle];
    removePlaylist(curTitle);
    tempPlaylist->setName(newTitle);
    addPlaylist(tempPlaylist);
}

// Returns a vector of all the playlists
vector<shared_ptr<Playlist>> PlaylistDriver::getListOfPlaylistsSorted() {
    SortedVector<shared_ptr<Playlist>, Playlist::playlistComparator> sortedVec;
    
    for(auto i : playlistMap){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}

// Returns a vector of all the playlists containing a particular song
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
