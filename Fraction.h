#ifndef INF2_LABO4_FRACTION_H
#define INF2_LABO4_FRACTION_H

template <typename T>
class Fraction {
public:
    /**
     * Construit une fraction grâce au numerateur et au dénominateur
     * @param numerateur
     * @param denominateur
     */
    Fraction<T>(T numerateur, T denominateur);


    /**
     * Convertit une fraction dans un type précis
     * @tparam typeConverti le type dans lequel convertir la fraction
     * @return la fraction convertie
     */
    template <typename typeConverti>
    typeConverti convertir () const;

    /**
     * Simplifie la fraction
     * @return la fraction simplifiée
     * @details La fonction divise le numérateur et le dénominateur par leur PGCD puis retourne le résultat
     *          sous forme d'un nouvel objet
     */
    Fraction<T> simplifier () const;

private:
    T numerateur;
    T denominateur;

    /**
     * Calcule le PGCD de deux nombres
     * @param x le premier nombre
     * @param y le deuxième nombre
     * @return le PGCD de X et Y
     * @details La fonction utilise l'algorithme d'Euclide vu dans le cours ASD1. La version itérative de l'algorithme
     *          est utilisée car elle est plus efficace sur de grands nombres.
     */
    T pgcd (T x, T y) const;
};

#include "FractionImpl.h"
#endif //INF2_LABO4_FRACTION_H
