#include "stdafx.h"
#include "InformacaoDeArvoreEnaria.h"

InformacaoDeArvoreEnaria::InformacaoDeArvoreEnaria(void)
{
	// Essa classe � apenas um base. Ela � feita para ser herdada
}

ostream& operator<<(ostream& os, InformacaoDeArvoreEnaria& info)
{
	return info.ToString(os);
}