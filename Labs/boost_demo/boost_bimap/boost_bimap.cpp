#include <string_view>

#include <boost/bimap.hpp>

#include "dbg.hpp"

using bimap = boost::bimap<std::string_view, int>;

int main() {

    bimap animales{};

    animales.insert({ "cat", 0 });
    animales.insert({ "dog", 1 });
    animales.insert({ "shark", 0 });
    animales.insert({ "spider", 0 });
    animales.insert({ "cat", 1 });

    dbg(animales.left.count("cat"));
    dbg(animales.right.count(0));

    return 0;
}
