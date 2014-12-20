#include "connection.h"
#include "connectionclosedexception.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

//using namespace std;

class MessageHandler {
public:
    MessageHandler(const Connection* conn) : c(conn) {}
    int readNumber();
    unsigned char readByte();
    std::string readString(int n);
    void writeString(const std::string& s);
    void writeNumber(int num);
    void writeByte(unsigned char b);
private:
    const Connection* c;
};
