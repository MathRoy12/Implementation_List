//
// Created by matou on 10/10/2024.
//

#ifndef IFT339_TP3_LISTEIPL_H
#define IFT339_TP3_LISTEIPL_H

#include "liste.h"

template<typename T>
class liste<T>::iterateurInverse{
    friend class liste<T>;
private:
     liste<T>::cellule* m_pointeur = nullptr;

    iterateurInverse() = default;
    iterateurInverse(liste<T>::cellule* c) :m_pointeur(c) {}

public:
    T& operator*()const { return m_pointeur->m_contenu; }
    T* operator->()const { return &(m_pointeur->m_contenu); }
    iterateurInverse& operator++()
    {
        m_pointeur = m_pointeur->m_prec;
        return *this;
    }
    iterateurInverse operator++(int)
    {
        iterateurInverse ret(*this);
        operator++();
        return ret;
    }
    iterateurInverse& operator--()
    {
        m_pointeur = m_pointeur->m_suiv;
        return *this;
    }
    iterateurInverse operator--(int)
    {
        iterateurInverse ret(*this);
        operator--();
        return ret;
    }

    bool operator==(const iterateurInverse&droite)const
    {
        return m_pointeur == droite.m_pointeur;
    }

    bool operator!=(const iterateurInverse&droite)const
    {
        return *this != droite;
    }
};

//Christian
template<typename T>
typename liste<T>::cellule *liste<T>::insert(liste::cellule * c, const T & element) {
    cellule * newCellule = new liste<T>::cellule(element);

    newCellule->m_suiv = c;
    if(c->m_prec == nullptr) {
        c->m_prec = newCellule;
        m_debut = c->m_prec;
    }
    else {
        c->m_prec->m_suiv = newCellule;
        c->m_prec = newCellule;
    }

    m_dim++;

    return newCellule;
}

//Mathieu
// TODO tester
template<typename T>
typename liste<T>::cellule *liste<T>::erase(liste::cellule * c) {
    cellule * c_suivant = c->m_suiv;
    c_suivant->m_prec = c->m_prec;

    delete c;
    m_dim--;

    return c_suivant;
}

template<typename T>
typename liste<T>::iterateurInverse liste<T>::rbegin() {
    return liste::iterateurInverse(&m_apres);
}

template<typename T>
typename liste<T>::iterateurInverse liste<T>::rend() {
    return liste::iterateurInverse(m_debut);
}

//Mathieu
template<typename T>
liste<T> &liste<T>::operator=(const liste & lst) {
    if (lst == *this){
        return *this;
    }

    this->clear();
    for (iterateur i = lst.begin();  i != i.end() ; i++) {
        this->push_back(*i);
    }
    return *this;
}

//Christian
template<typename T>
void liste<T>::reverse() {

}

#endif //IFT339_TP3_LISTEIPL_H
