#ifndef DATABASE_H					// avoid repeated expansion
#define DATABASE_H

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Database {
	
public:
    
    virtual ~Database() = default;
	Database();
    
    virtual vector<pair<int, string>> getNewsGroups();
	
    
    virtual void createNewsGroup(const string& ng);
		
	
    bool newsGroupExists(const string& name);
		
	
    bool newsGroupExists(const int& number);

	
    virtual	void deleteNewsGroup(const int& number);
     
	
    vector<pair<int,string>> getArticles(const int& newsGroup);
	
	
    virtual void createArticle(const int& newsGroup, const string& title,
							   const string& author, const string& text);
    
	
    bool articleExistsInNewsGroup(const int& newsGroup, const int& artID);
     
	
    virtual void deleteArticle(const int& newsGroup, const int& artID);
		
	
    vector<string> getArticleInNewsGroup(const int& newsGroup, const int& artID);
		
	
	struct article{
		string title;
		string text;
		string author;
		article(string t, string txt, string aut) : 
				title(t), text(txt), author(aut){}
	};
	
	
protected:
	unordered_map<int, pair<string, unordered_map<int, article>>> db;
	int groupID;
	int artID;
        
};
#endif