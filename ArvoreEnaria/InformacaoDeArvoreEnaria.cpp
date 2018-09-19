#include "stdafx.h"
#include "InformacaoDeArvoreEnaria.h"

InformacaoDeArvoreEnaria::InformacaoDeArvoreEnaria(void)
{
	// Essa classe é apenas um base. Ela é feita para ser herdada
}

ostream& operator<<(ostream& os, InformacaoDeArvoreEnaria& info)
{
	return info.ToString(os);
}