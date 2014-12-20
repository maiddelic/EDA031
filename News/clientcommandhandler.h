#include <string>
#include <unordered_map>

class ClientCommandHandler {
	
public:
    ClientCommandHandler(const MessageHandler& m) : mh(m) {}
    
//	~ClientCommandHandler();
    
    std::unordered_map<std::string, int> listNewsGroups();
    
    void createNewsGroup(const std::string& name);
    
    void deleteNewsGroup(const int num);
    
    void listArticles(const int num);
    
    void createArticle(const int num, const std::string& title, const std::string& author, const std::string& text);
    
    void deleteArticle(const int num, const int num2);
    
    void getArticle(const int num, const int num2);
	
private:
    MessageHandler mh;
};
