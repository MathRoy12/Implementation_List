/*
*  list.h
*
*  Auteur : Jean Goulet
*
*  Modifie par : Vincent Ducharme,  Date : Automne 2022
*  Modifié par : MF Auclair-Fortier, automne 2024
*
*/

#ifndef _LISTE_H_
#define _LISTE_H_

#include <ostream>
#include <cassert>
#include <initializer_list>
#include <utility>

///////////////////////////////////////////////////////////
/*Description de la representation

Chaine de cellules doublement chainées
Une cellule supplementaire a la fin,
nommee m_apres en memoire automatique
m_debut pointe sur la premiere cellule
m_dim contient le nombre d'elements dans la liste

iterator: pointeur sur la cellule concernee,
la fin est un pointeur sur la cellule de queue

reverse_iterator: pointeur sur la cellule qui
suit la cellule concernee
(rbegin: la queue, rend: la premiere)

Vous pouvez afficher la liste comme ceci :
afficher(std::cout, maListe);

*//////////////////////////////////////////////////////////


template<typename TYPE>
class liste {
private:
    struct cellule {
        TYPE m_contenu;
        cellule *m_suiv;
        cellule *m_prec;

        cellule(const TYPE &c, cellule *s = nullptr, cellule *p = nullptr)
                : m_contenu(c), m_suiv(s), m_prec(p) {}

        ~cellule() = default;
    };

    cellule *m_debut;
    cellule m_apres;
    size_t m_dim;

    //********* fonctions generatrices privees

    //inserer avant cette cellule
    cellule *insert(cellule *, const TYPE &);

    //enlever cette cellule
    cellule *erase(cellule *);

public:
    class iterateur;

    class iterateurInverse; // prendrait un const_reverse_iterator
    class iterateurVersConst;

    // Constructeurs
    // sans paramètre
    liste();

    // copieur
    liste(const liste &) = delete; // copieur desactivé
    liste(liste &&);

    // à partir d'une liste d'initialisation
    liste(std::initializer_list<TYPE>);

    // destructeur
    ~liste();

    liste &operator=(const liste &);

    iterateur insert(iterateur, const TYPE &);     // Retourne un iterator sur la position de la valeur ajoutee
    iterateurInverse insert(iterateurInverse, const TYPE &);

    iterateur erase(iterateur);                   // Retourne un iterator sur la position suivant celle supprimee
    iterateurInverse erase(iterateurInverse);

    void push_back(const TYPE &);

    void pop_back();

    void push_front(const TYPE &);

    void pop_front();

    const TYPE &back() const;

    const TYPE &front() const;

    TYPE &back();

    TYPE &front();

    void clear();

    size_t size() const;

    bool empty() const;

    iterateur begin();

    iterateur end();

    iterateurVersConst begin() const;

    iterateurVersConst end() const;

    iterateurVersConst cbegin() const;

    iterateurVersConst cend() const;

    iterateurInverse rbegin();

    iterateurInverse rend();


    //algorithmes
    void splice(iterateur, liste &);  // Transfere le contenu de la liste recue dans la liste courante
    void resize(size_t, const TYPE & = TYPE());

    void reverse();

    //fonction de mise au point (code jetable)
    friend void afficher(std::ostream &out, const liste<TYPE> &source) {
        typename liste<TYPE>::cellule *p = source.m_debut;
        size_t i = 0, skipde = source.m_dim, skipa = 0;
        if (skipde > 5)
            skipde = 5;
        if (skipa < source.m_dim - 5)
            skipa = source.m_dim - 5;
        out << "-----list " << &source << " (" << source.m_dim << " elements) -----\n";
        out << "m_debut: " << source.m_debut << "\n";
        while (p != &(source.m_apres)) {
            if (i < skipde || i > skipa)
                out << i << "=> <" << p->m_contenu
                    << "," << p->m_suiv << "," << p->m_prec
                    << ">\n";
            else if (i == skipde)
                out << "   .....\n";
            i++;
            p = p->m_suiv;
        }
        out << "m_apres: <???," << source.m_apres.m_suiv << "," << source.m_apres.m_prec << ">\n";
        out << "-------------------------------------------\n";
    }
};

