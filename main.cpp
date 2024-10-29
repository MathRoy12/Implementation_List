#include <iostream>
#include "liste.h"
#include <list>

int main() {

    liste<int> lista;
    lista.push_back(10);
    lista.push_back(11);
    lista.push_front(13);
    lista.push_front(12);
    afficher(std::cout,lista);
    sort(lista.rbegin(),lista.rend());
    afficher(std::cout,lista);
    return 0;
}
