#ifndef DOTIFYDRIVER_H
#define DOTIFYDRIVER_H

#include "Library.h"
#include "Playlistdriver.h"
using namespace std;

class DotifyDriver {
public:
    // Constructor and Destructor
    DotifyDriver() {};
    ~DotifyDriver() {};
    
    // Library commands
    void addSongToLibrary(shared_ptr<LibrarySong> inSong) { dotLibrary.addSong(inSong); };
    void removeSongFromLibrary(unsigned int identifier) { dotLibrary.removeSong(identifier); };
    void playLibrarySong(unsigned int identifier, unsigned int numTimesPlayed) { dotLibrary.playSong(identifier, numTimesPlayed); };
    vector<shared_ptr<LibrarySong>> getSortedLibrary(string sortCategory) { return dotLibrary.sortLibrary(sortCategory); };
    //*** TO DO
    //export
    //import
    
    // Playlist commands
    void addPlaylist(shared_ptr<Playlist> inPlaylist) { dotPlaylistDriver.addPlaylist(inPlaylist); };
    void removePlaylist(string title) { dotPlaylistDriver.removePlaylist(title); };
    void renamePlaylist(string curTitle, string newTitle) { dotPlaylistDriver.renamePlaylist(curTitle, newTitle); };
    void addSongToPlayList(string title, shared_ptr<LibrarySong> inSong) { dotPlaylistDriver.addSongToPlaylist(title, inSong); };
    void removeSongFromPlayList(string title, unsigned int identifier) { dotPlaylistDriver.removeSongFromPlaylist(title, identifier); };
    void ratePlaylist(string title, unsigned int inRating) { dotPlaylistDriver.ratePlaylist(title, inRating); };
    vector<shared_ptr<LibrarySong>> getListOfSongsInPlaylist(string title) { return dotPlaylistDriver.getListOfSongsInPlaylist(title); };
    vector<shared_ptr<Playlist>> getListOfPlaylistsSorted() { return dotPlaylistDriver.getListOfPlaylistsSorted(); };
    //*** TO DO
    //autogenerate
    //export
    //import
    
    
private:
    Library dotLibrary;
    PlaylistDriver dotPlaylistDriver;
};

#endif