///////////////////////////////////////////////////////////
//les classes d'iteration

template<typename TYPE>
class liste<TYPE>::iterateur {
    friend class liste<TYPE>;

private:
    cellule *m_pointeur = nullptr;

    iterateur() = default;

    iterateur(cellule *c) : m_pointeur(c) {}

public:

    TYPE &operator*() const { return m_pointeur->m_contenu; }

    TYPE *operator->() const { return &(m_pointeur->m_contenu); }

    iterateur &operator++() {
        // ++i
        m_pointeur = m_pointeur->m_suiv;
        return *this;
    }

    iterateur operator++(int) {
        // i++
        iterateur ret(*this);
        operator++();
        return ret;
    }

    iterateur &operator--() {
        // --i
        m_pointeur = m_pointeur->m_prec;
        return *this;
    }

    iterateur operator--(int) {
        // i--
        iterateur ret(*this);
        operator--();
        return ret;
    }

    bool operator==(const iterateur &droite) const {
        return m_pointeur == droite.m_pointeur;
    }

    bool operator!=(const iterateur &droite) const {
        return !(*this == droite);
    }
};


template<typename TYPE>
class liste<TYPE>::iterateurVersConst {
    friend class liste<TYPE>;

private:
    const cellule *m_pointeur = nullptr;

    iterateurVersConst() = default;

    iterateurVersConst(const cellule *c) : m_pointeur(c) {}

public:

    const TYPE &operator*() const { return m_pointeur->m_contenu; }

    const TYPE *operator->() const { return &(m_pointeur->m_contenu); }

    iterateurVersConst &operator++() {
        // ++i
        m_pointeur = m_pointeur->m_suiv;
        return *this;
    }

    iterateurVersConst operator++(int) {
        // i++
        iterateurVersConst ret(*this);
        operator++();
        return ret;
    }

    iterateurVersConst &operator--() {
        // --i
        m_pointeur = m_pointeur->m_prec;
        return *this;
    }

    iterateurVersConst operator--(int) {
        // i--
        iterateurVersConst ret(*this);
        operator--();
        return ret;
    }

    bool operator==(const iterateurVersConst &droite) const {
        return m_pointeur == droite.m_pointeur;
    }

    bool operator!=(const iterateurVersConst &droite) const {
        return !(*this == droite);
    }
};

// Ce fichier inclue la définition de la classe reverse_iterator, il faut mettre le include avant de l'utiliser
#include "listeIpl.h"


///////////////////////////////////////////////////////////
template<typename TYPE>
liste<TYPE>::liste()
        : m_apres(TYPE()), m_debut(&m_apres), m_dim(0) {}

template<typename TYPE>
liste<TYPE>::~liste() {
    clear();
}

//template <typename TYPE>
//listeBidir<TYPE>::listeBidir(const listeBidir& droite)
//    : listeBidir()
//{
//	// Une meilleure implémentation serait d'utiliser le constructeur par copie
//	// dans l'implémentation de l'opérateur= et coder directement le code de copie
//	// dans le constructeur par copie.
//    *this = droite;
//}

template<typename TYPE>
liste<TYPE>::liste(std::initializer_list<TYPE> droite) : liste() {
    for (const auto &x: droite)
        push_back(x);
}

template<typename TYPE>
typename liste<TYPE>::iterateur liste<TYPE>::insert(iterateur i, const TYPE &x) {
    return iterateur(insert(i.m_pointeur, x));
}

template<typename TYPE>
typename liste<TYPE>::iterateur liste<TYPE>::erase(iterateur i) {
    return iterateur(erase(i.m_pointeur));
}

template<typename TYPE>
typename liste<TYPE>::iterateurInverse liste<TYPE>::insert(iterateurInverse i, const TYPE &x) {
    insert(i.m_pointeur, x);
    return i;
}

template<typename TYPE>
typename liste<TYPE>::iterateurInverse liste<TYPE>::erase(iterateurInverse i) {
    erase(i.m_pointeur->m_prec);
    return i;
}

template<typename TYPE>
void liste<TYPE>::push_back(const TYPE &x) {
    insert(end(), x);
}

