#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <bitset>


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
