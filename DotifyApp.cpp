#ifndef DOTIFYAPP_CPP
#define DOTIFYAPP_CPP

#include "DotifyApp.h"

using namespace std;

// Runs the Dotify Application
// Continually receives input from the user and executes the corresponding command
void DotifyApp::run(int argc, const char * argv[]) {
    // Attempts to load any files
    load(argc, argv);
    
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

// Implements loading from a library and playlist file from the commandline
void DotifyApp::load(int argc, const char * argv[]) {
    // No files provided
    if (argc <= 1) {
        cout << "No library file provided." << endl;
        cout << "No playlists file provided." << endl;
        return;
    }
    
    // One file provided (Check for valid library file)
    if (argc == 2) {
        loadLibrary(argv[1]);
        cout << "No playlists file provided." << endl;
    }
    
    // Two (or more) files provided (Check for valid library and playlists file)
    if (argc > 2) {
        loadLibrary(argv[1]);
        loadPlaylists(argv[2]);
//        cout << "Loading playlists from " << "\"" << fileName << "\"." << endl;
    }
}

// Reads the data file into a vector, then loads each line as a LibrarySong pointer to the library
void DotifyApp::loadLibrary(string fileName) {
    vector<string> libraryVec;
    string readLine = "";
    
    ifstream myfile (fileName);
    if (!myfile) {
        cout << "Could not load library from “" << "\"" << fileName << "\". Skipping." << endl;
    }
    
    if (myfile.is_open()) {
        while (getline(myfile, readLine))
        {
            libraryVec.push_back(readLine);
        }
        myfile.close();
    }
    
    if (libraryVec.empty()) {
        cout << "Could not load library from “" << "\"" << fileName << "\". Skipping." << endl;
        return;
    }
    
    vector<string> stringVec;
    
    // Parse each string into a song and add it to the library
    for (int i = 0; i < libraryVec.size(); i++) {
        stringVec = parseStringToVector(libraryVec.at(i));
        shared_ptr<Song> newSong(new Song(stringVec[0], stringVec[1], stringVec[2]));
        shared_ptr<LibrarySong> newLibSong(new LibrarySong(newSong, stoi(stringVec[3])));
        dotDriver.addSongToLibrary(newLibSong);
    }
    
    cout << "Loading library from " << "\"" << fileName << "\"." << endl;
    
}

// Reads the data file into a vector, then loads each line as a playlist or song into its playlist
void DotifyApp::loadPlaylists(string fileName) {
    vector<string> playlistsVec;
    string readLine = "";
    
    ifstream myfile (fileName);
    if (!myfile) {
        cout << "Could not load playlists from “" << "\"" << fileName << "\". Skipping." << endl;
    }
    
    if (myfile.is_open()) {
        while (getline(myfile, readLine))
        {
            playlistsVec.push_back(readLine);
        }
        myfile.close();
    }
    
    if (playlistsVec.empty()) {
        cout << "Could not load playlists from “" << "\"" << fileName << "\". Skipping." << endl;
        return;
    }
    
    vector<string> playlistVec;
    vector<string> playlistSongVec;
    unsigned int identifier = 0;
    
    // Parse the first string into a playlist, load the next "numSongs" strings as songs, repeat
    for (int i = 0; i < playlistsVec.size(); i++) {
        playlistVec = parseStringToVector(playlistsVec.at(i));
        shared_ptr<Playlist> newPlaylist(new Playlist(playlistVec[0], stoi(playlistVec[1])));
        dotDriver.addPlaylist(newPlaylist);
        // If playlist contains songs, add them
        if (stoi(playlistVec[2]) > 0) {
            for (int j = 1; j <= stoi(playlistVec[2]); j++) {
                playlistSongVec = parseStringToVector(playlistsVec.at(i+j));
                identifier = createIdentifier(playlistSongVec[0] + playlistSongVec[1] + playlistSongVec[2]);
                
                if (!dotDriver.libContains(identifier)) {
                    cout << "Could not find song in library: \"" << playlistsVec.at(i+j) << "\"" << endl;
                    return;
                }
                
                dotDriver.addSongToPlayList(playlistVec[0], dotDriver.getLibSong(identifier));
            }
        }
        i += stoi(playlistVec[2]);
    }
    
    cout << "Loading library from " << "\"" << fileName << "\"." << endl;
    
}

unsigned int DotifyApp::createIdentifier(string inString) {
    unsigned int identifier = 0;
    
    for (int i = 0; i < inString.size(); i++) {
        identifier += inString[i]*(i+1);
    }
    
    return identifier;
}

vector<string> DotifyApp::parseStringToVector(const string exportFormatString) {
    stringstream ss(exportFormatString);
    string item;
    vector<string> parsedVector;
    // Parses the string, adding each token separated by the delimiter into the vector
    while (getline(ss, item, '|')) {
        parsedVector.push_back(item);
    }
    return parsedVector;
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
    
    if (dotDriver.containsPlaylistWithName(playlistName)) {
        cout << "\"" << playlistName << "\" playlist already exists." << endl;
        return;
    }
    
    shared_ptr<Playlist> newPlaylist(new Playlist(playlistName));
    dotDriver.addPlaylist(newPlaylist);
    cout << "\"" << playlistName << "\" playlist created successfully." << endl;
    
}

// This command removes a playlist. The user specifies the playlist’s title.
// If the playlist does not exist, indicate the problem.
void DotifyApp::removePlaylist() {
    string playlistName = "";
    cout << "What is the title of the playlist you’d like to remove?" << endl;
    playlistName = getLine();
    
    if (!dotDriver.containsPlaylistWithName(playlistName)) {
        cout << "\"" << playlistName << "\" playlist does not exist." << endl;
        return;
    }
    
    dotDriver.removePlaylist(playlistName);
    cout << "\"" << playlistName << "\" playlist removed successfully." << endl;
    
}

//This command renames an existing playlist. The user specifies the current title of the
// playlist to change and the new title. If the playlist does not exist or if a playlist
// with the specified title already exists, indicate the problem.
void DotifyApp::renamePlaylist() {
    string playlistName = "";
    string newName = "";
    cout << "What is the title of the playlist you’d like to rename?" << endl;
    playlistName = getLine();
    
    if (!dotDriver.containsPlaylistWithName(playlistName)) {
        cout << "\"" << playlistName << "\" playlist does not exist." << endl;
        return;
    }
    
    cout << "What is the new title that you’d like to rename it to?" << endl;
    newName = getLine();
    
    if (dotDriver.containsPlaylistWithName(newName)) {
        cout << "\"" << playlistName << "\" playlist already exists." << endl;
        return;
    }

    dotDriver.renamePlaylist(playlistName, newName);
    cout << "\"" << playlistName << "\" playlist renamed successfully to \"" << newName << "\"" << endl;
}

// TO BE IMPLEMENED
void DotifyApp::autogenerate() {
    cout << "To be implemented." << endl;
}

// This command adds a song from the user’s library to an existing playlist. The user specifies the
// playlist to add to and the song to be added. If the playlist does not exist, if the song does not
// exist in the library, or if the song being added already exists in the playlist, indicate the problem.
void DotifyApp::addSongToPlaylist() {
    string playlistName = "";
    unsigned int identifier = 0;
    
    cout << "What is the title of the playlist you’d like to add a song to?" << endl;
    playlistName = getLine();
    
    if (!dotDriver.containsPlaylistWithName(playlistName)) {
        cout << "\"" << playlistName << "\" playlist does not exist." << endl;
        return;
    }
    
    cout << "What is identifier of the song to add to the playlist?" << endl;
    identifier = getInt();
    
    if (!dotDriver.libContains(identifier)) {
        cout << "No song with identifier #" << identifier << " exists in your library." << endl;
        return;
    }
    
    dotDriver.addSongToPlayList(playlistName, dotDriver.getLibSong(identifier));
    cout << "\"" << dotDriver.getLibSong(identifier)->getSongName() << "\" by " <<
    dotDriver.getLibSong(identifier)->getSongArtist() << " (" << dotDriver.getLibSong(identifier)->getSongAlbum() <<
    "), identified as #" << dotDriver.getLibSong(identifier)->getIdentifier() << " added successfully to playlist \"" <<
    playlistName << "\"." << endl;
    
}

// This command removes a song from a playlist. The user specifies the playlist to remove the song from and
// the song to be removed. If the playlist does not exist or if the song does not exist in the playlist,
// indicate the problem.
void DotifyApp::removeSongFromPlaylist() {
    string playlistName = "";
    unsigned int identifier = 0;
    
    cout << "What is the title of the playlist you’d like to remove a song from?" << endl;
    playlistName = getLine();
    
    if (!dotDriver.containsPlaylistWithName(playlistName)) {
        cout << "\"" << playlistName << "\" playlist does not exist." << endl;
        return;
    }
    
    cout << "What is identifier of the song to remove from the playlist?" << endl;
    identifier = getInt();
    
    if (!dotDriver.libContains(identifier)) {
        cout << "No song with identifier #" << identifier << " exists in your library." << endl;
        return;
    }
    
    dotDriver.removeSongFromPlayList(playlistName, identifier);
    cout << "\"" << dotDriver.getLibSong(identifier)->getSongName() << "\" by " <<
    dotDriver.getLibSong(identifier)->getSongArtist() << " (" << dotDriver.getLibSong(identifier)->getSongAlbum() <<
    "), identified as #" << dotDriver.getLibSong(identifier)->getIdentifier() << " removed successfully from playlist \"" <<
    playlistName << "\"." << endl;
    
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
        cout << i+1 << ". \"" << sortedLibrary.at(i)->getSongName() << "\" by " << sortedLibrary.at(i)->getSongArtist() <<
        " (" << sortedLibrary.at(i)->getSongAlbum() << ") - " << sortedLibrary.at(i)->getNumPlays() << " plays [#" <<
        sortedLibrary.at(i)->getIdentifier() << "]" << endl;
    }
}

