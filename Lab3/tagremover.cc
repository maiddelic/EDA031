//
//  TagRemover.cpp
//  
//
//  Created by Niklas Sjöberg on 2014-02-14.
//
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "TagRemover.h"

using namespace std;

TagRemover::TagRemover(string input) {
    filename = input;
}

void
TagRemover::print() const{
    ifstream infile;
    infile.open(filename);
    
    if(!infile){
        cerr << "Could not open file!" << endl;
        exit(1);
    }
    
    string str((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    
    regex reg("\\<[^\\>]*\\>");
    
    string s = regex_replace(str, reg, "");
    
    regex reg2("&lt");
    regex reg3("&gt");
    regex reg4("&nbsp");
    regex reg5("&amp");
    
    string s1 = regex_replace(s, reg2, "<");
    string s2 = regex_replace(s1, reg3, ">");
    string s3 = regex_replace(s2, reg4, " ");
    string s4 = regex_replace(s3, reg5, "&");
    
    infile.close();
    
    cout << s4;
}

