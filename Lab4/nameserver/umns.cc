//
//  UMNS.cc
//  
//
//  Created by Niklas Sjöberg on 2014-02-21.
//
//
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include "umns.h"

using namespace std;

UMNS::UMNS(){

}

UMNS::~UMNS(){

}

void UMNS::insert(const HostName& h, const IPAddress& i){
    addresses.insert(pair<HostName, IPAddress>(h, i));
}


bool UMNS::remove(const HostName& h){
    return addresses.erase(h);
}

IPAddress UMNS::lookup(const HostName& h) const{
    try{
        IPAddress ip = addresses.at(h);
        return ip;
    } catch (out_of_range e){
        return NON_EXISTING_ADDRESS;
    }
}