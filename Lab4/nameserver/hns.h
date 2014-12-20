//
//  HNS.h
//  
//
//  Created by Niklas Sjöberg on 2014-02-21.
//
//
#ifndef HNS_H
#define HNS_H

#include <vector>
#include <string>
#include "nameserverinterface.h"

using namespace std;

class HNS : public NameServerInterface {
public:
    HNS(int size);
    ~HNS();
    void insert(const HostName&, const IPAddress&);
    bool remove (const HostName&);
    IPAddress lookup(const HostName&) const;
    
private:
    int getHash(const HostName& h) const;
    void rehash();
    int tableSize;
    const double threshold = 0.75;
    int count = 0;
    vector<vector<pair<HostName, IPAddress>>> pairs;
};

#endif