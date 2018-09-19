#include "stdafx.h"
#include "ArvoreEnaria.h"

ArvoreEnaria::ArvoreEnaria(int qtosPtrs)
{
	if (qtosPtrs < 2)
		throw "ArvoreEnaria: inicialização com menos de dois ponteiros.";

	this->qtosPtrs = qtosPtrs;

	this->raiz = NULL;
}

void ArvoreEnaria::Guardar(InformacaoDeArvoreEnaria* info)
{
	if (this->raiz == NULL)
		this->raiz = new NoDeArvoreEnaria(this->qtosPtrs);

	this->raiz->GuardarInfo(info);
}

bool ArvoreEnaria::Remover(InformacaoDeArvoreEnaria* info)
{
	if (this->raiz == NULL)
		return false;

	bool removeu = this->raiz->RemoverInfo(info);

	if (removeu && (!this->raiz->TemInfo()))
		this->raiz = NULL;

	return removeu;
}

NoDeArvoreEnaria* ArvoreEnaria::GetRaiz() const
{
	return this->raiz;
}

ostream& ArvoreEnaria::ToString(ostream& os) const
{
	if (this->GetRaiz() != NULL)
		os << *(this->GetRaiz());
	else
		os << "()";

	return os;
}

ostream& operator<<(ostream& os, ArvoreEnaria& arvore)
{
	return arvore.ToString(os);
}