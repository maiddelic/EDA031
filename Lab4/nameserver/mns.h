//
//  MNS.h
//  
//
//  Created by Niklas Sjöberg on 2014-02-21.
//
//
#ifndef MNS_H
#define MNS_H

#include <map>
#include <string>
#include "nameserverinterface.h"

using namespace std;

class MNS : public NameServerInterface {
public:
    MNS();
    ~MNS();
    void insert(const HostName&, const IPAddress&);
    bool remove (const HostName&);
    IPAddress lookup(const HostName&) const;
    
private:
    map<HostName, IPAddress> addresses;
};

#endif