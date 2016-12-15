// A Song item contains a name, artist and album

#ifndef SONG_H
#define SONG_H

#include <string>
using namespace std;

class Song {
public:
    // Constructor and Destructor
    Song(string inSongName = "", string inSongArtist = "", string inSongAlbum = "") :
            songName(inSongName), songArtist(inSongArtist), songAlbum(inSongAlbum) {};
    ~Song() {};
    
    // Getters and Setters
    void setSongName(string inSongName) { songName = inSongName; };
    void setSongArtist(string inSongArtist) { songArtist = inSongArtist; };
    void setSongAlbum(string inSongAlbum) { songAlbum = inSongAlbum; };
    string getSongName() { return songName; };
    string getSongArtist() { return songArtist; };
    string getSongAlbum() { return songAlbum; };
    
private:
    // Private Song Variables
    string songName = "";
    string songArtist = "";
    string songAlbum = "";
};

#endif
