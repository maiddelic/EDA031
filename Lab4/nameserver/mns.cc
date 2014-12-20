//
//  MNS.cc
//  
//
//  Created by Niklas Sjöberg on 2014-02-21.
//
//
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include "mns.h"

using namespace std;

MNS::MNS(){

}

MNS::~MNS(){

}

void MNS::insert(const HostName& h, const IPAddress& i){
    addresses.insert(pair<HostName, IPAddress>(h, i));
}


bool MNS::remove(const HostName& h){
    return addresses.erase(h);
}

IPAddress MNS::lookup(const HostName& h) const{
    try{
        IPAddress ip = addresses.at(h);
        return ip;
    } catch (out_of_range e){
        return NON_EXISTING_ADDRESS;
    }
}