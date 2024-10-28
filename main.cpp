#include <iostream>
#include "liste.h"
#include <list>

int main() {

    liste<int> lista;
    lista.push_back(10);
    lista.push_back(11);
    lista.push_front(12);
    lista.push_front(13);
    auto i = lista.rend();
    std::list<int> list;
    list.push_back(10);
    list.push_back(11);
    list.push_back(12);
    list.push_back(13);
    for (auto rit=lista.rbegin(); rit!=lista.rend(); ++rit)
        std::cout << ' ' << *rit;
    return 0;
}
