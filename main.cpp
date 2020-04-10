#include <iostream>
#include "Fraction.h"

//Cette fonction nous permet (sans copier de code) de tester les estimations de PI avec plusieurs type.
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
    cout << "Les tests commencent: " << endl << endl;
    cout << "On verifie d'abord que les fonctions fonctionnes avec le type int :" << endl << endl;
    cout << "On construit les deux fractions suivantes :" << endl;
    cout << "Fraction <int>f(8,32);" << endl;
    cout << "Fraction <int>f2(2,3);" << endl;
    Fraction<int> f(8, 32);
    Fraction<int> f2(2, 3);
    cout << "cout << \"f = \" << f << \" , f2 = \" << f2 << endl; :" << endl;
    cout << "f = " << f << " , f2 = " << f2 << endl << endl;

    Fraction<int> fSimplifie = f.simplifier();
    cout << "Fraction <int>fSimplifie = f.simplifier(); :" << endl;
    cout << "Simplification de f : fs = " << f << " = " << fSimplifie << endl;

    cout << endl << "Identite :" << endl;
    cout << "f et f : " << boolalpha << f.identite(f) << endl;
    cout << "f et fs: " << boolalpha << f.identite(fSimplifie) << endl;
    cout << "f et f2: " << boolalpha << f.identite(f2) << endl;

    cout << endl << "Egalite :" << endl;
    cout << "f == f : " << boolalpha << (f == f) << endl;
    cout << "f == fs: " << boolalpha << (f == fSimplifie) << endl;
    cout << "f == f2: " << boolalpha << (f == f2) << endl;

    cout << endl << "Addition :" << endl;
    Fraction<int> fAdd1 = f + f;
    Fraction<int> fAdd2 = f + fSimplifie;
    Fraction<int> fAdd3 = f2 + f;
    cout << "f + f  = " << fAdd1 << endl;
    cout << "f + fs = " << fAdd2 << endl;
    cout << "f + f2 = " << fAdd3 << endl;

    cout << endl << "Multiplication :" << endl;
    Fraction<int> fMul1 = f * f;
    Fraction<int> fMul2 = f * fSimplifie;
    Fraction<int> fMul3 = f2 * f;
    cout << "f * f  = " << fMul1 << endl;
    cout << "f * fs = " << fMul2 << endl;
    cout << "f * f2 = " << fMul3 << endl;

    cout << endl << "Addition +=:" << endl;
    f += f;
    cout << "f += f :" << f << endl;

    cout << endl << "Multiplication *=:" << endl;
    f *= f;
    cout << "f *= f :" << f << endl;

    cout << endl << endl << "On verifie quelques overflow/underflow: " << endl << endl;

    cout << "Fraction<char> charF1(64,7);" << endl;
    cout << "Fraction<char> charF2(2,16);" << endl;
    cout << "On les multiplie : " << endl;
    Fraction<char> charF1(64, 1);
    Fraction<char> charF2(2, 1);
    try {
        charF1 * charF2;
    } catch (overflow_error &e) {
        cout << e.what();
    }
    cout << endl << endl << "Fraction<long long> longlongF1(numeric_limits<long long>::min(),1);" << endl;
    cout << "Fraction<long long> longlongF2(-2,1);" << endl;
    cout << "On les additionnes : " << endl;
    Fraction<long long> longlongF1(numeric_limits<long long>::min(), 1);
    Fraction<long long> longlongF2(-2, 1);
    try {
        longlongF1 + longlongF2;
    } catch (underflow_error &e) {
        cout << e.what();
    }
    cout << endl << endl << "Un dernier avec un UNSIGNED long" << endl;
    cout << "Fraction<unsigned long> ulF1(numeric_limits<unsigned long>::max(), 1);" << endl;
    cout << "Fraction<unsigned long> ulF2(2, 1);" << endl;
    cout << "On les multiplie : " << endl;
    Fraction<unsigned long> ulF1(numeric_limits<unsigned long>::max(), 1);
    Fraction<unsigned long> ulF2(2, 1);
    try {
        ulF1 + ulF2;
    } catch (overflow_error &e) {
        cout << e.what();
    }
    cout << endl << endl;


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

