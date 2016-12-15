// Library Song
// Wrapper class for Song

#ifndef LIBRARYSONG_H
#define LIBRARYSONG_H

#include <memory>
#include "Song.h"
using namespace std;

class LibrarySong {
public:
    // Constructor and Destructor
    LibrarySong(shared_ptr<Song> inLibSong = 0) : libSong(inLibSong) {};
    ~LibrarySong() {};
    
    // Setters and Getters
    string getSongName() { return libSong->getSongName(); };
    string getSongArtist() { return libSong->getSongArtist(); };
    string getSongAlbum() { return libSong->getSongAlbum(); };
    shared_ptr<Song> getSong() { return libSong; };
    void playSong(unsigned int inNumTimesPlayed) { numberOfPlays += inNumTimesPlayed; };
    unsigned int getNumPlays() { return numberOfPlays; };
    unsigned int getIdentifier() { return identifier; };
    
    // Comparators
    // Returns the comparison of two LibrarySongs by different categories
    struct LibSongNameComparator {
        bool operator()(shared_ptr<LibrarySong> leftSong, shared_ptr<LibrarySong> rightSong) {
            return leftSong->getSongName() < rightSong->getSongName();
        }
    };
    struct LibSongArtistComparator {
        bool operator()(shared_ptr<LibrarySong> leftSong, shared_ptr<LibrarySong> rightSong) {
            return leftSong->getSongArtist() < rightSong->getSongArtist();
        }
    };
    struct LibSongAlbumComparator {
        bool operator()(shared_ptr<LibrarySong> leftSong, shared_ptr<LibrarySong> rightSong) {
            return leftSong->getSongAlbum() < rightSong->getSongAlbum();
        }
    };
    struct LibSongPlaysComparator {
        bool operator()(shared_ptr<LibrarySong> leftSong, shared_ptr<LibrarySong> rightSong) {
            return leftSong->getNumPlays() < rightSong->getNumPlays();
        }
    };
    
private:
    // Pointer to a Song
    shared_ptr<Song> libSong;
    
    // Private Library Song Variables
    unsigned int numberOfPlays = 0;
    unsigned int identifier = createIdentifier(getSongName() + getSongArtist() + getSongAlbum());
    unsigned int createIdentifier(string inString);
};

#endif
