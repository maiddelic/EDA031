//
//  prime.cc
//  
//
//  Created by Niklas Sjöberg on 2014-02-17.
//
//
#include <string>
#include <iostream>

using namespace std;

int main(){
    string s(100001, 'P');
    string p;
    size_t index = 0;
    
    s.replace(0, 2, "CC");
    
    for(size_t i = 2; i < s.length(); i=i+index+1){
        for(size_t j = 2; i*j < s.length(); ++j){
            s.replace(i*j, 1, "C");
        }
        p = s.substr(i+1, s.length());
        index = p.find_first_of("P");
        if(index == string::npos){
            break;
        }
    }
    
    for(size_t i = 0; i < 201; ++i){
        if(s[i]=='P'){
            cout << i << " ";
        }
    }
    
    cout << endl;
    cout << s.find_last_of("P") << endl;
}