#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <iostream>
#include <istream>
#include <fstream>


#include "file-database.h"

using namespace std;

string file;
FileDatabase::FileDatabase(string fileName){
    file = fileName;
    readFile();
    writeFile();
}

void FileDatabase::createNewsGroup(const string& ng){
    Database::createNewsGroup(ng);
    cout << "CREATE!!"<< endl;
    writeFile();
}


void FileDatabase::deleteNewsGroup(const int& number){
    Database::deleteNewsGroup(number);
    writeFile();
}

void FileDatabase::createArticle(const int& newsGroup, const string& title,
                                 const string& author, const string& text){
    Database::createArticle(newsGroup, title, author, text);
    writeFile();
}



void FileDatabase::deleteArticle(const int& newsGroup, const int& artID){
    Database::deleteArticle(newsGroup, artID);
    writeFile();
}


void FileDatabase::writeFile(){
    cout << "Write!" << endl;
    ofstream outfile;
    outfile.open(file);
    int numNewsGroups = db.size();
    if(!outfile){
        cerr << "Could not open output file" << endl;
        exit(1);
    }
    outfile << to_string(numNewsGroups);
    outfile.put('\n');
    for(auto it = db.begin(); it != db.end(); ++it){
        outfile << to_string(it->first);
        outfile.put(' ');
        
        outfile << it->second.first;
        outfile.put(' ');
        int numArticles = it->second.second.size();
        outfile << to_string(numArticles);
        outfile.put('\n');
        auto artMap = it->second.second;
        for(auto it2 = artMap.begin(); it2 != artMap.end(); ++it2){
            outfile << to_string(it2->first);
            outfile.put(' ');
            outfile << it2->second.title;
            outfile.put(' ');
            outfile << it2->second.author;
            outfile.put(' ');
            outfile << it2->second.text;
            outfile.put('\n');
        }
    }
    outfile << to_string(groupID);
    outfile.put('\n');
    outfile << to_string(artID);
    outfile.close();
}

void FileDatabase::readFile(){
    ifstream infile;
    infile.open(file);
    if(infile){
        string word;
        int numNewsGroups;
        if(getline(infile, word)){
            numNewsGroups = stoi(word);
            for(int i = 0; i != numNewsGroups; ++i){
                if(getline(infile, word)){
                    int firstSpace = word.find_first_of(' ');
                    int newsGroupNumber = stoi(word.substr(0, firstSpace));
                    word = word.substr(firstSpace+1, word.length()-firstSpace-1);
                    
                    firstSpace = word.find_first_of(' ');
                    string newsGroupName = word.substr(0, firstSpace);
                    word = word.substr(firstSpace+1, word.length()-firstSpace-1);
                    
                    firstSpace = word.find_first_of(' ');
                    int nbrOfArticles = stoi(word.substr(0, firstSpace));
                    unordered_map<int, article> m;
                    for(int i = 0; i != nbrOfArticles; ++i){
                        if(getline(infile, word)){
                            int firstSpace = word.find_first_of(' ');
                            int articleNumber = stoi(word.substr(0, firstSpace));
                            word = word.substr(firstSpace+1, word.length()-firstSpace-1);
                            
                            firstSpace = word.find_first_of(' ');
                            string title  = word.substr(0, firstSpace);
                            word = word.substr(firstSpace+1, word.length()-firstSpace-1);
                            
                            firstSpace = word.find_first_of(' ');
                            string author  = word.substr(0, firstSpace);
                            word = word.substr(firstSpace+1, word.length()-firstSpace-1);
                            
                            firstSpace = word.find_first_of(' ');
                            string text  = word.substr(0, firstSpace);
                            
                            article art = article(title, author, text);
                            m.insert(make_pair(articleNumber, art));
                        }
                    }
                    db.insert(make_pair(newsGroupNumber,make_pair(newsGroupName, m)));
                    
                }
            }
        }
        if(getline(infile, word)){
            groupID = stoi(word);
        }
        if(getline(infile, word)){
            artID = stoi(word);
        }
        infile.close();
    } else {
        cerr << "Could not open input file" << endl;
        groupID = 0;
        artID = 0;
    }
}