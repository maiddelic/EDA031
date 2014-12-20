//
//  read.cpp
//  
//
//  Created by Niklas Sjöberg on 2014-02-07.
//
//
#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <vector>

using namespace std;


int main(){
    ifstream infile;
    infile.open("words");
    ofstream outfile;
    outfile.open("words.txt");
    
    if (!infile) {
        cerr << "Could not open input file" << endl;
        exit(1);
    } else if (!outfile) {
        cerr << "Could not open output file" << endl;
        exit(1);
    }
    
    ostream_iterator<string> outfile_iterator(outfile, " ");
    vector<string> lines;
    vector<string> trigrams;
    string word;
    string trigram;
    
    while(getline(infile, word)){
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        lines.push_back(word);
        
        if(word.length() < 3){
            lines.push_back("0");
        } else {
            lines.push_back(to_string(word.length()-2));
            for(int i = word.length(); i > 2; --i){
                trigram = word.substr(0, 3);
                transform(trigram.begin(), trigram.end(), trigram.begin(), ::tolower);
                trigrams.push_back(trigram);
                word.erase(0, 1);
            }
            sort(trigrams.begin(), trigrams.end());
            lines.insert(lines.end(), trigrams.begin(), trigrams.end());
            trigrams.clear();
        }
        copy(lines.begin(), lines.end(), outfile_iterator);
        outfile.put('\n');
        lines.clear();
    }
    
    
    
    infile.close();
    outfile.close();
    
    
//    int i = 0;
//    string line;
//    filebuf fb;
//    if(fb.open(argv[1], ios::in)){
//        istream is(&fb);
//        while(getline(is, line) && i < 10){
////            transform(line.begin(), line.end(), line.begin(), ::tolower);
//            cout << line;
//            ++i;
//            
//            
//            
//            if(line.length() < 3){
//                cout << " trigrams: " << 0 << endl;
//            } else {
//                cout << " trigrams: " << line.length()-2 << endl;
//            }
//        }
//    }
//    fb.close();
}
