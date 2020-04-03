#include <iostream>
#include "Fraction.h"

int main() {

    Fraction <int>f(8,32);
    Fraction <int>f2(2,3);
    cout << "premier test: " << f << endl;
    Fraction <int>fSimplifie = f.simplifier();
    cout << "simplifie: " << fSimplifie << endl;
    cout << "identite 1: " << f.identite(f) << endl;
    cout << "identite 2: " << f.identite(fSimplifie) << endl;
    cout << "identite 3: " << f.identite(f2) << endl;
    cout << "egalite 1: " << (f == f) << endl;
    cout << "egalite 2: " << (f == fSimplifie) << endl;
    cout << "egalite 3: " << (f == f2) << endl;


    Fraction<int> fAdd1 = f+f;
    Fraction<int> fAdd2 = f+fSimplifie;
    Fraction<int> fAdd3 = f2+f;
    cout << "addition 1: " << fAdd1 << endl;
    cout << "addition 2: " << fAdd2 << endl;
    cout << "addition 3: " << fAdd3 << endl;

    Fraction<int> fMul1 = f*f;
    Fraction<int> fMul2 = f*fSimplifie;
    Fraction<int> fMul3 = f2*f;
    cout << "multiplication 1: " << fMul1 << endl;
    cout << "multiplication 2: " << fMul2 << endl;
    cout << "multiplication 3: " << fMul3 << endl;

    //// Estimation de PI 1
    Fraction<long long>fSomme(4,1);
    short signe = 1;
    long long count = 0;
    for(; count <= numeric_limits<long long>::max(); ++count)
    {

        try
        {
            fSomme += Fraction<long long>(4 * signe , (1 + 2 * count));
        }
        catch(...)
        {
            break;
        }
        signe *= -1;
    }
    count++; // Pour que le comptage commence à 1 et pas à zéro
    cout << "Résultat de l'estimation de PI 1 (après " << count <<" itérations :"
         <<  endl << fSomme << " = " << fSomme.convertir<long double>();

    //// Estimation de PI 2
    fSomme = Fraction<long long>(3 , 1);
    signe = 1;
    count = 1;

    for(; count <= numeric_limits<long long>::max()/2; ++count)
    {

        try
        {
            unsigned i = 2 * count ;
            fSomme += Fraction<long long>( 4 * signe, i++ * i++ * i);
        }
        catch(...)
        {
            break;
        }
        signe *= -1;
    }

    cout << "Résultat de l'estimation de PI 1 (après " << count <<" itérations :"
         <<  endl << fSomme << " = " << fSomme.convertir<long double>();


    return 0;
}
