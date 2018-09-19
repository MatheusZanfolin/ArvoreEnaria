#pragma once

#include "InformacaoDeArvoreEnaria.h"

#include <iostream>

using namespace std;

class Inteiro : public InformacaoDeArvoreEnaria
{
private:
	int valor;

public:
	Inteiro(int);

	int GetValor() const;

	int CompararCom(InformacaoDeArvoreEnaria*) const;

	ostream& ToString(ostream&) const;
};