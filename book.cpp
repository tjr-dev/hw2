#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Book::Book(string category, string name, double price,
           int qty, string isbn, string author)
    : Product(category, name, price, qty),
      isbn_(isbn), author_(author)
{
}

set<string> Book::keywords() const
{
    set<string> nameWords = parseStringToWords(name_);
    set<string> authorWords = parseStringToWords(author_);

    set<string> words = setUnion(nameWords, authorWords);
    words.insert(convToLower(isbn_));

    return words;
}

string Book::displayString() const
{
    stringstream ss;

    ss << name_ << "\n";
    ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    ss << fixed << setprecision(2);
    ss << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Book::dump(ostream& os) const
{
    Product::dump(os);
    os << isbn_ << "\n";
    os << author_ << "\n";
}