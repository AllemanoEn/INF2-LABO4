/// \file FractionImpl.h
/// \authors Enzo Allemano, David Pellissier, Michael Ruckstuhl
/// \date 10.04.2020
///
/// Remarque :
///
/// Compilateur : MinGw-g++ 6.3.0

#ifndef INF2_LABO4_FRACTIONIMPL_H
#define INF2_LABO4_FRACTIONIMPL_H

#include "cmath"
#include "Fraction.h"
#include "limits"

using namespace std;

template<typename T>
Fraction<T>::Fraction(T numerateur, T denominateur) {
    if (denominateur == 0)
        throw invalid_argument("le denominateur ne peut etre 0");


    if(denominateur < 0){

        if(denominateur == numeric_limits<T>::min())
            throw overflow_error("Le denominateur a atteint la limite negative. Nous ne pouvons pas le rendre positif");

        if(numerateur == numeric_limits<T>::min())
            throw overflow_error("Le numerateur a atteint la limite negative. Nous ne pouvons pas le rendre positif");

        numerateur = - numerateur;
        denominateur = - denominateur;
    }

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

    return Fraction<T>(numerateur / div, denominateur / div);

}

template<typename T>
bool Fraction<T>::identite(const Fraction<T> &autreFraction) const {
    return (this->numerateur == autreFraction.numerateur && this->denominateur == autreFraction.denominateur);
}

template<typename T>
bool Fraction<T>::operator==(const Fraction<T> &autreFraction) const {
    Fraction<T> thisFractionSimplifiee = this->simplifier();
    Fraction<T> autreFractionSimplifiee = autreFraction.simplifier();

    return this->simplifier().identite(autreFraction.simplifier());

}

template<typename T>
Fraction<T> Fraction<T>::operator*(const Fraction<T> autreFraction) const {
    Fraction<T> thisFractionSimplifiee = this->simplifier();
    Fraction<T> autreFractionSimplifiee = autreFraction.simplifier();

    return Fraction<T>( safeMultipl(thisFractionSimplifiee.numerateur, autreFractionSimplifiee.numerateur),
                        safeMultipl(thisFractionSimplifiee.denominateur, autreFractionSimplifiee.denominateur)).simplifier();
}

template<typename T>
Fraction<T> Fraction<T>::operator*=(const Fraction<T> &autreFraction) {
    *this = *this * autreFraction;
    return *this;
}

template<typename T>
Fraction<T> Fraction<T>::operator+(const Fraction<T> autreFraction) const{

    Fraction<T> lhsFractionSimplifiee = this->simplifier();
    Fraction<T> rhsFractionSimplifiee = autreFraction.simplifier();

    if (lhsFractionSimplifiee.denominateur != rhsFractionSimplifiee.denominateur) {

        T ppcmDenominateur = ppcm(lhsFractionSimplifiee.denominateur, rhsFractionSimplifiee.denominateur);
        T thisMultiplicateur = ppcmDenominateur / lhsFractionSimplifiee.denominateur;
        T autreMultiplicateur = ppcmDenominateur / rhsFractionSimplifiee.denominateur;

        lhsFractionSimplifiee.numerateur = safeMultipl(lhsFractionSimplifiee.numerateur, thisMultiplicateur);
        lhsFractionSimplifiee.denominateur = safeMultipl(lhsFractionSimplifiee.denominateur, thisMultiplicateur);
        rhsFractionSimplifiee.numerateur = safeMultipl(rhsFractionSimplifiee.numerateur, autreMultiplicateur);
        // le dénominateur de autreFractionSimplifiee n'est pas utilisé
    }

    T resultatNumerateur = safeAdd(lhsFractionSimplifiee.numerateur, rhsFractionSimplifiee.numerateur);
    T resultatDenominateur = lhsFractionSimplifiee.denominateur;

    return Fraction<T>(resultatNumerateur, resultatDenominateur).simplifier();

}

template<typename T>
Fraction<T> Fraction<T>::operator+=(const Fraction<T> &autreFraction) {
    *this = *this + autreFraction;
    return *this;
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

template<typename T>
T Fraction<T>::ppcm(T x, T y) const {
    T produit = safeMultipl(x, y);

    if(produit < 0){
        produit = safeMultipl(produit, -1);
    }

    return T( produit / pgcd(x,y) );
}

template<typename T>
T Fraction<T>::getDenominateur() const {
    return this->denominateur;
}

template<typename T>
T Fraction<T>::getNumerateur() const {
    return this->numerateur;
}

template<typename T>
std::ostream &operator<<(std::ostream &lhs, Fraction<T>& rhs) {
    return lhs << rhs.getNumerateur() << '/' << rhs.getDenominateur();
}

template<typename T>
T Fraction<T>::safeAdd(T a, T b) const {
    if ((b > 0) && (a > numeric_limits<T>::max() - b))
        throw overflow_error("l addition fait un overflow");
    if ((b < 0) && (a < numeric_limits<T>::min() - b))
        throw underflow_error("l addition fait un underflow");
    return a + b;
}

template<typename T>
T Fraction<T>::safeMultipl(T a, T b) const {

    // Car selon le compilateur utilisé, la fonction abs() ne prend pas les entiers non signés
    long long signedA =  a,
              signedB = b;

    if (((a < 0 && b < 0) || (a > 0 && b > 0)) &&
        ( (unsigned long long) abs(signedB) > ( numeric_limits<T>::max() / (unsigned long long) abs(signedB) )))
    {
        throw overflow_error("la multiplication fait un overflow");
    }

    else if(((a > 0 && b < 0) || (a < 0 && b > 0)) &&
            ( (unsigned long long)abs(signedB) > ( (unsigned long long)abs( (long long) numeric_limits<T>::min()) / abs(signedA) )))
    {
        throw underflow_error("la multiplication fait un underflow");
    }

    return a * b;
}


#endif //INF2_LABO4_FRACTIONIMPL_H