#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"
#include "messagehandler.h"
#include "database.h"
#include "file-database.h"
#include "memory-database.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

bool listNewsGroups(const Connection* conn, Database& db);
bool createNewsGroup(const Connection* conn, Database& db);
bool deleteNewsGroup(const Connection* conn, Database& db);
bool listArticles(const Connection* conn, Database& db);
bool createArticle(const Connection* conn, Database& db);
bool deleteArticle(const Connection* conn, Database& db);
bool getArticle(const Connection* conn, Database& db);
void deregister(Server& s, std::shared_ptr<Connection> c);


bool listNewsGroups(const Connection* conn, Database& db){
    MessageHandler mh(conn);
    char c = mh.readByte();
    if(c != Protocol::COM_END){
        return false;
    }
    mh.writeByte(Protocol::ANS_LIST_NG);
    vector<pair<int, string>> newsGroups = db.getNewsGroups();
    mh.writeByte(Protocol::PAR_NUM);
    mh.writeNumber(newsGroups.size());
    for (pair<int, string> p : newsGroups) {
        mh.writeByte(Protocol::PAR_NUM);
        mh.writeNumber(p.first);
        mh.writeByte(Protocol::PAR_STRING);
        mh.writeNumber(p.second.length());
        mh.writeString(p.second);
    }
    mh.writeByte(Protocol::ANS_END);
    
    return true;
}



bool createNewsGroup(const Connection* conn, Database& db){
    MessageHandler mh(conn);
    char c = mh.readByte();
    if(c != Protocol::PAR_STRING){
        return false;
    }
    int n = mh.readNumber();
    string newsGroup = mh.readString(n);
    c = mh.readByte();
    if(c != Protocol::COM_END){
        return false;
    }
    
    mh.writeByte(Protocol::ANS_CREATE_NG);
    if(!db.newsGroupExists(newsGroup)){
        db.createNewsGroup(newsGroup);
		
        mh.writeByte(Protocol::ANS_ACK);
    }else{
        mh.writeByte(Protocol::ANS_NAK);
        mh.writeByte(Protocol::ERR_NG_ALREADY_EXISTS);
    }
    mh.writeByte(Protocol::ANS_END);
    return true;
}

