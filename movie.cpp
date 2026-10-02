#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Movie::Movie(string category, string name, double price,
             int qty, string genre, string rating)
    : Product(category, name, price, qty),
      genre_(genre), rating_(rating)
{
}

set<string> Movie::keywords() const
{
    set<string> words = parseStringToWords(name_);
    words.insert(convToLower(genre_));

    return words;
}

string Movie::displayString() const
{
    stringstream ss;

    ss << name_ << "\n";
    ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    ss << fixed << setprecision(2);
    ss << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Movie::dump(ostream& os) const
{
    Product::dump(os);
    os << genre_ << "\n";
    os << rating_ << "\n";
}