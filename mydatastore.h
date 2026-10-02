#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>

class MyDataStore : public DataStore {
public:
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(
        std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    bool addToCart(std::string username, Product* p);
    bool viewCart(std::string username);
    bool buyCart(std::string username);

private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*> > keywordIndex_;
    std::map<std::string, std::vector<Product*> > carts_;
};

#endif