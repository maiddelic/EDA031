//
//  HNS.cc
//  
//
//  Created by Niklas Sjöberg on 2014-02-21.
//
//
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "hns.h"

using namespace std;

HNS::HNS(int size){
    tableSize = size;
    pairs = vector<vector<pair<HostName, IPAddress>>>(tableSize, vector<pair<HostName, IPAddress>>());
}

HNS::~HNS(){

}

void HNS::insert(const HostName& h, const IPAddress& i){
    int index = getHash(h);
    pairs[index].push_back(pair<HostName, IPAddress>(h, i));
    ++count;
    
    double k = count / tableSize;
    if(k >= threshold){
        rehash();
    }
}


bool HNS::remove(const HostName& h){
    int index = getHash(h);
    
    vector<pair<HostName, IPAddress>>::iterator it = find_if (pairs[index].begin(), pairs[index].end(), [h](pair<HostName, IPAddress> p) { return p.first == h;
    });

    if(it != pairs[index].end()){
        pairs[index].erase(it);
//        --count;
        return true;
    }
    return false;
}

IPAddress HNS::lookup(const HostName& h) const{
    int index = getHash(h);
    vector<const pair<HostName, IPAddress>>::iterator it = find_if (pairs[index].begin(), pairs[index].end(), [h](pair<HostName, IPAddress> p) { return p.first == h;
    });
    
    if(it == pairs[index].end()){
        return NON_EXISTING_ADDRESS;
    }
    return it->second;
}

int HNS::getHash(const HostName& hostname) const{
    int hashValue = 0;
    for (size_t i = 0; i < hostname.length(); ++i) {
        hashValue = hashValue + int(hostname[i]);
    }
    hashValue %= tableSize;
    return hashValue;
}

void HNS::rehash(){
    vector<vector<pair<HostName,IPAddress>>> temp = pairs;
    count = 0;
    tableSize = tableSize*2;
    pairs = vector<vector<pair<HostName, IPAddress>>>(tableSize, vector<pair<HostName, IPAddress>>());
    
    for(vector<pair<HostName,IPAddress>> p : temp){
        for(pair<HostName,IPAddress> p2 : p){
            insert(p2.first, p2.second);
        }
    }
}
