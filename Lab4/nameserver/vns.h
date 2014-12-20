//
//  VNS.h
//  
//
//  Created by Niklas Sjöberg on 2014-02-21.
//
//
#ifndef VNS_H
#define VNS_H

#include <vector>
#include <string>
#include "nameserverinterface.h"

using namespace std;

class VNS : public NameServerInterface {
public:
    VNS();
    ~VNS();
    void insert(const HostName&, const IPAddress&);
    bool remove (const HostName&);
    IPAddress lookup(const HostName&) const;
    
private:
    vector<pair<HostName, IPAddress>> ipAddresses;
};

#endif