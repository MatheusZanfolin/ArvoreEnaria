#pragma once

#include <iostream>

using namespace std;

class InformacaoDeArvoreEnaria
{
public:
	InformacaoDeArvoreEnaria(void);

	virtual int CompararCom(InformacaoDeArvoreEnaria*) const = 0;

	virtual ostream& ToString(ostream&) const = 0;

	friend ostream& operator<<(ostream&, InformacaoDeArvoreEnaria&);
};