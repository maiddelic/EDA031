#include "connection.h"
#include "connectionclosedexception.h"
#include "messagehandler.h"
#include "clientcommandhandler.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <unordered_map>

using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}
	
	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	
	Connection conn(argv[1], port);
	if (!conn.isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	
    MessageHandler mh(&conn);
    ClientCommandHandler cch(mh);
    
	cout << "Welcome, sir!" << endl;
    cout << "Enter a command: ";
    
    string in;
    unordered_map<string, int> groups;
    int selGroup = -1;
	getline(cin, in)
	while (true) {
        try {
            stringstream ss(in);
            string command;
            ss >> command;
            if(command == "list") {
                string s2 = "";
                ss >> s2;
                if(s2 == "") {
                    selGroup = -1;
                    groups = cch.listNewsGroups();
                } else {
                    auto ng = groups.find(s2);
                    int nbr = 0;
                    if (groups.empty()) {
                        cout << "You need to type 'list' before accessing any specific newsgroup" << endl;
                    } else if (ng == groups.end()){
                        cout << "Newsgroup does not exist" << endl;
                    } else {
                        nbr = ng->second;
                        selGroup = nbr;
                        cch.listArticles(nbr);
                        groups.clear(); //ändring
                    }
                }
                
            } else if (command == "create") {
                string s2;
                ss >> s2;
                string s3 = "";
                ss >> s3;
                if(s3 != ""){
                    string s4 = "";
                    ss >> s4;
//                    string text;                    //ÄNDRING
//                    while(ss >> s4){                //ÄNDRING
//                        text = text + s4 + " ";     //ÄNDRING
//                    }                               //ÄNDRING
                    if (selGroup == -1){
                        cout << "You need to be in a newsgroup to create an article." << endl;
                    } else if (s4 == ""){
                        cout << "You need to enter title, author and article text to create an article." << endl;
                    } else {
                        cch.createArticle(selGroup, s2, s3, s4);   //ÄNDRING
                    }
                } else {
                    if(selGroup != -1) {
                        cout << "You can't create a newsgroup within a newsgroup, type 'list' to go to root before creating a newsgroup" << endl;
                    } else {
                        cch.createNewsGroup(s2);
                    }
                }
            
            } else if(command == "delete"){
                string s2;
                ss >> s2;
                if(selGroup == -1){
                    try{
                        int i = stoi(s2);
                        cch.deleteNewsGroup(i);
                    } catch (invalid_argument e){
                        cerr << "Invalid input, you need to enter the number of the newsgroup you want to delete." << endl;
                    }
                } else {
                    try{
                        int i = stoi(s2);
                        cch.deleteArticle(selGroup, i);
                    } catch (invalid_argument e){
                        cerr << "Invalid input, you need to enter the number of the article you want to delete." << endl;
                    }
                }
                
            } else if (command == "read"){
                string s2;
                int i;
                ss >> s2;
                try{
                    i = stoi(s2);
                    cch.getArticle(selGroup, i);
                } catch (invalid_argument){
                    cerr << "Invalid inputyou need to enter the number of the article you want to read." << endl;
                }
                
            } else {
                cout << "Unknown command, try again!" << endl;
            }
            
            ss.flush();
            cout << "Enter a command: ";
        
        } catch (ConnectionClosedException&) {
            cout << " No reply from server. Exiting." << endl;
            exit(1);
        }
	}
}
