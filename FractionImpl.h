#ifndef INF2_LABO4_FRACTIONIMPL_H
#define INF2_LABO4_FRACTIONIMPL_H

using namespace std;

template <typename T>
Fraction<T>::Fraction(T numerateur, T denominateur) : numerateur(numerateur), denominateur(denominateur){ }

template <typename T> template <typename typeConverti>
typeConverti Fraction<T>::convertir() const {
    long double nombreConverti = (long double)numerateur/denominateur;

    return typeConverti(nombreConverti);
}

template <typename T>
Fraction<T> Fraction<T>::simplifier() const {

    // Cas triviaux: 0/X -> 0/1, 1/X -> 1/X, X/1 -> X/1
    if(numerateur == 0) {
        return Fraction(0, 1);
    }
    else if(numerateur == 1 || denominateur == 1) {
        return this;
    }

    T div = pgcd(numerateur, denominateur);

    // TODO: Ce if sert à optimiser 2 divisions par 1. Est-ce négligeable ?
    if(div != 1) {
        return Fraction<T>(numerateur/div, denominateur/div);
    }
    else {
        return this;
    }

}

template<typename T>
T Fraction<T>::pgcd (T x, T y) const{
    T reste = x%y;

    while(reste)
    {
        x = y;
        y = reste;
        reste = x%y;
    }

    return y;
}

#endif //INF2_LABO4_FRACTIONIMPL_H
