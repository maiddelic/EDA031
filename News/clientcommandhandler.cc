#include "messagehandler.h"
#include "protocol.h"
#include "clientcommandhandler.h"

#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, int> ClientCommandHandler::listNewsGroups() {        //DONE
    mh.writeByte(Protocol::COM_LIST_NG);
    mh.writeByte(Protocol::COM_END);
    
    if (mh.readByte() == Protocol::ANS_LIST_NG) {
        mh.readByte();
        unordered_map<string, int> groups;
        unsigned int nbrofgroups = mh.readNumber();
        if (nbrofgroups == 0) {
            cout << "There are no newsgroups, try creating a one! " << endl;
        } else {
            for (size_t i = 0; i != nbrofgroups; ++i) {
                mh.readByte();
                int articlenumber = mh.readNumber();
                mh.readByte();
                int stringsize = mh.readNumber();
                string articlename = mh.readString(stringsize);
                cout << articlenumber << " " << articlename << endl;
                groups.insert(make_pair(articlename, articlenumber));
            }
        }
        mh.readByte();
        return groups;
    } else {
        cerr << "Wrong answer received from server, connection terminated" << endl;
        exit(1);
    }
}

void ClientCommandHandler::createNewsGroup(const string& name) {       //DONE
    mh.writeByte(Protocol::COM_CREATE_NG);
    mh.writeByte(Protocol::PAR_STRING);
    mh.writeNumber(name.size());
    mh.writeString(name);
    mh.writeByte(Protocol::COM_END);
    
    if(mh.readByte() == Protocol::ANS_CREATE_NG) {
        if(mh.readByte() == Protocol::ANS_NAK) {
            mh.readByte();
            cout << "Newsgroup already exists!" << endl;
        } else {
            cout << "Newsgroup created successfully!" << endl;
        }
        mh.readByte();
    } else {
        cerr << "Wrong answer received from server, connection terminated" << endl;
        exit(1);
    }
}

void ClientCommandHandler::deleteNewsGroup(const int num) {      //DONE
    mh.writeByte(Protocol::COM_DELETE_NG);
    mh.writeByte(Protocol::PAR_NUM);
    mh.writeNumber(num);
    mh.writeByte(Protocol::COM_END);
    
    if(mh.readByte() == Protocol::ANS_DELETE_NG) {
        if(mh.readByte() == Protocol::ANS_NAK) {
            mh.readByte();
            cout << "Newsgroup doesn't exist!" << endl;
        } else {
            cout << "Newsgroup deleted!" << endl;
        }
        mh.readByte();
    } else {
        cerr << "Wrong answer received from server, connection terminated" << endl;
        exit(1);
    }
}

void ClientCommandHandler::listArticles(const int num) {    //DONE
    mh.writeByte(Protocol::COM_LIST_ART);
    mh.writeByte(Protocol::PAR_NUM);
    mh.writeNumber(num);
    mh.writeByte(Protocol::COM_END);
    
    if(mh.readByte() == Protocol::ANS_LIST_ART) {
        if(mh.readByte() == Protocol::ANS_ACK){
            mh.readByte();
            unsigned int nbrofarticles = mh.readNumber();
            if(nbrofarticles == 0) {
                cout << "There are no articles in this newsgroup." << endl;
            } else {
                for (size_t i = 0; i != nbrofarticles; ++i){
                    mh.readByte();
                    int articlenumber = mh.readNumber();
                    mh.readByte();
                    int stringsize = mh.readNumber();
                    string articlename = mh.readString(stringsize);
                    cout << articlenumber << " " << articlename << endl;
                }
            }
        } else {
            mh.readByte();
            cout << "Newsgroup doesn't exist!" << endl;
        }
        mh.readByte();
    } else {
        cerr << "Wrong answer received from server, connection terminated" << endl;
        exit(1);
    }
}

void ClientCommandHandler::createArticle(const int num, const string& title, const string& author, const string& text) {        //DONE
    mh.writeByte(Protocol::COM_CREATE_ART);
    mh.writeByte(Protocol::PAR_NUM);
    mh.writeNumber(num);
    mh.writeByte(Protocol::PAR_STRING);
    mh.writeNumber(text.size());
    mh.writeString(text);
    mh.writeByte(Protocol::PAR_STRING);
    mh.writeNumber(title.size());
    mh.writeString(title);
    mh.writeByte(Protocol::PAR_STRING);
    mh.writeNumber(author.size());
    mh.writeString(author);
    mh.writeByte(Protocol::COM_END);
    
    if(mh.readByte() == Protocol::ANS_CREATE_ART) {
        if(mh.readByte() == Protocol::ANS_NAK) {
            mh.readByte();
            cout << "Newsgroup doesn't exist!" << endl;
        } else {
            cout << "Article successfully created!" << endl;
        }
        mh.readByte();
    } else {
        cerr << "Wrong answer received from server, connection terminated" << endl;
        exit(1);
    }
}

void ClientCommandHandler::deleteArticle(const int num, const int num2) {      //DONE
    mh.writeByte(Protocol::COM_DELETE_ART);
    mh.writeByte(Protocol::PAR_NUM);
    mh.writeNumber(num);
    mh.writeByte(Protocol::PAR_NUM);
    mh.writeNumber(num2);
    
    mh.writeByte(Protocol::COM_END);
    
    if(mh.readByte() == Protocol::ANS_DELETE_ART) {
        if(mh.readByte() == Protocol::ANS_NAK) {
            auto fail = mh.readByte();
            if (fail == Protocol::ERR_NG_DOES_NOT_EXIST){
                cout << "Newsgroup doesn't exist!" << endl;
            } else if(fail == Protocol::ERR_ART_DOES_NOT_EXIST) {
                cout << "Article doesn't exist!" << endl;
            }
        } else {
            cout << "Article deleted!" << endl;
        }
        mh.readByte();
    } else {
        cerr << "Wrong answer received from server, connection terminated" << endl;
        exit(1);
    }
}

void ClientCommandHandler::getArticle(const int num, const int num2) {     //DONE
    mh.writeByte(Protocol::COM_GET_ART);
    mh.writeByte(Protocol::PAR_NUM);
    mh.writeNumber(num);
    mh.writeByte(Protocol::PAR_NUM);
    mh.writeNumber(num2);
    mh.writeByte(Protocol::COM_END);

    if(mh.readByte() == Protocol::ANS_GET_ART) {
        if(mh.readByte() == Protocol::ANS_ACK) {
            string title;
            string author;
            string text;
            
            mh.readByte();
            int size = mh.readNumber();
            text = mh.readString(size);
            
            mh.readByte();
            int size2 = mh.readNumber();
            title = mh.readString(size2);
            
            mh.readByte();
            int size3 = mh.readNumber();
            author = mh.readString(size3);
            
            cout << title << "    " << "From: " << author << endl;
            cout << text << endl;
        } else {
            unsigned char fail = mh.readByte();
            if (fail == Protocol::ERR_NG_DOES_NOT_EXIST){
                cout << "Newsgroup doesn't exist!" << endl;
            } else if(fail == Protocol::ERR_ART_DOES_NOT_EXIST) {
            cout << "Article doesn't exist!" << endl;
            }
        }
        mh.readByte();
    } else {
        cerr << "Wrong answer received from server, connection terminated" << endl;
        exit(1);
    }
}

