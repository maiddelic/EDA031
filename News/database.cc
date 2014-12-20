#include <unordered_map>
#include <string>
#include <vector>
#include "database.h"
#include <iostream>

using namespace std;

Database::Database(){}



vector<pair<int, string>> Database::getNewsGroups(){
	vector<pair<int, string>> groups;
	for(auto it = db.begin(); it != db.end(); ++it){
		groups.push_back(make_pair(it->first, it->second.first));
	}
    sort(groups.begin(), groups.end(), [](const pair<int,string>& p1, const pair<int,string>& p2){
        return p1.first < p2.first;
    });
	return groups;
}

void Database::createNewsGroup(const string& ng){
    cout << "DBCREATE!" << endl;
	unordered_map<int, article> newsG;
	auto p = make_pair(ng,newsG);
	++groupID;
	db.insert(make_pair(groupID,p));
}

bool Database::newsGroupExists(const string& name){
	for(auto it = db.begin(); it != db.end(); ++it){
		if(it->second.first == name){
			return true;
		}
	}
	return false;
}

bool Database::newsGroupExists(const int& number){
	auto it = db.find(number);
	return it != db.end();
}


void Database::deleteNewsGroup(const int& number){
	db.erase(number);
}

vector<pair<int,string>> Database::getArticles(const int& newsGroup) {
	vector<pair<int,string>> articles;
	auto it = db.find(newsGroup);
	auto &articleMap = it->second.second;
	for(auto it2 = articleMap.begin(); it2 != articleMap.end(); ++it2){
		articles.push_back(make_pair(it2->first, it2->second.title));
		
	}
    sort(articles.begin(), articles.end(), [](const pair<int,string>& p1, const pair<int,string>& p2){
        return p1.first < p2.first;
    });
	return articles;
}

void Database::createArticle(const int& newsGroup, const string& title,
						   const string& author, const string& text){
	auto it = db.find(newsGroup);
	auto &art = it->second.second;
	++artID;
	article a(title, text, author);
	art.insert(make_pair(artID, a));
}

bool Database::articleExistsInNewsGroup(const int& newsGroup, const int& artID){
	auto it = db.find(newsGroup);
	auto temp = it->second.second;
	return temp.find(artID) != temp.end();
}

void Database::deleteArticle(const int& newsGroup, const int& artID){
	auto it = db.find(newsGroup);
	auto &temp = it->second.second;
	temp.erase(artID);
}

vector<string> Database::getArticleInNewsGroup(const int& newsGroup, const int& artID){
	vector<string> art;
	auto it = db.find(newsGroup);
	auto temp = it->second.second;
	auto it2 = temp.find(artID);
	art.push_back(it2->second.title);
	art.push_back(it2->second.author);
	art.push_back(it2->second.text);
	return art;
}



