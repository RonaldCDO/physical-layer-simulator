// #pragma once
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <bitset>
#include <math.h>

#define FRAME_SIZE 2
const std::vector<int> flag{0,1,1,1,1,1,1,0};
const std::vector<int> escape{0,1,1,0,1,0,0,1};

/**
 * @brief Camada de enlace de dados transmissora
 * Reponsável por transmitir a mensagem para ser enquadrada
 * de acordo com o método escolhido
 *
 * @param mensagem Mensagem a ser enquadrada e transmitida
 */
void CamadaEnlaceDadosTransmissora (std::vector<int> quadro);

/**
 * @brief Camada enlace de dados transmissora enquadramento
 * Reponsável realizar o enquadramento da mensagem de acordo com o método escolhido
 * e encaminha-la para a Camada Fisica Transmissora
 *
 * @param quadro Conjunto de bits a ser enquadrado e encaminhado para o meio fisico
 */
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (std::vector<int> quadro);

/**
 * @brief Implementa o enquadramento por insercao de bytes
 *
 * @param quadro conjunto de bits a ser enquadrado
 * @return Conjunto composto pelos quadros
 */
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (std::vector<int> quadro);

/**
 * @brief Camada enlace de dados receptora
 * Responsável por encaminhar o quadro para ser desenquadrado
 *
 * @param quadro Quadro de bits a ser desenquadrado
 */
void CamadaEnlaceDadosReceptora (std::vector<int> quadro);

/**
 * @brief Camada enlace de dados receptora desenquadramento
 * Reponsável realizar o desnquadramento do quadro de acordo com o método escolhido
 * e encaminha-la para a Camada de Aplicacao Receptora
 *
 * @param quadro Conjunto de bits a ser desenquadrado e encaminhado para a aplicacao
 */

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErro (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC (std::vector<int> quadro);


std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramento (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosRepectoraControleDeErro (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramentoContagemDeCaracteres (std::vector<int> quadro);

/**
 * @brief Implementa o desenquadramento de insecao de bytes para o quadro
 *
 * @param quadro quadro de bits a ser desenquadrado
 * @return conjunto de bits desenquadrado
 */
std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramentoInsercaoDeBytes (std::vector<int> quadro);

/**
 * @brief Agrupa bytes
 * Funcao que separa o conjunto de bits em um vetor de vetores, cada um
 * representando um byte
 * 
 * @param quadro conjunto de bits a ser dividido
 * @param numberOfBytes numero de bytes contidos no quadro
 * 
 * @return vetor de bytes
 */

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErro (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar (std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC (std::vector<int> quadro);

std::vector<std::vector<int>> groupBytes(std::vector<int> quadro, int numberOfBytes);

std::vector<int> IntToBinary (int numberOfBytes);

int BinaryToInt (std::vector<int> binaryVector);

