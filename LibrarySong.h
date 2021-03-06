/******************/
/** LIBRARY_SONG **/
/******************/
// Wrapper class for Song, contains a Song pointer and its identifier and number of plays

#ifndef LIBRARYSONG_H
#define LIBRARYSONG_H

#include <memory>
#include "Song.h"
using namespace std;

class LibrarySong {
public:
    // Constructor and Destructor
    LibrarySong(shared_ptr<Song> inLibSong = 0, unsigned int inNumPlays = 0) :
        libSong(inLibSong), numberOfPlays(inNumPlays) {};
    ~LibrarySong() {};
    
    // Setters and Getters
    string getSongName() { return libSong->getSongName(); };
    string getSongArtist() { return libSong->getSongArtist(); };
    string getSongAlbum() { return libSong->getSongAlbum(); };
    shared_ptr<Song> getSong() { return libSong; };
    unsigned int getNumPlays() { return numberOfPlays; };
    unsigned int getIdentifier() { return identifier; };
    
    // Plays the song a number of times
    void playSong(unsigned int inNumTimesPlayed) { numberOfPlays += inNumTimesPlayed; };
    
    // Returns itself in the export file format
    string toLibraryExportFormat();
    string toPlaylistExportFormat();
    
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
            return leftSong->getNumPlays() > rightSong->getNumPlays();
        }
    };
    struct LibSongIdentifierComparator {
        bool operator()(shared_ptr<LibrarySong> leftSong, shared_ptr<LibrarySong> rightSong) {
            return leftSong->getIdentifier() < rightSong->getIdentifier();
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
