#ifndef DOTIFYAPP_CPP
#define DOTIFYAPP_CPP

#include "DotifyApp.h"

using namespace std;

// Implaments loading from a library and playlist file from the commandline
void DotifyApp::load(int argc, const char * argv[]) {
    // No files provided
    if (argc <= 1) {
        cout << "No library file provided." << endl;
        cout << "No playlists file provided." << endl;
        return;
    }
    
    // One file provided (Check for valid library file)
    if (argc == 2) {
        cout << "Loading library from " << "\"" << argv[1] << "\"." << endl;
        cout << "No playlists file provided." << endl;
    }
    
    // Two (or more) files provided (Check for valid library and playlists file)
    if (argc > 2) {
        cout << "Loading library from " << "\"" << argv[1] << "\"." << endl;
        cout << "Loading playlists from " << "\"" << argv[2] << "\"." << endl;
    }
}

// Runs the Dotify Application
// Continually receives input from the user and executes the corresponding command
void DotifyApp::run() {
    string inCommand = "";
    // Startup message
    cout << "Welcome to Dotify! For a full list of commands, type \"HELP\"." << endl;
    // Gets a command input from the user
    inCommand = getInput();
    
    // Executes an action depending on the command input provided by the user
    while (true) {
        if (inCommand == "EXIT") {
            cout << "Thank you for using Dotify!" << endl;
            return;
        } else if (inCommand == "AS") {
            addSong();
        } else if (inCommand == "RS") {
            removeSong();
        } else if (inCommand == "AP") {
            addPlaylist();
        } else if (inCommand == "RP") {
            removePlaylist();
        } else if (inCommand == "RN") {
            renamePlaylist();
        } else if (inCommand == "AG") {
            autogenerate();
        } else if (inCommand == "ASP") {
            addSongToPlaylist();
        } else if (inCommand == "RSP") {
            removeSongFromPlaylist();
        } else if (inCommand == "LB") {
            displayLibrarySongs();
        } else if (inCommand == "PLS") {
            displayPlaylists();
        } else if (inCommand == "PL") {
            displayPlaylistSongs();
        } else if (inCommand == "RT") {
            ratePlaylist();
        } else if (inCommand == "PLY") {
            playSong();
        } else if (inCommand == "EXP") {
            exportToFile();
        } else if (inCommand == "HELP") {
            help();
        } else { // Command not recognized
            cout << "Invalid command.\nFor a full list of commands, type \"HELP\"." << endl;
        }
        // Retrieves a new command input from the user
        inCommand = getInput();
    }
}

    /*********************/
    /** DOTIFY COMMANDS **/
    /*********************/

// Adds a song to the library
void DotifyApp::addSong() {
    shared_ptr<LibrarySong> newLibSong(new LibrarySong(getSong()));
    
    // If song already exists, tell the user
    if (dotDriver.libContains(newLibSong->getIdentifier())) {
        cout << "\"" << newLibSong->getSongName() << "\" by " << newLibSong->getSongArtist() <<
            " (" << newLibSong->getSongAlbum() << "), identified as #" << newLibSong->getIdentifier() <<
            ", already exists in your library." << endl;
        return;
    } else { // Add the song to the library
        dotDriver.addSongToLibrary(newLibSong);
        cout << "\"" << newLibSong->getSongName() << "\" by " << newLibSong->getSongArtist() <<
        " (" << newLibSong->getSongAlbum() << "), identified as #" << newLibSong->getIdentifier() <<
        ", purchased successfully to your library." << endl;
        return;
    }
}

// Gets a song from the user to be added
shared_ptr<Song> DotifyApp::getSong() {
    string songName = "", songArtist = "", songAlbum = "";
    cout << "What is the name of the song you’d like to purchase?" << endl;
    songName = getLine();
    cout << "Who is its artist?" << endl;
    songArtist = getLine();
    cout << "Which album does it belong to?" << endl;
    songAlbum = getLine();
    
    shared_ptr<Song> newSong(new Song(songName, songArtist, songAlbum));
    
    return newSong;
}

// Removes a song from the library
void DotifyApp::removeSong() {
    unsigned int removeIdentifier = 0;
    cout << "What is the identifier of the song you’d like to remove from your library?" << endl;
    removeIdentifier = getInt();
    
    if (!dotDriver.libContains(removeIdentifier)) {
        cout << "No song with identifier #" << removeIdentifier << "exists in your library." << endl;
        return;
    }
    
}

void DotifyApp::addPlaylist() {
    
}

void DotifyApp::removePlaylist() {
    
}

void DotifyApp::renamePlaylist() {
    
}

void DotifyApp::autogenerate() {
    // u w0t m8
}

void DotifyApp::addSongToPlaylist() {
    
}

void DotifyApp::removeSongFromPlaylist() {
    
}

void DotifyApp::displayLibrarySongs() {
    
}

void DotifyApp::displayPlaylists() {
    
}

void DotifyApp::displayPlaylistSongs() {
    
}

void DotifyApp::ratePlaylist() {
    
}

void DotifyApp::playSong() {
    
}

void DotifyApp::exportToFile() {
    
}

void DotifyApp::help() {
    cout << "AS: Purchases a new song to your library" << endl;
    cout << "RS: Removes a specific song from your library" << endl;
    cout << "AP: Creates an empty playlist" << endl;
    cout << "RP: Removes a specific playlist" << endl;
    cout << "RN: Renames a specific playlist" << endl;
    cout << "AG: Autogenerates a playlist based on song name, artist, album, or magic" << endl;
    cout << "ASP: Adds a specific song from your library to a playlist" << endl;
    cout << "RSP: Removes a specific song from a playlist" << endl;
    cout << "LB: Displays all the songs in your library" << endl;
    cout << "PLS: Displays all the of the playlists in alphabetical order of title" << endl;
    cout << "PL: Displays all the songs in a specific playlist in the order added" << endl;
    cout << "RT: Rates a specific playlist from 1 to 5" << endl;
    cout << "PLY: Plays a specific song in your library a specified number of time" << endl;
    cout << "EXP: Exports the song library and playlists to files" << endl;
    cout << "HELP: Displays this help menu" << endl;
    cout << "EXIT: Exits the program" << endl;
}

    /**********************/
    /** HELPER FUNCTIONS **/
    /**********************/

// Retrieves a string input from the user
string DotifyApp::getInput() {
    string input = "";
    cout << "\n> ";
    cin >> input;
    cin.ignore();
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input;
}

// Retrieves a string line from the user
string DotifyApp::getLine() {
    string input = "";
    cout << "> ";
    getline(cin, input);
    return input;
}

// Retrieves an integer from the user
unsigned int DotifyApp::getInt() {
    unsigned int input;
    cout << "> ";
    cin >> input;
    cin.ignore();
    while (!cin) {
        cout << "Invalid input. Please input a positive integer." << endl;
        cin.clear();
        cin.ignore();
        cout << "> ";
        cin >> input;
    }
    return input;
}


#endif
