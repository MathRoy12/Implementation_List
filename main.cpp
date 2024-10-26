#include <iostream>
#include "liste.h"

int main() {

    liste<int> lista;
    lista.push_back(2);
    lista.push_back(4);
    lista.push_back(6);
    lista.push_front(8);
    lista.push_front(10);
    afficher(std::cout, lista);

    //std::cout << "Hello, World!" << std::endl;
    return 0;
}
