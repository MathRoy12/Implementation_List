#include <iostream>
#include "liste.h"

int main() {

    liste<int> lista;
    lista.push_back(10);
    lista.push_back(11);
    lista.push_front(12);
    lista.push_front(13);
    auto i = lista.begin();
    i++;
    lista.erase(i);
    afficher(std::cout,lista);
    liste<int> listb;
    listb = lista;
    afficher(std::cout,listb);

    return 0;
}
