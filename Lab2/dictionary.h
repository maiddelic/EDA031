#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <unordered_set>
#include "word.h"

using namespace std;

class Dictionary {
public:
	Dictionary();
	bool contains(const string& word) const;
	vector<string> get_suggestions(const string& word) const;
private:
    void add_trigram_suggestions(vector<string>& v, const string& w) const;
    void rank_suggestions(vector<string>& v, const string& w) const;
    void trim_suggestions(vector<string>& v) const;
    unordered_set<string> wordset;
    static const int max_length = 25;
    vector<Word> words[max_length];
};

#endif
