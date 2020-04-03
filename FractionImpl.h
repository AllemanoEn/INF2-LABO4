#ifndef INF2_LABO4_FRACTIONIMPL_H
#define INF2_LABO4_FRACTIONIMPL_H

#include "cmath"
#include "Fraction.h"


using namespace std;

template<typename T>
Fraction<T>::Fraction(T numerateur, T denominateur) {
    this->numerateur = numerateur;
    this->denominateur = denominateur;
}

template<typename T>
template<typename typeConverti>
typeConverti Fraction<T>::convertir() const {
    long double nombreConverti = (long double) numerateur / denominateur;

    return typeConverti(nombreConverti);
}

template<typename T>
Fraction<T> Fraction<T>::simplifier() const {

    // Cas triviaux: 0/X -> 0/1, 1/X -> 1/X, X/1 -> X/1
    if (numerateur == 0) {
        return Fraction(0, 1);
    } else if (numerateur == 1 || denominateur == 1) {
        return Fraction(numerateur, denominateur);
    }

    T div = pgcd(numerateur, denominateur);

    // TODO: Ce if sert à optimiser 2 divisions par 1. Est-ce négligeable ?
    if (div != 1) {
        return Fraction<T>(numerateur / div, denominateur / div);
    } else {
        return Fraction(numerateur, denominateur);
    }

}

template<typename T>
bool Fraction<T>::identite(Fraction<T> autreFraction) const{
    return (this->numerateur == autreFraction.numerateur && this->denominateur == autreFraction.denominateur);
}

template<typename T>
bool Fraction<T>::operator==(const Fraction<T> &autreFraction) const {
    Fraction<T> thisFractionSimplifiee = this->simplifier();
    Fraction<T> autreFractionSimplifiee = autreFraction.simplifier();
    return (thisFractionSimplifiee.numerateur == autreFractionSimplifiee.numerateur &&
            thisFractionSimplifiee.denominateur == autreFractionSimplifiee.denominateur);
}

template<typename T>
Fraction<T> Fraction<T>::operator*(const Fraction<T> &autreFraction) const {
    Fraction<T> thisFractionSimplifiee = this->simplifier();
    Fraction<T> autreFractionSimplifiee = autreFraction.simplifier();
    return Fraction<T>(thisFractionSimplifiee.numerateur * autreFractionSimplifiee.numerateur,
                       thisFractionSimplifiee.denominateur * autreFractionSimplifiee.denominateur);
}

template<typename T>
void Fraction<T>::operator*=(const Fraction<T> &autreFraction) {
    Fraction<T> thisFractionSimplifiee = this->simplifier();
    Fraction<T> autreFractionSimplifiee = autreFraction.simplifier();
    this->numerateur = thisFractionSimplifiee.numerateur * autreFractionSimplifiee.numerateur;
    this->denominateur = thisFractionSimplifiee.denominateur * autreFractionSimplifiee.denominateur;
}

template<typename T>
Fraction<T> Fraction<T>::operator+(const Fraction<T> &autreFraction) const {
    Fraction<T> thisFractionSimplifiee = this->simplifier();
    Fraction<T> autreFractionSimplifiee = autreFraction.simplifier();
    if (thisFractionSimplifiee.denominateur != autreFractionSimplifiee.denominateur) {
        thisFractionSimplifiee.numerateur *= autreFractionSimplifiee.denominateur;
        autreFractionSimplifiee.numerateur *= thisFractionSimplifiee.denominateur;
        thisFractionSimplifiee.denominateur *= autreFractionSimplifiee.denominateur;
    }
    return Fraction<T>(thisFractionSimplifiee.numerateur + autreFractionSimplifiee.numerateur,
                       thisFractionSimplifiee.denominateur);
}

template<typename T>
void Fraction<T>::operator+=(const Fraction<T> &autreFraction) {
    Fraction<T> thisFractionSimplifiee = this->simplifier();
    Fraction<T> autreFractionSimplifiee = autreFraction.simplifier();
    if (thisFractionSimplifiee.denominateur != autreFractionSimplifiee.denominateur) {
        thisFractionSimplifiee.numerateur *= autreFractionSimplifiee.denominateur;
        autreFractionSimplifiee.numerateur *= thisFractionSimplifiee.denominateur;
        thisFractionSimplifiee.denominateur *= autreFractionSimplifiee.denominateur;
    }
    this->numerateur = thisFractionSimplifiee.numerateur + autreFractionSimplifiee.numerateur;
    this->denominateur = thisFractionSimplifiee.denominateur;
}

template<typename T>
T Fraction<T>::pgcd(T x, T y) const {
    T reste = x % y;

    while (reste) {
        x = y;
        y = reste;
        reste = x % y;
    }

    return y;
}

#endif //INF2_LABO4_FRACTIONIMPL_H
