//
//  test_tostring.cc
//  
//
//  Created by Niklas Sjöberg on 2014-02-16.
//
//
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "date.h"

using namespace std;

template <typename T>
string toString(T t){
    stringstream out;
    out << t;
    return out.str();
}

template <typename T>
T string_cast(const string &s){
    T val;
    stringstream iss(s);
//    if( !(iss >> val) ){
//        throw new invalid_argument("type casting not valid");
//    }
    iss >> val;
//    if(iss.fail()){
//        cout << "Hejj fail hejj!" << endl;
//    }
    return val;
}


int main(){
    
    // A.4
    double d = 1.234;
    Date today;
    string sd = toString(d);
    string st = toString(today);
    cout << sd << endl;
    cout << st << endl;
    cout << endl;
    
    // A.5

    try {
        int i = string_cast<int>("123");
        double d2 = string_cast<double>("12.34");
//        Date date = string_cast<Date>("2013-07-25");
        
        cout << toString(i) << endl;
        cout << toString(d2) << endl;
//        cout << toString(date) << endl;
    } catch (const invalid_argument& e) {
        cerr << "Error: " <<  e.what() << endl;
    }
    
}