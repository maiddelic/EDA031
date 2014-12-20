#include <string>
#include <vector>
#include "word.h"

using namespace std;

Word::Word(const string& w, const vector<string>& t) {
    word = w;
    trigram = t;
}

string Word::get_word() const {
	return word;
}


//förutsätter att vektorn med trigrams är sorterad (inparametern).
unsigned int Word::get_matches(const vector<string>& t) const {
    unsigned int matches = 0;
    int prev_match = -1;
    for(size_t i = 0; i < t.size(); ++i){
        for(size_t j = prev_match+1; j < trigram.size(); ++j){
            if(t[i].compare(trigram[j]) == 0){
                ++matches;
                prev_match = j;
                break;
            //} else if(t[i].compare(trigram[j]) < 0){ // Gått förbi möjliga matches
             //   break;
            }
        }
    }
    return matches;
}
