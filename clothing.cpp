#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

Clothing::Clothing(string category, string name, double price,
                   int qty, string size, string brand)
    : Product(category, name, price, qty),
      size_(size), brand_(brand)
{
}

set<string> Clothing::keywords() const
{
    set<string> nameWords = parseStringToWords(name_);
    set<string> brandWords = parseStringToWords(brand_);

    return setUnion(nameWords, brandWords);
}

string Clothing::displayString() const
{
    stringstream ss;

    ss << name_ << "\n";
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    ss << fixed << setprecision(2);
    ss << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Clothing::dump(ostream& os) const
{
    Product::dump(os);
    os << size_ << "\n";
    os << brand_ << "\n";
}