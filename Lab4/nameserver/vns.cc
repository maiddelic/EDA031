//
//  VNS.cc
//  
//
//  Created by Niklas Sjöberg on 2014-02-21.
//
//
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "vns.h"

using namespace std;

VNS::VNS(){
    ipAddresses.resize(300000);
}

VNS::~VNS(){
//    for (size_t i = 0; i < ipAddresses.size(); ++i) {
//        delete ipAddresses.at(i);
//    }
//    ipAddresses.clear();
}

void VNS::insert(const HostName& h, const IPAddress& i){
	pair<HostName, IPAddress> p(h,i);
	ipAddresses.push_back(p);
   
}


bool VNS::remove(const HostName& h){
	
    vector<pair<HostName, IPAddress>>::iterator it = find_if(ipAddresses.begin(), ipAddresses.end(), [h](pair<HostName, IPAddress> p) { return p.first == h;
    });
    
    if(it != ipAddresses.end()){
        ipAddresses.erase(it);
        return true;
    }
	
    return false;
}

IPAddress VNS::lookup(const HostName& h) const{
  auto it = find_if (ipAddresses.begin(), ipAddresses.end(), [h](pair<HostName, IPAddress> p) { return p.first == h;
   });
    
   if(it == ipAddresses.end()){
        return NON_EXISTING_ADDRESS;
    }
    return (it->second);
	
}