#include <iostream>
#include "Fraction.h"

int main() {
    Fraction <int>f(8,32);
    Fraction <int>f2(2,3);
    cout << "premier test: " << f.affichage()<< endl;
    Fraction <int>fSimplifie = f.simplifier();
    cout << "simplifie: " << fSimplifie.affichage()<< endl;
    cout << "identite 1: " << f.identite(f) << endl;
    cout << "identite 2: " << f.identite(fSimplifie) << endl;
    cout << "identite 3: " << f.identite(f2) << endl;
    cout << "egalite 1: " << (f == f) << endl;
    cout << "egalite 2: " << (f == fSimplifie) << endl;
    cout << "egalite 3: " << (f == f2) << endl;
    Fraction<int> fAdd1 = f+f;
    Fraction<int> fAdd2 = f+fSimplifie;
    Fraction<int> fAdd3 = f2+f;
    cout << "addition 1: " << fAdd1.affichage() << endl;
    cout << "addition 2: " << fAdd2.affichage() << endl;
    cout << "addition 3: " << fAdd3.affichage() << endl;
    Fraction<int> fMul1 = f*f;
    Fraction<int> fMul2 = f*fSimplifie;
    Fraction<int> fMul3 = f2*f;
    cout << "multiplication 1: " << fMul1.affichage() << endl;
    cout << "multiplication 2: " << fMul2.affichage() << endl;
    cout << "multiplication 3: " << fMul3.affichage() << endl;
    f += f2;
    cout << f.affichage() << endl;
    f *= f2;
    cout << f.affichage() << endl;

    return 0;
}
