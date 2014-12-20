//
//  UMNS.h
//  
//
//  Created by Niklas Sjöberg on 2014-02-21.
//
//
#ifndef UMNS_H
#define UMNS_H

#include <unordered_map>
#include <string>
#include "nameserverinterface.h"

using namespace std;

class UMNS : public NameServerInterface {
public:
    UMNS();
    ~UMNS();
    void insert(const HostName&, const IPAddress&);
    bool remove (const HostName&);
    IPAddress lookup(const HostName&) const;
    
private:
    unordered_map<HostName, IPAddress> addresses;
};

#endif