bool deleteNewsGroup(const Connection* conn, Database& db){
    MessageHandler mh(conn);
    char c = mh.readByte();
    if(c != Protocol::PAR_NUM){
        return false;
    }
    int newsGroupNumber = mh.readNumber();
    c = mh.readByte();
    if(c != Protocol::COM_END){
        return false;
    }
    
    mh.writeByte(Protocol::ANS_DELETE_NG);
    if(db.newsGroupExists(newsGroupNumber)){
        db.deleteNewsGroup(newsGroupNumber);
        mh.writeByte(Protocol::ANS_ACK);
    } else {
        mh.writeByte(Protocol::ANS_NAK);
        mh.writeByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    mh.writeByte(Protocol::ANS_END);
    return true;
}

bool listArticles(const Connection* conn, Database& db){
    MessageHandler mh(conn);
    char c = mh.readByte();
    if(c != Protocol::PAR_NUM){
        return false;
    }
    int newsGroupNumber = mh.readNumber();
    c = mh.readByte();
    if(c != Protocol::COM_END){
        return false;
    }
    
    mh.writeByte(Protocol::ANS_LIST_ART);
    if(db.newsGroupExists(newsGroupNumber)){
        mh.writeByte(Protocol::ANS_ACK);
        vector<pair<int, string>> articles = db.getArticles(newsGroupNumber);
        mh.writeByte(Protocol::PAR_NUM);
        mh.writeNumber(articles.size());
        for(pair<int, string> p : articles){
            mh.writeByte(Protocol::PAR_NUM);
            mh.writeNumber(p.first);
            mh.writeByte(Protocol::PAR_STRING);
            string s = p.second;
            mh.writeNumber(s.length());
            mh.writeString(s);
        }
    }else {
        mh.writeByte(Protocol::ANS_NAK);
        mh.writeByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    mh.writeByte(Protocol::ANS_END);
    
    return true;
}

bool createArticle(const Connection* conn, Database& db){
    MessageHandler mh(conn);
    char c = mh.readByte();
    if(c != Protocol::PAR_NUM){
        cout << "!PAR_NUM" << endl;
        return false;
    }
    int newsGroupNumber = mh.readNumber();
    c = mh.readByte();
    if(c != Protocol::PAR_STRING){
        cout << "!PAR_STRING1" << endl;
        return false;
    }
    int titleN = mh.readNumber();
    string title = mh.readString(titleN);
    c = mh.readByte();
    if(c != Protocol::PAR_STRING){
        cout << "!PAR_STRING2" << endl;
        return false;
    }
    int authorN = mh.readNumber();
    string author = mh.readString(authorN);
    c = mh.readByte();
    if(c != Protocol::PAR_STRING){
        cout << "!PAR_STRING3" << endl;
        return false;
    }
    int textN = mh.readNumber();
    string text = mh.readString(textN);
    c = mh.readByte();
    if(c != Protocol::COM_END){
        cout << "!COM_END" << endl;
        return false;
    }
    
    
    mh.writeByte(Protocol::ANS_CREATE_ART);
    if(db.newsGroupExists(newsGroupNumber)){
        vector<pair<int, string>> articles = db.getArticles(newsGroupNumber);
        db.createArticle(newsGroupNumber, title, author, text);
        articles = db.getArticles(newsGroupNumber);
        mh.writeByte(Protocol::ANS_ACK);
    } else {
        mh.writeByte(Protocol::ANS_NAK);
        mh.writeByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    mh.writeByte(Protocol::ANS_END);
    return true;
}

bool deleteArticle(const Connection* conn, Database& db){
    MessageHandler mh(conn);
    char c = mh.readByte();
    if(c != Protocol::PAR_NUM){
        return false;
    }
    int newsGroupNumber = mh.readNumber();
    c = mh.readByte();
    if(c != Protocol::PAR_NUM){
        return false;
    }
    int articleNumber = mh.readNumber();
    c = mh.readByte();
    if(c != Protocol::COM_END){
        return false;
    }
    
    mh.writeByte(Protocol::ANS_DELETE_ART);
    if (db.newsGroupExists(newsGroupNumber)){
        if(db.articleExistsInNewsGroup(newsGroupNumber, articleNumber)){
            db.deleteArticle(newsGroupNumber, articleNumber);
            mh.writeByte(Protocol::ANS_ACK);
        } else {
            mh.writeByte(Protocol::ANS_NAK);
            mh.writeByte(Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    } else {
        mh.writeByte(Protocol::ANS_NAK);
        mh.writeByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    mh.writeByte(Protocol::ANS_END);
    
    return true;
}

bool getArticle(const Connection* conn, Database& db){
    MessageHandler mh(conn);
    char c = mh.readByte();
    if(c != Protocol::PAR_NUM){
        return false;
    }
    int newsGroupNumber = mh.readNumber();
    c = mh.readByte();
    if(c != Protocol::PAR_NUM){
        return false;
    }
    int articleNumber = mh.readNumber();
    c = mh.readByte();
    if(c != Protocol::COM_END){
        return false;
    }
    
    mh.writeByte(Protocol::ANS_GET_ART);
    if (db.newsGroupExists(newsGroupNumber)){
        if(db.articleExistsInNewsGroup(newsGroupNumber, articleNumber)){
            mh.writeByte(Protocol::ANS_ACK);
            vector<string> article = db.getArticleInNewsGroup(newsGroupNumber, articleNumber);
            string title = article.at(0);
            string author = article.at(1);
            string text = article.at(2);
            
            mh.writeByte(Protocol::PAR_STRING);
            mh.writeNumber(title.length());
            mh.writeString(title);
            
            mh.writeByte(Protocol::PAR_STRING);
            mh.writeNumber(author.length());
            mh.writeString(author);
            
            mh.writeByte(Protocol::PAR_STRING);
            mh.writeNumber(text.length());
            mh.writeString(text);
        } else {
            mh.writeByte(Protocol::ANS_NAK);
            mh.writeByte(Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    } else {
        mh.writeByte(Protocol::ANS_NAK);
        mh.writeByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    mh.writeByte(Protocol::ANS_END);
    return true;
}

void deregister(Server& s, std::shared_ptr<Connection> c){
    s.deregisterConnection(c);
    cout << "Client closed connection" << endl;
}


int main(int argc, char* argv[]){
	if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Server server(port);
	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}
    FileDatabase db = FileDatabase("filer");
	//MemoryDatabase db = MemoryDatabase();
	while (true) {
        auto conn = server.waitForActivity();
        Connection* c = conn.get();
        MessageHandler mh(c);
        bool ok;
		if (conn != nullptr) {
			try {
				char nbr = mh.readByte();
                switch (nbr){
                    case Protocol::COM_LIST_NG: ok=listNewsGroups(c, db); break;
                    case Protocol::COM_CREATE_NG: ok=createNewsGroup(c, db); break;
                    case Protocol::COM_DELETE_NG: ok=deleteNewsGroup(c, db); break;
                    case Protocol::COM_LIST_ART: ok=listArticles(c, db);break;
                    case Protocol::COM_CREATE_ART: ok=createArticle(c, db); break;
                    case Protocol::COM_DELETE_ART: ok=deleteArticle(c, db); break;
                    case Protocol::COM_GET_ART: ok=getArticle(c, db);break;
                    default: ok = false;
                }
                if(!ok){
                    deregister(server, conn);
                }
			} catch (ConnectionClosedException&) {
                deregister(server, conn);
			}
		} else {
			conn = make_shared<Connection>();
			server.registerConnection(conn);
			cout << "New client connects" << endl;
		}
	}
}
