#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <sstream>

#define COD_BINARIA 0
#define COD_MANCHESTER 1
#define COD_BIPOLAR 2

std::vector<int> BinaryConversor (std::string mensagem);

std::string StringConversor (std::vector<int>);

void AplicacaoTransmissora (void);

void CamadaDeAplicacaoTransmissora (std::string mensagem);

void CamadaFisicaTransmissora (std::vector<int> quadro);

std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (std::vector<int> quadro);

std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester (std::vector<int> quadro);

std::vector<int> CamadaFisicaTransmissoraCodificacaoBipolar (std::vector<int> quadro);

void MeioDeComunicacao (std::vector<int> fluxoBrutoDeBits);

void CamadaFisicaReceptora (std::vector<int> fluxoBrutoDeBitsPontoB);

std::vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (std::vector<int> quadro);

std::vector<int> CamadaFisicaReceptoraDecodificacaoManchester (std::vector<int> quadro);

std::vector<int> CamadaFisicaReceptoraDecodificacaoBipolar (std::vector<int> quadro);

void CamadaDeAplicacaoReceptora (std::vector<int> fluxoBrutoDeBits);

void AplicacaoReceptora (std::string mensagem);


