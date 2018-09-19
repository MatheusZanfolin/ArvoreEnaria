#include "stdafx.h"

#include "Inteiro.h"

Inteiro::Inteiro(int valor)
{
	this->valor = valor;
}

int Inteiro::GetValor() const
{
	return this->valor;
}

int Inteiro::CompararCom(InformacaoDeArvoreEnaria* outro) const
{
	Inteiro* outroInteiro = (Inteiro*)outro;

	return this->valor - outroInteiro->valor;
}

ostream& Inteiro::ToString(ostream& os) const
{
	os << this->valor;

	return os;
}