#ifndef INF2_LABO4_FRACTIONIMPL_H
#define INF2_LABO4_FRACTIONIMPL_H

#include "cmath"
#include "Fraction.h"
#include "limits"

using namespace std;

template<typename T>
Fraction<T>::Fraction(T numerateur, T denominateur) {
    if(denominateur == 0)
        throw invalid_argument("le denominateur ne peut etre 0");

    if(denominateur < 0){

        if(denominateur == numeric_limits<T>::min())
            throw overflow_error("Le denominateur a atteints la limite negative. Nous ne pouvons pas le rendre positif");

        if(numerateur == numeric_limits<T>::min())
            throw overflow_error("Le numerateur a atteints la limite negative. Nous ne pouvons pas le rendre positif");

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
bool Fraction<T>::identite(Fraction<T> autreFraction) const{
    return (this->numerateur == autreFraction.numerateur && this->denominateur == autreFraction.denominateur);
}

template<typename T>
bool Fraction<T>::operator==(const Fraction<T> &autreFraction) const {
     Fraction<T> thisFractionSimplifiee = this->simplifier();
     Fraction<T> autreFractionSimplifiee = autreFraction.simplifier();

     return this->simplifier().identite(autreFraction.simplifier());

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
Fraction<T> Fraction<T>::operator+(const Fraction<T> &autreFraction) const{

    Fraction<T> lhsFractionSimplifiee = this->simplifier();
    Fraction<T> rhsFractionSimplifiee = autreFraction.simplifier();

    if (lhsFractionSimplifiee.denominateur != rhsFractionSimplifiee.denominateur) {

        int ppcmDenominateur = ppcm(lhsFractionSimplifiee.denominateur, rhsFractionSimplifiee.denominateur);
        int thisMultiplicateur = ppcmDenominateur / lhsFractionSimplifiee.denominateur;
        int autreMultiplicateur = ppcmDenominateur / rhsFractionSimplifiee.denominateur;

        lhsFractionSimplifiee.numerateur *= thisMultiplicateur;
        lhsFractionSimplifiee.denominateur *= thisMultiplicateur;
        rhsFractionSimplifiee.numerateur *= autreMultiplicateur;
        // le dénominateur de autreFractionSimplifiee n'est pas utilisé
    }

    T resultatNumerateur = lhsFractionSimplifiee.numerateur + rhsFractionSimplifiee.numerateur;
    T resultatDenominateur = lhsFractionSimplifiee.denominateur;

    return Fraction<T>(resultatNumerateur, resultatDenominateur);

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
    long long produitAbs = abs(x * y);

    return T( produitAbs / pgcd(x,y) );
}

template<typename T>
T Fraction<T>::getDenominateur() {
    return this->denominateur;
}

template<typename T>
T Fraction<T>::getNumerateur() {
    return this->numerateur;
}

template <typename T>
std::ostream &operator<< (std::ostream &lhs, Fraction<T> rhs) {
    return lhs << rhs.getNumerateur() << '/' << rhs.getDenominateur();
}

#endif //INF2_LABO4_FRACTIONIMPL_H