// This command displays all of the playlists. The playlists are displayed in a numbered list ordered
// first by rating and then alphabetically by title. Each playlist shows its title, rating, and number of songs.
void DotifyApp::displayPlaylists() {
    vector<shared_ptr<Playlist>> playlists = dotDriver.getListOfPlaylistsSorted();
    
    if (playlists.empty()) {
        cout << "You have no playlists." << endl;
    }
    
    for (int i = 0; i < playlists.size(); i++) {
        cout << i+1 << ". \"" << playlists.at(i)->getName() << "\" - Rating: " << playlists.at(i)->getRating() <<
            " - " << playlists.at(i)->numSongs() << " songs" << endl;
    }
}

// This command displays all of the songs in a playlist. The user specifies the playlist. The songs are
// displayed in a numbered list in the order that they were added to the playlist, and each song shows its
// name, artist, album, number of plays, and identifier.
void DotifyApp::displayPlaylistSongs() {
    string playlistName = "";
    
    cout << "What is the title of the playlist you’d like to display?" << endl;
    playlistName = getLine();
    
    if (!dotDriver.containsPlaylistWithName(playlistName)) {
        cout << "\"" << playlistName << "\" playlist does not exist." << endl;
        return;
    }
    
    if (dotDriver.isEmpty(playlistName)) {
        cout << "\"" << playlistName << "\" playlist has no songs." << endl;
        return;
    }
    
    vector<shared_ptr<LibrarySong>> songs = dotDriver.getListOfSongsInPlaylist(playlistName);
    
    for (int i = 0; i < songs.size(); i++) {
        cout << i+1 << ". \"" << songs.at(i)->getSongName() << "\" by " << songs.at(i)->getSongArtist() <<
        " (" << songs.at(i)->getSongAlbum() << ") - " << songs.at(i)->getNumPlays() << " plays [#" <<
        songs.at(i)->getIdentifier() << "]" << endl;
    }
    
}

