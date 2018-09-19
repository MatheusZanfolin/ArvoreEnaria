#include "stdafx.h"
#include "NoDeArvoreEnaria.h"
#include <exception>

NoDeArvoreEnaria::NoDeArvoreEnaria(int qtosPtrs)
{
	if (qtosPtrs < 2)
		throw "NoDeArvoreEnaria: inicialização com menos de dois ponteiros.";

	this->vetPtr  = new NoDeArvoreEnaria*        [qtosPtrs];
	this->vetInfo = new InformacaoDeArvoreEnaria*[qtosPtrs - 1];

	for (int i = 0; i < qtosPtrs; i++)
		this->vetPtr[i] = NULL;

	for (int i = 0; i < qtosPtrs - 1; i++)
		this->vetInfo[i] = NULL;

	this->qtosPtrs = qtosPtrs;
	this->qtasInfo = 0;
}

void NoDeArvoreEnaria::GuardarInfo(InformacaoDeArvoreEnaria* info)
{
	bool cheio = true;
	int posicaoVaga = -1;

	for (int i = 0; i < this->qtosPtrs - 1; i++)
	{
		if (this->vetInfo[i] == NULL)
		{
			cheio = false;

			posicaoVaga = i;

			break;
		}
	}		

	if (!cheio)
	{
		this->vetInfo[posicaoVaga] = info;

		this->qtasInfo++;

		this->OrdenarInfo();

		return;
	}

	for (int i = 0; i < this->qtosPtrs - 1; i++)
	{
		if (info->CompararCom(this->vetInfo[i]) < 0)
		{
			if (this->vetPtr[i] == NULL)
				this->vetPtr[i] = new NoDeArvoreEnaria(this->qtosPtrs);

			this->vetPtr[i]->GuardarInfo(info);

			return;
		}			
	}

	if (this->vetPtr[this->qtosPtrs - 1] == NULL)
		this->vetPtr[this->qtosPtrs - 1] = new NoDeArvoreEnaria(this->qtosPtrs);

	this->vetPtr[this->qtosPtrs - 1]->GuardarInfo(info);
}

bool NoDeArvoreEnaria::RemoverInfo(InformacaoDeArvoreEnaria* info)
{
	int indiceInfo = -1;

	for (int i = 0; i < this->qtosPtrs - 1; i++)
	{
		if (this->vetInfo[i] == NULL)
			return false;
		
		if (info->CompararCom(this->vetInfo[i]) == 0)
		{
			indiceInfo = i;

			break;
		}			
		else if (info->CompararCom(this->vetInfo[i]) < 0)
		{
			if (this->vetPtr[i] == NULL)
				return false;

			bool removeu = this->vetPtr[i]->RemoverInfo(info);

			if (removeu && (!this->vetPtr[i]->TemInfo()))
				this->vetPtr[i] = NULL;

			return removeu;
		}
	}		

	if (indiceInfo == -1) // Ainda não achou. A info pode estar no maior dos filhos
	{
		if (this->vetPtr[qtosPtrs - 1] == NULL)
			return false;

		bool removeu = this->vetPtr[qtosPtrs - 1]->RemoverInfo(info);

		if (removeu && (!this->vetPtr[qtosPtrs - 1]->TemInfo()))
			this->vetPtr[qtosPtrs - 1] = NULL;

		return removeu;
	}
	else // A informação desejada está nesse ponteiro
	{
		bool temFilho   = false;
		bool filhoMaior = false;

		NoDeArvoreEnaria* filho = NULL;

		if (this->vetPtr[indiceInfo] != NULL)
		{
			filho = this->vetPtr[indiceInfo];

			temFilho   = true;
			filhoMaior = false;
		}
		else if (this->vetPtr[indiceInfo + 1] != NULL)
		{
			filho = this->vetPtr[indiceInfo + 1];

			temFilho   = true;
			filhoMaior = true;
		}

		if (temFilho)
		{
			InformacaoDeArvoreEnaria* infoFilha = NULL;

			if (filhoMaior)
				infoFilha = this->GetMenorDosMaioresFilhos(indiceInfo);
			else
				infoFilha = this->GetMaiorDosMenoresFilhos(indiceInfo);

			this->RemoverInfo(infoFilha); // Tira-se a informação filha de seu lugar atual... 			

			this->vetInfo[indiceInfo] = infoFilha; // ...e insere-se a mesma no lugar da info que queremos excluir

			this->RemoverVazios();

			return true;
		}

		// Essa info não tem filho, deve-se encontrar alguma info que tem

		if (!this->TemFilho()) // Esse nó não tem filho, basta que se faça a remoção do vetor
		{
			for (int i = indiceInfo; i < this->qtosPtrs - 2; i++)
				this->vetInfo[i] = this->vetInfo[i + 1];

			this->vetInfo[this->qtosPtrs - 2] = NULL;

			this->qtasInfo--;

			return true;
		}			

		int indiceInfoComFilho = -1;

		// Primeiro procura-se infos que tem filho à esquerda da info a ser deletada

		for (int i = indiceInfo - 1; i >= 0; i--)
			if (this->vetPtr[i] != NULL)
			{
				indiceInfoComFilho = i;

				break;
			}

		if (indiceInfoComFilho != -1) 
		{
			InformacaoDeArvoreEnaria* substituta = this->GetMaiorDosMenoresFilhos(indiceInfoComFilho);

			for (int i = indiceInfo; i > indiceInfoComFilho; i--)
				this->vetInfo[i] = this->vetInfo[i - 1];

			this->RemoverInfo(substituta); 

			this->RemoverVazios();

			this->vetInfo[indiceInfoComFilho] = substituta;

			return true;
		}

		// Como não foram encontrados, agora procura-se info com filho à direita da info a ser deletada

		for (int i = indiceInfo + 1; i < this->qtosPtrs ; i++)
			if (this->vetPtr[i] != NULL)
			{
				indiceInfoComFilho = i;

				break;
			}

		if (indiceInfoComFilho != -1)
		{
			InformacaoDeArvoreEnaria* substituta = this->GetMenorDosMaioresFilhos(indiceInfoComFilho);

			for (int i = indiceInfo; i < indiceInfoComFilho; i++)
				this->vetInfo[i] = this->vetInfo[i + 1];

			this->RemoverInfo(substituta); 

			this->RemoverVazios();

			this->vetInfo[indiceInfoComFilho] = substituta;

			return true;
		}

		throw "NoDeArvoreEnaria: Erro ao remover info. Informação com filho não encontrada";
	}	
}

