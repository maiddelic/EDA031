#include "database.h"

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace std;

class MemoryDatabase : public Database{
	
public:
    
    MemoryDatabase(){
    	groupID = 0;
        artID = 0;
    }
	
    ~MemoryDatabase(){}
    
	void createNewsGroup(const string& ng){
        Database::createNewsGroup(ng);
	}
	
    void deleteNewsGroup(const int& number){
        Database::deleteNewsGroup(number);
	}
	
    void createArticle(const int& newsGroup, const string& title,
                       const string& author, const string& text){
        Database::createArticle(newsGroup, title, author, text);
	}
	
    void deleteArticle(const int& newsGroup, const int& artID){
        Database::deleteArticle(newsGroup, artID);
	}
    
};