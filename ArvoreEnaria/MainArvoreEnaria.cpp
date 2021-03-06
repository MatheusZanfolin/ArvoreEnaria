// MainArvoreEnaria.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <iostream>

#include "ArvoreEnaria.h"
#include "Inteiro.h"

using namespace std;

int main()
{
	Inteiro* _1 = new Inteiro(1);
	Inteiro* _3 = new Inteiro(3);
	Inteiro* _5 = new Inteiro(5);
	Inteiro* _8 = new Inteiro(8);
	Inteiro* _10 = new Inteiro(10);
	Inteiro* _22 = new Inteiro(22);
	Inteiro* _45 = new Inteiro(45);

	string entrada = "Ola";

	ArvoreEnaria* arvore = new ArvoreEnaria(2);

	cout << "Arvore enaria: \n\n";

	arvore->Guardar(_8);

	cout << *arvore << "\n\n";

	arvore->Guardar(_5);

	cout << *arvore << "\n\n";

	arvore->Guardar(_10);

	cout << *arvore << "\n\n";

	arvore->Guardar(_3);

	cout << *arvore << "\n\n";

	arvore->Guardar(_22);

	cout << *arvore << "\n\n";

	arvore->Guardar(_1);

	cout << *arvore << "\n\n";

	arvore->Guardar(_45);

	cout << *arvore << "\n\n";

	return 0;
}