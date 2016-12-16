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

// This command adds a new song to the user’s library. The user specifies the song’s name, artist, and album.
// By default, the song is assigned the next available identifier and starts with 0 plays. If the song already
// exists in the library, indicate the problem.

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

// This command removes a song from the user’s library and any playlists that that song belongs to.
// The user specifies the song’s identifier. Display the playlists that the song was removed from.
// If the song does not exist in the library, indicate the problem.

void DotifyApp::removeSong() {
    unsigned int identifier = 0;
    cout << "What is the identifier of the song you’d like to remove from your library?" << endl;
    identifier = getInt();
    
    // If song does not exist in library, tells the user
    if (!dotDriver.libContains(identifier)) {
        cout << "No song with identifier #" << identifier << " exists in your library." << endl;
        return;
    }
    
    // Song exists in the library, sets it to temp, remove it from the library
    shared_ptr<LibrarySong> tempSong = dotDriver.getLibSong(identifier);
    dotDriver.removeSongFromLibrary(identifier);
    
    // Check if song exists in any playlists
    // Get a vector containing the names of all playlists with that song
    vector<string> playlistsContainingSong = dotDriver.playlistsContainingSong(identifier);
    
    // If no playlists contain the song, let user know song was removed from only library
    if (playlistsContainingSong.size() == 0) {
        cout << "\"" << tempSong->getSongName() << "\" by " << tempSong->getSongArtist() <<
        " (" << tempSong->getSongAlbum() << "), identified as #" << tempSong->getIdentifier() <<
        ", removed successfully from your library." << endl;
    } else { // Let user know song was removed from library and playlists
        cout << "\"" << tempSong->getSongName() << "\" by " << tempSong->getSongArtist() <<
        " (" << tempSong->getSongAlbum() << "), identified as #" << tempSong->getIdentifier() <<
        ", removed successfully from your library and from playlists \"";
        for (int i = 0; i < playlistsContainingSong.size(); i++) {
            cout << playlistsContainingSong.at(i) << "\"";
            if (i > 0) {
                cout << ", ";
            } else {
                cout << "." << endl;
            }
        }
    }
}

// This command creates a new playlist. The user specifies the playlist’s title. By default, the playlist
// starts off with a rating of 1 and no songs. The app must not contain duplicate playlists (i.e., playlists
// with the same title). If the playlist already exists, indicate the problem.
void DotifyApp::addPlaylist() {
    string playlistName = "";
    cout << "What is the title of the playlist you’d like to create?" << endl;
    playlistName = getLine();
    
    
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

// This command displays all of the songs in the user’s library. The user specifies the criterion
//  to order the songs by—name, artist, album, or plays. The songs are displayed in a numbered list,
//  with each displaying its name, artist, album, plays, and identifier.
void DotifyApp::displayLibrarySongs() {
    if (dotDriver.libIsEmpty()) {
        cout << "You have no songs in your library." << endl;
        return;
    }
    
    string category;
    
    cout << "What category should the songs be ordered by? (NAME/ARTIST/ALBUM/PLAYS)" << endl;
    category = getInput();
    if (category != "NAME" && category != "ARTIST" && category != "ALBUM" && category != "PLAYS") {
        cout << "\"" << category << "\" is not a valid criterion to order by." << endl;
        return;
    }
    
    vector<shared_ptr<LibrarySong>> sortedLibrary = dotDriver.getSortedLibrary(category);
    
    for (int i = 0; i < sortedLibrary.size(); i++) {
        cout << i << ". \"" << sortedLibrary.at(i)->getSongName() << "\" by " << sortedLibrary.at(i)->getSongArtist() <<
        " (" << sortedLibrary.at(i)->getSongAlbum() << ") - " << sortedLibrary.at(i)->getNumPlays() << " plays [#" <<
        sortedLibrary.at(i)->getIdentifier() << "]" << endl;
    }
}

void DotifyApp::displayPlaylists() {
    
}

void DotifyApp::displayPlaylistSongs() {
    
}

void DotifyApp::ratePlaylist() {
    
}

// This command plays a song in the user’s library a certain number of times. The user specifies the song’s
// identifier and the number of times to play the song. If the provided value is invalid, assume that the song
// was played 0 times. Display the number of plays started with and the new number of plays for that song. If the
// song does not exist in the library, indicate the problem.

void DotifyApp::playSong() {
    unsigned int identifier = 0;
    cout << "What is the identifier of the song you’d like to listen to?" << endl;
    identifier = getInt();
    unsigned int oldTimesPlayed = dotDriver.getLibSong(identifier)->getNumPlays();
    
    // If song does not exist in library, tells the user
    if (!dotDriver.libContains(identifier)) {
        cout << "No song with identifier #" << identifier << " exists in your library." << endl;
        return;
    }
    
    // If song exists, ask for number of times to play song
    unsigned int numTimes = 0;
    cout << "How many times would you like to play this song?" << endl;
    cout << "> ";
    cin >> numTimes;
    cin.ignore();
    if (cin.fail()) {
        numTimes = 0;
        cin.clear();
        cin.ignore(80, '\n');
    }
    
    dotDriver.getLibSong(identifier)->playSong(numTimes);
    
    cout << "\"" << dotDriver.getLibSong(identifier)->getSongName() << "\" by " <<
    dotDriver.getLibSong(identifier)->getSongArtist() << " (" << dotDriver.getLibSong(identifier)->getSongAlbum() <<
    "), identified as #" << dotDriver.getLibSong(identifier)->getIdentifier() << ", played successfully "
    << numTimes << " times (" << oldTimesPlayed << " plays -> " << dotDriver.getLibSong(identifier)->getNumPlays() <<
    " plays)." << endl;
    
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
    cin.ignore(80, '\n');
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
        cin.ignore(80, '\n');
        cout << "> ";
        cin >> input;
    }
    return input;
}


#endif
