/*************/
/** LIBRARY **/
/*************/
// Contains an unordered_map of Library Song pointers, using its identifier as the key

#ifndef LIBRARY_CPP
#define LIBRARY_CPP

#include "Library.h"
using namespace std;

// Returns a vector of the library sorted by the provided category
vector<shared_ptr<LibrarySong>> Library::sortLibrary(string sortCategory) {
    vector<shared_ptr<LibrarySong>> sortedLibrary;
    
    if (sortCategory == "NAME") {
        sortedLibrary = getLibSortedByName();
    } else if (sortCategory == "ARTIST") {
        sortedLibrary = getLibSortedByArtist();
    } else if (sortCategory == "ALBUM") {
        sortedLibrary = getLibSortedByAlbum();
    } else if (sortCategory == "PLAYS"){
        sortedLibrary = getLibSortedByPlays();
    } else { // //sortCatefory == "ID"
        sortedLibrary = getLibSortedByIdentifier();
    }
    
    return sortedLibrary;
}

// Returns a vector of the library sorted by name
vector<shared_ptr<LibrarySong>> Library::getLibSortedByName() {
    SortedVector<shared_ptr<LibrarySong>, LibrarySong::LibSongNameComparator> sortedVec;
    
    for(auto i : myLibrary){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}

// Returns a vector of the library sorted by artist
vector<shared_ptr<LibrarySong>> Library::getLibSortedByArtist() {
    SortedVector<shared_ptr<LibrarySong>, LibrarySong::LibSongArtistComparator> sortedVec;
    
    for(auto i : myLibrary){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}

// Returns a vector of the library sorted by album
vector<shared_ptr<LibrarySong>> Library::getLibSortedByAlbum() {
    SortedVector<shared_ptr<LibrarySong>, LibrarySong::LibSongAlbumComparator> sortedVec;
    
    for(auto i : myLibrary){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}

// Returns a vector of the library sorted by plays
vector<shared_ptr<LibrarySong>> Library::getLibSortedByPlays() {
    SortedVector<shared_ptr<LibrarySong>, LibrarySong::LibSongPlaysComparator> sortedVec;
    
    for(auto i : myLibrary){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}

// Returns a vector of the library sorted by identifier
vector<shared_ptr<LibrarySong>> Library::getLibSortedByIdentifier() {
    SortedVector<shared_ptr<LibrarySong>, LibrarySong::LibSongIdentifierComparator> sortedVec;
    
    for(auto i : myLibrary){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}

// Get vector of Library songs containing a certain string in a certain category for autogenerate
vector<shared_ptr<LibrarySong>> Library::agLibrary(string query, string category) {
    vector<shared_ptr<LibrarySong>> agLibrary;
    
    if (category == "NAME") {
        for(auto i : myLibrary){
            if (i.second->getSongName() == query) {
                agLibrary.push_back(i.second);
            }
        }
    } else if (category == "ARTIST") {
        for(auto i : myLibrary){
            if (i.second->getSongArtist() == query) {
                agLibrary.push_back(i.second);
            }
        }
    } else { // ALBUM
        for(auto i : myLibrary){
            if (i.second->getSongAlbum() == query) {
                agLibrary.push_back(i.second);
            }
        }
    }
    return agLibrary;
}


#endif
