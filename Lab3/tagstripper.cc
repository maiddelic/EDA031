//
//  tagstripper.cc
//  
//
//  Created by Niklas Sjöberg on 2014-02-14.
//
//
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "TagRemover.h"

using namespace std;

//tagremover är inte klar, följer inte riktigt intruktionerna. Översätter bland annat inte html specialchars.
int main(int argc, char *argv[]){
    
    if (argc < 2) {
        cerr<<"No file name entered!" << endl;
        exit(1);
    }
    
    TagRemover tr(argv[1]);
    tr.print();
    
    
    
//    ifstream infile;
//    infile.open("test.html");
//    
//    if(!infile){
//        cerr << "Could not open file!" << endl;
//        exit(1);
//    }
//
//    string str((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
//    
//    cout << str << endl;
//
//    regex reg("\\<[^\\>]*\\>");
//    
//    string out = regex_replace(str, reg, "");
//    
//    
//    cout << out;
//    
//    
//    
//    infile.close();
    
    
//    string line;
//    string stripped;
//    bool inTag = false;
//    while(getline(infile, line)) {
//    
//        if(inTag){
//            size_t eraseEndPos = line.find('>');
//        
//            if(eraseEndPos != string::npos){
//                line.erase(0, eraseEndPos);
//                inTag = false;
//            } else {
//                line.erase();
//            }
//        } else {
//            size_t eraseStartPos = line.find('<');
//            if(eraseStartPos != string::npos){
//                size_t eraseEndPos = line.find('>');
//                if(eraseEndPos == string::npos){
//                    inTag = true;
//                    line.erase(eraseStartPos);
//                } else {
//                    line.erase(eraseStartPos, eraseEndPos);
//                }
//            } else {
//
//            }
//        }
//        cout << line << endl;
}
