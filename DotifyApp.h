#ifndef DOTIFYAPP_H
#define DOTIFYAPP_H

#include <iostream>
#include <string>
#include <memory>
#include "DotifyDriver.h"
#include "SortedVector.h"
using namespace std;

class DotifyApp {
public:
    // Constructor and Destructor
    DotifyApp() {};
    ~DotifyApp() {};
    
    // Runs the Dotify Application
    // Continually receives input from the user and executes the corresponding command
    void run();
    
private:
    // An instsance of the Dotify Driver
    DotifyDriver dotDriver;
    
    // Functionality of the ToDoList App, mapped to input by the user
    void addSong();
    void removeSong();
    void addPlaylist();
    void removePlaylist();
    void renamePlaylist();
    void autogenerate();
    void addSongToPlaylist();
    void removeSongFromPlaylist();
    void displayLibrarySongs();
    void displayPlaylistSongsAlpha();
    void displayPlaylistSongsAdded();
    void ratePlaylist();
    void playSong();
    void exportToFile();
    void help();
    
    // Helper functions
    
    
};

#endif
