#ifndef PLAYLISTDRIVER_H
#define PLAYLISTDRIVER_H

#include <vector>
#include <memory>
#include <string>
#include "Playlist.h"
using namespace std;

class PlaylistDriver {
public:
    // Constructor and Destructor
    PlaylistDriver() {};
    ~PlaylistDriver() {};
    
    // Add and remove playlists
    void addPlaylist(shared_ptr<Playlist> inPlaylist) {
        playlistMap.insert({inPlaylist->getName(), inPlaylist}); };
    void removePlaylist(string title) { playlistMap.erase(title); };
    
    // Rename playlist
    void renamePlaylist(string curTitle, string newTitle);
    
    // Add and remove songs
    void addSongToPlaylist(string title, shared_ptr<LibrarySong> inSong) {
        playlistMap[title]->addSong(inSong); };
    void removeSongFromPlaylist(string title, unsigned int identifier) {
        playlistMap[title]->removeSong(identifier);};
    
    // Rate playlist
    void ratePlaylist(string title, unsigned int inRating) {
        playlistMap[title]->setRating(inRating); };
    
    // Return a vector of the list of songs in a specific playlist sorted by order added
    vector<shared_ptr<LibrarySong>> getListOfSongsInPlaylist(string title) {
        return playlistMap[title]->getVector(); };
    
    // Return a vector of playlists sorted by rating then title
    vector<shared_ptr<Playlist>> getListOfPlaylistsSorted();
    
    // Return a vector of strings containing the titles of playlist containing a specific song
    vector<string> playlistsContainingSong(unsigned int identifier);
    
    // Checks if a playlist with a certain name already exists
    bool contains(string title) { return playlistMap.count(title) == 1; };
    
    // Checks if a playlist is empty
    bool isEmpty(string title) { return playlistMap[title]->numSongs() == 0; };
    
private:
    // Map containing playlist pointers
    unordered_map<string, shared_ptr<Playlist>> playlistMap;
};

#endif
