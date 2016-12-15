#ifndef DOTIFYAPP_H
#define DOTIFYAPP_H

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include "DotifyDriver.h"
#include "SortedVector.h"
using namespace std;

class DotifyApp {
public:
    // Constructor and Destructor
    DotifyApp() {};
    ~DotifyApp() {};
    
    // Implaments loading from a library and playlist file from the commandline
    void load(int argc, const char * argv[]);
    
    // Runs the Dotify Application
    // Continually receives input from the user and executes the corresponding command
    void run();
    
private:
    // An instsance of the Dotify Driver
    DotifyDriver dotDriver;
    
    // Functionality of the ToDoList App, mapped to input by the user
    void addSong();
    shared_ptr<Song> getSong();
    void removeSong();
    void addPlaylist();
    void removePlaylist();
    void renamePlaylist();
    void autogenerate();
    void addSongToPlaylist();
    void removeSongFromPlaylist();
    void displayLibrarySongs();
    void displayPlaylists();
    void displayPlaylistSongs();
    void ratePlaylist();
    void playSong();
    void exportToFile();
    void help();
    
    // Helper functions
    // Gets an input from the user
    string getInput();
    // Gets a line from the user
    string getLine();
    // Gets an integer from the user
    unsigned int getInt();
    
};

#endif
