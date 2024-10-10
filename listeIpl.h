//
// Created by matou on 10/10/2024.
//

#ifndef IFT339_TP3_LISTEIPL_H
#define IFT339_TP3_LISTEIPL_H

#include "liste.h"

template<typename T>
class iterateurInverse{
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
        // ++i
        m_pointeur = m_pointeur->m_prec;
        return *this;
    }
    iterateurInverse operator++(int)
    {
        // i++
        iterateurInverse ret(*this);
        operator++();
        return ret;
    }
    iterateurInverse& operator--()
    {
        // --i
        m_pointeur = m_pointeur->m_suiv;
        return *this;
    }
    iterateurInverse operator--(int)
    {
        // i--
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
        return !(*this == droite);
    }
};

#endif //IFT339_TP3_LISTEIPL_H