template<typename TYPE>
void liste<TYPE>::pop_back() {
    erase(rbegin());
}

template<typename TYPE>
void liste<TYPE>::push_front(const TYPE &x) {
    insert(begin(), x);
}

template<typename TYPE>
void liste<TYPE>::pop_front() {
    erase(begin());
}

template<typename TYPE>
const TYPE &liste<TYPE>::back() const {
    return *rbegin();
}

template<typename TYPE>
const TYPE &liste<TYPE>::front() const {
    return *begin();
}

template<typename TYPE>
TYPE &liste<TYPE>::back() {
    return *rbegin();
}

template<typename TYPE>
TYPE &liste<TYPE>::front() {
    return *begin();
}


template<typename TYPE>
void liste<TYPE>::clear() {
    while (!empty()) {
        m_debut = erase(m_debut);
    }
}

template<typename TYPE>
size_t liste<TYPE>::size() const {
    return m_dim;
}

template<typename TYPE>
bool liste<TYPE>::empty() const {
    return size() == 0;
}


///////////////////////////////////////////////////////////
// gestion de l'iteration
///////////////////////////////////////////////////////////

template<typename TYPE>
typename liste<TYPE>::iterateur liste<TYPE>::begin() {
    return iterateur(m_debut);
}

template<typename TYPE>
typename liste<TYPE>::iterateur liste<TYPE>::end() {
    return iterateur(&m_apres);
}

template<typename TYPE>
typename liste<TYPE>::iterateurVersConst liste<TYPE>::begin() const {
    return iterateurVersConst(m_debut);
}

template<typename TYPE>
typename liste<TYPE>::iterateurVersConst liste<TYPE>::end() const {
    return iterateurVersConst(&m_apres);
}

template<typename TYPE>
typename liste<TYPE>::iterateurVersConst liste<TYPE>::cbegin() const {
    return iterateurVersConst(m_debut);
}

template<typename TYPE>
typename liste<TYPE>::iterateurVersConst liste<TYPE>::cend() const {
    return iterateurVersConst(&m_apres);
}

///////////////////////////////////////////////////////////
// algorithmes
///////////////////////////////////////////////////////////


template<typename TYPE>
void liste<TYPE>::resize(size_t n, const TYPE &val) {
    iterateur it = begin();
    for (size_t i = 0; i < n; ++i, ++it)
        if (it == end())
            it = insert(it, val);
    while (it != end())
        it = erase(it);
}

template<typename TYPE>
void liste<TYPE>::splice(iterateur i, liste<TYPE> &lst) {
    if (lst.empty())
        return;
    cellule *ap = i.m_pointeur;
    cellule *av = ap->m_prec;
    cellule *pr = lst.m_debut;
    cellule *de = lst.m_apres.m_prec;
    av->m_suiv = pr;
    pr->m_prec = av;
    ap->m_prec = de;
    de->m_suiv = ap;
    if (ap == m_debut)
        m_debut = pr;
    //rendre L vide
    lst.m_debut = lst.m_apres.m_prec = lst.m_apres.m_suiv = &lst.m_apres;

    m_dim += lst.m_dim;
    lst.m_dim = 0;
}

///////////////////////////////////////////////////////////
//algorithme de tri avec des iterateurs generaux

template<typename iter>
void sort(iter deb, iter fin) {
    size_t nb = 0;
    iter i = deb, j = fin, pivot = deb;
    //choisir l'element du milieu comme pivot
    for (; i != j; ++nb, ++i)
        if (static_cast<void>(++nb), i == --j)
            break;
    if (nb < 2)
        return;  //rien a trier
    std::swap(*deb, *i);
    //separer la liste en deux  {<PIVOT,>=PIVOT}
    ++(i = deb);
    j = fin;
    while (i != j)
        if (*i < *pivot)
            ++i;
        else if (*--j < *pivot)
            std::swap(*i++, *j);
    --i;
    std::swap(*pivot, *i);
    //trier les deux sous-listes
    sort(deb, i);
    sort(j, fin);
}

///////////////////////////////////////////////////////////
#endif