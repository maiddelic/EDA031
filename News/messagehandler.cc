#include "connection.h"
#include "connectionclosedexception.h"
#include "messagehandler.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;


int MessageHandler::readNumber() {
    unsigned char byte1 = c->read();
    unsigned char byte2 = c->read();
    unsigned char byte3 = c->read();
    unsigned char byte4 = c->read();

    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}



string MessageHandler::readString(int n) {
    string s;
	char ch;
	for(int i = 0; i < n; i++){
        ch = c->read();
        s+= ch;
    }
	return s;
}

void MessageHandler::writeString(const std::string& s) {
    for(int i = 0; s[i] != '\0'; i++){
		c->write(s[i]);
	}
}

void MessageHandler::writeNumber(int num) {
    c->write((num >> 24) & 0xFF);
	c->write((num >> 16) & 0xFF);
	c->write((num >> 8)	 & 0xFF);
	c->write(num & 0xFF);
}

void MessageHandler::writeByte(unsigned char b){
    c->write(b & 0xFF);
}

unsigned char MessageHandler::readByte(){
    unsigned char byte1 = c->read();
    return byte1;
}

