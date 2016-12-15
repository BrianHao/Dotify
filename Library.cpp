#ifndef LIBRARY_CPP
#define LIBRARY_CPP

#include "Library.h"
using namespace std;

vector<shared_ptr<LibrarySong>> Library::sortLibrary(string sortCategory) {
    vector<shared_ptr<LibrarySong>> sortedLibrary;
    
    if (sortCategory == "NAME") {
        sortedLibrary = getLibSortedByName();
    } else if (sortCategory == "ARTIST") {
        sortedLibrary = getLibSortedByArtist();
    } else if (sortCategory == "ALBUM") {
        sortedLibrary = getLibSortedByAlbum();
    } else { //sortCatefory == "PLAYS"
        sortedLibrary = getLibSortedByPlays();
    }
    
    return sortedLibrary;
}

vector<shared_ptr<LibrarySong>> Library::getLibSortedByName() {
    SortedVector<shared_ptr<LibrarySong>, LibrarySong::LibSongNameComparator> sortedVec;
    
    for(auto i : myLibrary){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}

vector<shared_ptr<LibrarySong>> Library::getLibSortedByArtist() {
    SortedVector<shared_ptr<LibrarySong>, LibrarySong::LibSongArtistComparator> sortedVec;
    
    for(auto i : myLibrary){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}

vector<shared_ptr<LibrarySong>> Library::getLibSortedByAlbum() {
    SortedVector<shared_ptr<LibrarySong>, LibrarySong::LibSongAlbumComparator> sortedVec;
    
    for(auto i : myLibrary){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}

vector<shared_ptr<LibrarySong>> Library::getLibSortedByPlays() {
    SortedVector<shared_ptr<LibrarySong>, LibrarySong::LibSongPlaysComparator> sortedVec;
    
    for(auto i : myLibrary){
        sortedVec.insert(i.second);
    }
    
    return sortedVec.toVector();
}


#endif
