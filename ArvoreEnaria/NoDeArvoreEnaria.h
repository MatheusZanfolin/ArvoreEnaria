#pragma once

#include <iostream>

#include "InformacaoDeArvoreEnaria.h"

using namespace std;

class NoDeArvoreEnaria
{
private:
	InformacaoDeArvoreEnaria** vetInfo;
	NoDeArvoreEnaria**         vetPtr;

	int qtosPtrs;
	int qtasInfo;

	void OrdenarInfo();

	InformacaoDeArvoreEnaria* GetMaiorDosMenoresFilhos(int);
	InformacaoDeArvoreEnaria* GetMenorDosMaioresFilhos(int);

	void RemoverVazios();
public:
	NoDeArvoreEnaria(int);

	void GuardarInfo(InformacaoDeArvoreEnaria*);
	bool RemoverInfo(InformacaoDeArvoreEnaria*);
	
	int GetNumPonteiros() const;

	NoDeArvoreEnaria* GetFilho(int) const;

	InformacaoDeArvoreEnaria* GetInfo (int) const;

	bool TemInfo() const;
	bool TemFilho() const;

	virtual ostream& ToString(ostream&) const;

	friend ostream& operator<<(ostream&, NoDeArvoreEnaria&);
};