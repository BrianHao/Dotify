/*******************/
/** DOTIFY_DRIVER **/
/*******************/
// A Dotify Driver contains an instance of a Library and an instance of a Playlist Driver
// It also provides an interface to interact with both systems.

#ifndef DOTIFYDRIVER_H
#define DOTIFYDRIVER_H

#include "Library.h"
#include "PlaylistDriver.h"
using namespace std;

class DotifyDriver {
public:
    // Constructor and Destructor
    DotifyDriver() {};
    ~DotifyDriver() {};
    
    // Library commands
    void addSongToLibrary(shared_ptr<LibrarySong> inSong) {
        dotLibrary.addSong(inSong); };
    void removeSongFromLibrary(unsigned int identifier) {
        dotLibrary.removeSong(identifier); };
    void playLibrarySong(unsigned int identifier, unsigned int numTimesPlayed) {
        dotLibrary.playSong(identifier, numTimesPlayed); };
    vector<shared_ptr<LibrarySong>> getSortedLibrary(string sortCategory) {
        return dotLibrary.sortLibrary(sortCategory); };
    bool libContains(unsigned int identifier) {
        return dotLibrary.contains(identifier); };
    shared_ptr<LibrarySong> getLibSong(unsigned int identifier) {
        return dotLibrary.getLibSong(identifier); };
    bool libIsEmpty() { return dotLibrary.empty(); };
    vector<shared_ptr<LibrarySong>> agLibrary(string query, string category) { return dotLibrary.agLibrary(query, category); };
    
    // Playlist commands
    void addPlaylist(shared_ptr<Playlist> inPlaylist) {
        dotPlaylistDriver.addPlaylist(inPlaylist); };
    void removePlaylist(string title) {
        dotPlaylistDriver.removePlaylist(title); };
    void renamePlaylist(string curTitle, string newTitle) {
        dotPlaylistDriver.renamePlaylist(curTitle, newTitle); };
    void addSongToPlayList(string title, shared_ptr<LibrarySong> inSong) {
        dotPlaylistDriver.addSongToPlaylist(title, inSong); };
    void removeSongFromPlayList(string title, unsigned int identifier) {
        dotPlaylistDriver.removeSongFromPlaylist(title, identifier); };
    void ratePlaylist(string title, unsigned int inRating) {
        dotPlaylistDriver.ratePlaylist(title, inRating); };
    vector<shared_ptr<LibrarySong>> getListOfSongsInPlaylist(string title) {
        return dotPlaylistDriver.getListOfSongsInPlaylist(title); };
    vector<shared_ptr<Playlist>> getListOfPlaylistsSorted() {
        return dotPlaylistDriver.getListOfPlaylistsSorted(); };
    vector<string> playlistsContainingSong(unsigned int identifier) {
        return dotPlaylistDriver.playlistsContainingSong(identifier); };
    bool containsPlaylistWithName(string title) { return dotPlaylistDriver.contains(title); };
    bool isEmpty(string title) { return dotPlaylistDriver.isEmpty(title); };
    
private:
    Library dotLibrary;
    PlaylistDriver dotPlaylistDriver;
};

#endif
