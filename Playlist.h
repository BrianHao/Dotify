#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include <memory>
#include "Song.h"
#include "Library.h"
#include "LibrarySong.h"
using namespace std;

class Playlist {
public:
    // Constructor and Destructor
    Playlist(string inPlaylistName = "", unsigned int inPlaylistRating = 1) :
        myName(inPlaylistName), myRating(inPlaylistRating) {};
    ~Playlist() {};
    
    // Getters and Setters
    string getName() { return myName; };
    void setName(string inName) { myName = inName; };
    unsigned int getRating() { return myRating; };
    void setRating(unsigned int inRating) { myRating = inRating; };
    unsigned int numSongs() { return myPlaylist.size(); };
    vector<shared_ptr<LibrarySong>> getVector() { return myPlaylistVec; };
    bool contains(unsigned int identifier) { return myPlaylist.count(identifier) == 1; };
    string toExportFormat() { return myName + "|" + to_string(myRating)+ "|" + to_string(numSongs()); };
    
    // Add and remove songs
    void addSong(shared_ptr<LibrarySong> inSong) {
        myPlaylist.insert({inSong->getIdentifier(), inSong}); myPlaylistVec.push_back(inSong); };
    void removeSong(unsigned int identifier);
    
    // Comparator
    // Returns the comparison of two playlists by rating, then name
    struct playlistComparator {
        bool operator()(shared_ptr<Playlist> leftPlaylist, shared_ptr<Playlist> rightPlaylist) {
            if (leftPlaylist->getRating() == rightPlaylist->getRating()) {
                return leftPlaylist->getName() < rightPlaylist->getName();
            }
            return leftPlaylist->getRating() > rightPlaylist->getRating();
        }
    };
    
private:
    unordered_map<unsigned int, shared_ptr<LibrarySong>> myPlaylist;
    vector<shared_ptr<LibrarySong>> myPlaylistVec;
    string myName = "";
    unsigned int myRating = 1;
    
};

#endif
