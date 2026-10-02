#include "mydatastore.h"
#include "util.h"
#include <iostream>

using namespace std;

MyDataStore::~MyDataStore()
{
    for (size_t i = 0; i < products_.size(); i++) {
        delete products_[i];
    }

    for (map<string, User*>::iterator it = users_.begin();
         it != users_.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);

    set<string> words = p->keywords();

    for (set<string>::iterator it = words.begin();
         it != words.end(); ++it) {
        keywordIndex_[convToLower(*it)].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    users_[convToLower(u->getName())] = u;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    set<Product*> matches;

    for (size_t i = 0; i < terms.size(); i++) {
        string term = convToLower(terms[i]);
        set<Product*> termMatches;

        map<string, set<Product*> >::iterator it =
            keywordIndex_.find(term);

        if (it != keywordIndex_.end()) {
            termMatches = it->second;
        }

        if (i == 0) {
            matches = termMatches;
        }
        else if (type == 0) {
            matches = setIntersection(matches, termMatches);
        }
        else {
            matches = setUnion(matches, termMatches);
        }
    }

    return vector<Product*>(matches.begin(), matches.end());
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>\n";

    for (size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile);
    }

    ofile << "</products>\n";
    ofile << "<users>\n";

    for (map<string, User*>::iterator it = users_.begin();
         it != users_.end(); ++it) {
        it->second->dump(ofile);
    }

    ofile << "</users>\n";
}

bool MyDataStore::addToCart(string username, Product* p)
{
    username = convToLower(username);

    if (users_.find(username) == users_.end()) {
        return false;
    }

    carts_[username].push_back(p);
    return true;
}

bool MyDataStore::viewCart(string username)
{
    username = convToLower(username);

    if (users_.find(username) == users_.end()) {
        return false;
    }

    vector<Product*>& cart = carts_[username];

    for (size_t i = 0; i < cart.size(); i++) {
        cout << "Item " << i + 1 << endl;
        cout << cart[i]->displayString() << endl;
        cout << endl;
    }

    return true;
}

bool MyDataStore::buyCart(string username)
{
    username = convToLower(username);

    if (users_.find(username) == users_.end()) {
        return false;
    }

    User* user = users_[username];
    vector<Product*>& cart = carts_[username];
    vector<Product*> remaining;

    for (size_t i = 0; i < cart.size(); i++) {
        Product* p = cart[i];

        if (p->getQty() > 0 &&
            user->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            user->deductAmount(p->getPrice());
        }
        else {
            remaining.push_back(p);
        }
    }

    cart = remaining;
    return true;
}