// This command gives a new rating to a playlist. The user specifies the playlist to rate
// and a rating from 1 to 5. If the playlist does not exist, if the song does not exist in
// the playlist, or if the rating is invalid, indicate the problem.
void DotifyApp::ratePlaylist() {
    string playlistName = "";
    unsigned int rating = 0;
    cout << "What is the title of the playlist you’d like to rate?" << endl;
    playlistName = getLine();
    
    if (!dotDriver.containsPlaylistWithName(playlistName)) {
        cout << "\"" << playlistName << "\" playlist does not exist." << endl;
        return;
    }
    
    cout << "What rating would you like to give this playlist? (1 to 5)" << endl;
    rating = getInt();
    if (rating < 1 || rating > 5) {
        cout << "\"" << rating << "\" is not a valid rating." << endl;
        return;
    }
    
    dotDriver.ratePlaylist(playlistName, rating);
    cout << "\"" << playlistName << "\" playlist rated successfully as a " << rating << "." << endl;
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

// This command exports the song library and playlists to files. The songs in the library will be exported
// to their own file and the playlists will be exported to their own file, based on the file format specified
// earlier. The user specifies the name of the library file and the name of the playlists file. If a file with
// a provided name already exists, then overwrite it. If the library contains no songs or if there are no playlists,
// then simply generate empty files.
void DotifyApp::exportToFile() {
    string libraryFileName = "";
    string playlistFileName = "";
    vector<shared_ptr<LibrarySong>> libraryVec = dotDriver.getSortedLibrary("ID");
    vector<shared_ptr<Playlist>> playlistsVec = dotDriver.getListOfPlaylistsSorted();
    vector<shared_ptr<LibrarySong>> playlistSongsVec;
    
    cout << "What is the name of the file you’d like to export your library to?" << endl;
    libraryFileName = getLine();
    cout << "What is the name of the file you’d like to export your playlists to?" << endl;
    playlistFileName = getLine();
    
    // Export Library
    if (!libraryVec.empty()) {
        ofstream libraryFile (libraryFileName);
        if (libraryFile.is_open())
        {
            for (int i = 0; i < libraryVec.size(); i++) {
                libraryFile << libraryVec.at(i)->toLibraryExportFormat() + "\n";
            }
            libraryFile.close();
        }
    }

    // Export Playlists
    if (!playlistsVec.empty()) {
        ofstream playlistFile (playlistFileName);
        if (playlistFile.is_open())
        {
            for (int i = 0; i < playlistsVec.size(); i++) {
                playlistFile << playlistsVec.at(i)->toExportFormat() + "\n";
                playlistSongsVec = dotDriver.getListOfSongsInPlaylist(playlistsVec.at(i)->getName());
                if (!playlistSongsVec.empty()) {
                    for (int j = 0; j < playlistSongsVec.size(); j++) {
                        playlistFile << playlistSongsVec.at(j)->toPlaylistExportFormat() + "\n";
                    }
                }
            }
            playlistFile.close();
        }
    }
    
    cout << "Library and playlists exported successfully!" << endl;
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
