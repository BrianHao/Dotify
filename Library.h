#ifndef LIBRARY_H
#define LIBRARY_H

#include <unordered_map>
#include <memory>
#include <string>
#include "LibrarySong.h"
#include "SortedVector.h"
using namespace std;

class Library {
public:
    // Constructor and Destructor
    Library() {};
    ~Library() {};
    
    // Manage Library Songs
    void addSong(shared_ptr<LibrarySong> inSong) {
        myLibrary.insert({inSong->getIdentifier(),inSong}); };
    void removeSong(unsigned int identifier) { myLibrary.erase(identifier); };
    void playSong(unsigned int identifier, unsigned int numTimesPlayed) {
        myLibrary[identifier]->playSong(numTimesPlayed); };
    shared_ptr<LibrarySong> getLibSong(unsigned int identifier) { return myLibrary[identifier]; };
    bool contains(unsigned int identifier) { return myLibrary.count(identifier) == 1; };
    bool empty() { return myLibrary.empty(); };
    
    // Get sorted list of Library songs for display
    vector<shared_ptr<LibrarySong>> sortLibrary(string sortCategory);
    
private:
    // Map of LibrarySong pointers, using its identifier as a key
    unordered_map<unsigned int, shared_ptr<LibrarySong>> myLibrary;
    
    // Helper functions to sort library
    vector<shared_ptr<LibrarySong>> getLibSortedByName();
    vector<shared_ptr<LibrarySong>> getLibSortedByArtist();
    vector<shared_ptr<LibrarySong>> getLibSortedByAlbum();
    vector<shared_ptr<LibrarySong>> getLibSortedByPlays();
    vector<shared_ptr<LibrarySong>> getLibSortedByIdentifier();
    
};

#endif
