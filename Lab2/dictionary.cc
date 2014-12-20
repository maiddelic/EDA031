#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "word.h"
#include "dictionary.h"

using namespace std;


Dictionary::Dictionary() {
    ifstream infile;
    infile.open("words.txt");
    
    if(!infile){
        cerr << "Could not open infile" << endl;
        exit(1);
    }
    
    cout << "Type in a word." << endl;
	
    string line;
    string trigram;
    unsigned int pos;
    string w;
    vector<string> trigrams;
    
    while(getline(infile, line)){
		pos = line.find(" ");
		w = line.substr(0,pos);
		wordset.insert(w);
        if (w.length() >= 3){
            for(size_t i = 0; i < w.length()-2; ++i){
                trigram = w.substr(i, i+2);
                transform(trigram.begin(), trigram.end(), trigram.begin(), ::tolower);
                trigrams.push_back(trigram);
            }
            sort(trigrams.begin(), trigrams.end());
        }
        Word word(w, trigrams);
        trigrams.clear();
        words[w.length()].push_back(word);
	}
    
    infile.close();
}

bool Dictionary::contains(const string& word) const {
    return wordset.count(word);
}

vector<string> Dictionary::get_suggestions(const string& word) const {
    vector<string> suggestions;
	add_trigram_suggestions(suggestions,word);
	rank_suggestions(suggestions,word);
	trim_suggestions(suggestions);
	return suggestions;

}


void Dictionary::add_trigram_suggestions(vector<string>& v, const string& w) const{
	int nbroftrigrams = w.length()-2;
    unsigned int match = nbroftrigrams/2;
    vector<string> trigrams;
    string trigram;
    for(size_t i = 0; i < w.length()-2; ++i){
        trigram = w.substr(i, i+2);
        transform(trigram.begin(), trigram.end(), trigram.begin(), ::tolower);
        trigrams.push_back(trigram);
    }
    sort(trigrams.begin(), trigrams.end());
    
    for(size_t j = w.length()-1; j < w.length()+2; ++j){
        vector<Word> tempwords = words[j];
        
        for(size_t i = 0; i < tempwords.size(); ++i){
            Word word = tempwords[i];
            if(word.get_matches(trigrams) >= match){
                v.push_back(word.get_word());
            }
        }
    }
}



void Dictionary::rank_suggestions(vector<string>& v, const string& w) const{
    if(!v.empty()){         ///Nytt
        vector<pair<int, string>> ranked;
        int d[26][26];
        
        for(size_t k = 0; k < v.size() ; ++k){
            d[0][0] = 0;
            for(size_t i = 0; i <= 25; ++i) d[i][0] = i;
            for(size_t j = 0; j <= 25; ++j) d[0][j] = j;
            int a2;
            for(size_t i = 1; i <= v[k].length() ; ++i){
                for(size_t j = 1; j <= w.length(); ++j){
                    int a;
                    if(v[k].at(i-1) == w.at(j-1)){
                        a =d[i-1][j-1];
                    } else {
                        a = d[i-1][j-1] +1;
                    }
                
                    int b = d[i-1][j] + 1;
                    int c = d[i][j-1] + 1;
                    d[i][j] = min(min(a,b), c);

                    a2 = d[i][j];
                }
            }
            pair<int, string> p = make_pair(d[v[k].length()][w.length()], v[k]);
            ranked.push_back(p);
        }
    
        v.clear();
        sort(ranked.begin(), ranked.end());
        for(size_t i = 0; i < ranked.size(); ++i){
            v.push_back(ranked[i].second);
        }
    }    //nytt
}



void Dictionary::trim_suggestions(vector<string>& v) const{
    if(!v.empty() && v.size()>5){     //nytt
        v.erase (v.begin()+5,v.end());
    } //nytt
}

