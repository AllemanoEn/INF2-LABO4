#include <iostream>
#include "Fraction.h"

template <typename T>
void estimationPI(Fraction<T> f){
    // Formule 1

    short signe = -1;
    long long count = 1;
    for(; count <= numeric_limits<T>::max(); ++count)
    {
        try
        {
            int num = 4 * signe;
            int denom = 1 + 2 * count;
            f += Fraction<T>((4 * signe) , (1 + 2 * count));
        }
        catch(...)
        {
            break;
        }
        signe *= -1;
    }

    cout << endl << "\tFormule 1 (après " << count <<" itérations) :"
         << endl << "\t" << f << " = " << fixed << f.template convertir<long double>() << endl;


    //Formule 2
    f = Fraction<T>(3 , 1);
    signe = 1;
    count = 1;

    for(; count <= numeric_limits<T>::max()/2; ++count)
    {

        try
        {
            unsigned i = 2 * count ;
            f += Fraction<T>( 4 * signe, i++ * i++ * i);
        }
        catch(...)
        {
            break;
        }
        signe *= -1;
    }

    cout << endl << "\tFormule 2 (apres " << count <<" iterations) :"
         << endl << "\t" << f << " = " << fixed << f.template convertir<long double>() << endl;

}

int main() {
    Fraction <int>f(8,32);
    Fraction <int>f2(2,3);
    cout << "f = " << f << " , f2 = " << f2 << endl;

    Fraction <int>fSimplifie = f.simplifier();
    cout << "Simplification de f : fs = " << f << " = " << fSimplifie << endl ;

    cout << endl << "Identité :" << endl;
    cout << "f et f : " << boolalpha << f.identite(f) << endl;
    cout << "f et fs: " << boolalpha << f.identite(fSimplifie) << endl;
    cout << "f et f2: " << boolalpha << f.identite(f2) << endl;

    cout << endl << "Egalité :" << endl;
    cout << "f == f : "  << boolalpha << (f == f) << endl;
    cout << "f == fs: "  << boolalpha << (f == fSimplifie) << endl;
    cout << "f == f2: "  << boolalpha << (f == f2) << endl;

    cout << endl << "Addition :" << endl;
    Fraction<int> fAdd1 = f+f;
    Fraction<int> fAdd2 = f+fSimplifie;
    Fraction<int> fAdd3 = f2+f;
    cout << "f + f  = " << fAdd1 << endl;
    cout << "f + fs = " << fAdd2 << endl;
    cout << "f + f2 = " << fAdd3 << endl;

    cout << endl << "Multiplication :" << endl;
    Fraction<int> fMul1 = f*f;
    Fraction<int> fMul2 = f*fSimplifie;
    Fraction<int> fMul3 = f2*f;
    cout << "f * f  = " << fMul1 << endl;
    cout << "f * fs = " << fMul2 << endl;
    cout << "f * f2 = " << fMul3 << endl;

    //// Estimations de avec <long long>
    cout << endl << "Estimations de PI avec des variables <long long> :" << endl;
    Fraction<long long>fSomme1(4,1);
    estimationPI(fSomme1);

    //// Estimations de avec <int>
    cout << endl << "Estimations de PI avec des variables <int> :" << endl;
    Fraction<int>fSomme2(4,1);
    estimationPI(fSomme2);

    return EXIT_SUCCESS;
}
