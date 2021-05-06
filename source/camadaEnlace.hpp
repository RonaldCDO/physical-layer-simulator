// #pragma once
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <bitset>
#include <math.h>

#define FRAME_SIZE 5
const std::vector<int> flag{0,1,1,1,1,1,1,0};
const std::vector<int> escape{0,1,1,0,1,0,0,1};


void CamadaEnlaceDadosTransmissora (std::vector<int> quadro);

void CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro);

void CamadaEnlaceDadosTransmissoraControleDeErro (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (std::vector<int> quadro);

void CamadaEnlaceDadosReceptora (std::vector<int> quadro);

void CamadaEnlaceDadosReceptoraDesenquadramento (std::vector<int> quadro);

void CamadaEnlaceDadosRepectoraControleDeErro (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramentoContagemDeCaracteres (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramentoInsercaoDeBytes (std::vector<int> quadro);

std::vector<std::vector<int>> groupBytes(std::vector<int> quadro, int numberOfBytes);

std::vector<int> IntToBinary (int numberOfBytes);

