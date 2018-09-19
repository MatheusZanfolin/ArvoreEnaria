#pragma once

#include <iostream>

#include "NoDeArvoreEnaria.h"
#include "InformacaoDeArvoreEnaria.h"
#include <exception>

using namespace std;

class ArvoreEnaria
{
private:
	NoDeArvoreEnaria* raiz;

	int qtosPtrs;

public:
	ArvoreEnaria(int);

	void Guardar(InformacaoDeArvoreEnaria*);
	bool Remover(InformacaoDeArvoreEnaria*);

	NoDeArvoreEnaria* GetRaiz() const;

	virtual ostream& ToString(ostream&) const;

	friend ostream& operator<<(ostream&, ArvoreEnaria&);
}; 