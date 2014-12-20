//
//  TagRemover.h
//  
//
//  Created by Niklas Sjöberg on 2014-02-14.
//
//
#ifndef TagRemover_H
#define TagRemover_H

#include <iostream>

using namespace std;

class TagRemover {
public:
    TagRemover(string input); 
    void print() const;     // removes html tags and translates html special charaters, then prints the new text.
private:
    string filename;
};

#endif