InformacaoDeArvoreEnaria* NoDeArvoreEnaria::GetMaiorDosMenoresFilhos(int indiceInfo)
{
	NoDeArvoreEnaria* filho = this->vetPtr[indiceInfo]; // Primeiro adquire-se o filho menor que a info
	
	while (filho->TemFilho())
	{
		if (filho->vetPtr[filho->qtosPtrs - 1] != NULL)
			filho = filho->vetPtr[filho->qtosPtrs - 1];

		for (int i = filho->qtosPtrs - 2; i > 0; i--)
		{
			if (filho->vetInfo[i] != NULL)
			{
				return filho->vetInfo[i];
			}

			if (filho->vetPtr[i] != NULL)
			{
				filho = filho->vetPtr[i];

				break;
			}
		}
	}

	for (int i = this->qtosPtrs - 2; i >= 0; i--)
		if (filho->vetInfo[i] != NULL)
			return filho->vetInfo[i];

	throw "NoDeArvoreEnaria: erro ao tentar encontrar maior dos menores descendentes";
}

InformacaoDeArvoreEnaria* NoDeArvoreEnaria::GetMenorDosMaioresFilhos(int indiceInfo) // TODO Espelhar esse método no get maior
{
	NoDeArvoreEnaria* filho = this->vetPtr[indiceInfo + 1]; // Primeiro adquire-se o filho maior que a info

	while (filho->TemFilho())
	{
		for (int i = 0; i < filho->qtosPtrs - 1; i++)
		{
			if (filho->vetPtr[i] != NULL)
			{
				filho = filho->vetPtr[i];

				break;
			}

			if (filho->vetInfo[i] != NULL)
			{
				return filho->vetInfo[i];
			}
		}
	}

	for (int i = 0; i < filho->qtosPtrs - 1; i++)
		if (filho->vetInfo[i] != NULL)
			return filho->vetInfo[i];

	throw "NoDeArvoreEnaria: erro ao tentar encontrar menor dos maiores descendentes";
}

void NoDeArvoreEnaria::RemoverVazios()
{
	for (int i = 0; i < this->qtosPtrs; i++)
		if (this->vetPtr[i] == NULL)
			continue;
		else if (this->vetPtr[i]->qtasInfo <= 0)
			this->vetPtr[i] = NULL;
		else
			this->vetPtr[i]->RemoverVazios();
}

void NoDeArvoreEnaria::OrdenarInfo()
{
	int lento;
	int rapido;

	InformacaoDeArvoreEnaria* aux;

	for (lento = 0; lento <= this->qtasInfo - 2; lento++)
	{
		for (rapido = lento + 1; rapido <= this->qtasInfo - 1; rapido++)
		{
			if (this->vetInfo[lento]->CompararCom(this->vetInfo[rapido]) > 0) // O vetor deve estar em ordem crescente
			{
				aux = this->vetInfo[lento];

				this->vetInfo[lento] = this->vetInfo[rapido];

				this->vetInfo[rapido] = aux;
			}
		}
	}	
}

int NoDeArvoreEnaria::GetNumPonteiros() const
{
	return this->qtosPtrs;
}

NoDeArvoreEnaria* NoDeArvoreEnaria::GetFilho(int indice) const
{
	return this->vetPtr[indice];
}

InformacaoDeArvoreEnaria* NoDeArvoreEnaria::GetInfo(int indice) const
{
	return this->vetInfo[indice];
}

bool NoDeArvoreEnaria::TemInfo() const
{
	for (int i = 0; i < this->qtosPtrs - 1; i++)
		if (this->vetInfo[i] != NULL)
			return true;

	return false;
}

bool NoDeArvoreEnaria::TemFilho() const
{
	for (int i = 0; i < this->qtosPtrs; i++)
		if (this->vetPtr[i] != NULL)
			return true;

	return false;
}

ostream& NoDeArvoreEnaria::ToString(ostream& os) const
{
	os << "(";

	for (int i = 0; i < this->GetNumPonteiros() - 1; i++)
	{
		if (this->GetFilho(i) == NULL)
			os << "__";
		else
			os << *(this->GetFilho(i));

		if (this->GetInfo(i) == NULL)
			os << "||";
		else
			os << *(this->GetInfo(i));
	}
	
	if (this->GetFilho(this->GetNumPonteiros() - 1) == NULL)
		os << "__";
	else
		os << *(this->GetFilho(this->GetNumPonteiros() - 1));

	os << ")";

	return os;
}

ostream& operator<<(ostream& os, NoDeArvoreEnaria& no)
{
	return no.ToString(os);
}