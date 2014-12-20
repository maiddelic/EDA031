#include "database.h"

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <iostream>
#include <istream>
#include <fstream>

using namespace std;

class FileDatabase : public Database{
	
public:
    
    
    FileDatabase(string fileName);
    
	~FileDatabase() = default;
    
    
    void createNewsGroup(const string& ng);
       
	
    
    void deleteNewsGroup(const int& number);
       
	
    void createArticle(const int& newsGroup, const string& title,
                       const string& author, const string& text);
   
	
    void deleteArticle(const int& newsGroup, const int& artID);
	
	
	void writeFile();
	void readFile();

    
	
};