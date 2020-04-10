/// \file Fraction.h
/// \authors Enzo Allemano, David Pellissier, Michael Ruckstuhl
/// \date 10.04.2020
///
/// \brief \b Laboratoire \b 04
/// \brief Contient la classe Fraction
///
/// Remarque :
///
/// Compilateur : MinGw-g++ 6.3.0

#ifndef INF2_LABO4_FRACTION_H
#define INF2_LABO4_FRACTION_H

#include <iostream>

template<typename T>
class Fraction {

public:
    /**
     * Construit une fraction grâce au numerateur et au dénominateur
     * @param numerateur
     * @param denominateur
     * @throw invalid_argument si le denominateur est egal a zero
     * @throw overflow_error lorsque le numerateur et/ou denominateur devient positif
     */
    Fraction<T>(T numerateur, T denominateur);


    /**
     * Convertit une fraction dans un type precis
     * @tparam typeConverti le type dans lequel convertir la fraction
     * @return la fraction convertie
     */
    template<typename typeConverti>
    typeConverti convertir() const;

    /**
     * Simplifie la fraction
     * @return la fraction simplifiée
     * @details La fonction divise le numérateur et le dénominateur par leur PGCD puis retourne le résultat
     *          sous forme d'un nouvel objet
     */
    Fraction<T> simplifier() const;

    /**
     * Vérifie si deux fraction sont identique, c'est à dire: que les numérateurs et les dénominateur
     * des deux fractions sont égaux.
     * @param autreFraction
     * @return vrai si les numérateurs et dénominateurs sont égaux
     */
    bool identite(Fraction<T> autreFraction) const;

    /**
     * Vérifie que la fraction est égale à une autre fraction grâce à l'opérateur =
     * @param autreFraction
     * @return vrai si la fraction est égale à l'autre fraction. Sinon faux.
     */
    bool operator==(const Fraction<T> &autreFraction) const;

    /**
     * Multiplie la fraction à une autre grâce à l'opérateur *
     * @param autreFraction
     * @return la multiplication de la fraction dans sa forme réduite
     */
    Fraction<T> operator*(const Fraction<T> &autreFraction) const;

    /**
     * Additione la fraction à une autre
     * @param autreFraction
     * @return l'addition de la fraction dans sa forme réduite
     */
    Fraction<T> operator+(const Fraction<T> &autreFraction) const;

    /**
     * La fraction est additionnée à une autre grâce à l'opérateur +=
     * @param autreFraction
     */
    Fraction<T> operator+=(const Fraction<T> &autreFraction);

    /**
     * La fraction est multipliée à une autre grâce à l'opérateur *
     * @param autreFraction
     */
    Fraction<T> operator*=(const Fraction<T> &autreFraction);

    /**
     * Permet d'afficher correctement une fraction
     * @param lhs flux ostream
     * @param rhs Fraction en question
     * @return le flux correctement affiché
     */
    template <typename Y>
    friend std::ostream &operator<< (std::ostream &lhs, Fraction<Y>& rhs);

    /**
     * Accesseur du denominateur
     * @return le denominateur
     */
    T getDenominateur();

    /**
     * Accesseur du numerateur
     * @return le numerateur
     */
    T getNumerateur();


private:
    T numerateur;
    T denominateur;

    /**
     * Calcule le plus grand commun diviseur de deux nombres
     * @param x le premier nombre
     * @param y le deuxième nombre
     * @return le PGCD de X et Y
     * @details La fonction utilise l'algorithme d'Euclide vu dans le cours ASD1. La version itérative de l'algorithme
     *          est utilisée car elle est plus efficace sur les grands nombres.
     */
    T pgcd(T x, T y) const;

    /**
     * Calcule le plus petit commun multiple
     * @param x le premier nombre
     * @param y le deuxième nombre
     * @return le PPCM de X et Y
     * @details Le calcul du PGCD est: | x * y | / pgcd(x, y)
     */
    T ppcm(T x, T y) const ;

    /**
     * Verifie si a + b fait un overflow ou un underflow. Si ce n'est pas le cas
     * renvoie le resultat le l'addition
     * @param a
     * @param b
     * @return le resultat de l'addition
     * @throw overflow si l'addition fait un overflow
     * @throw underflow si l'addition fait un underflow
     */
    T additionCheck(T a, T b) const;

    /**
     * Effectue a * b dans la mesure ou le resultat ne risque pas de deborder des limites du type T
     * @param a
     * @param b
     * @return le produit de a et b
     * @throw overflow si la multiplication donne un nombre trop grand
     * @throw underflow si la multiplication renvoie un nombre trop petit
     */
    T safeMultipl(T a, T b) const;

};

#include "FractionImpl.h"

#endif //INF2_LABO4_FRACTION_H