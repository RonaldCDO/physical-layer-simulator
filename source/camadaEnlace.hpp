#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <bitset>
#include <math.h>

#define FRAME_SIZE 2
#define BIT_PARIDADE 0
#define CRC 1
#define HAMMING_CODE 2

#define CONTAGEM_DE_CARACTERS 0
#define INSERCAO_DE_BYTES 1

const std::vector<int> flag{0,1,1,1,1,1,1,0};
const std::vector<int> escape{0,1,1,0,1,0,0,1};

/**
 * @brief Camada de enlace de dados transmissora
 * Reponsável por transmitir a mensagem de acordo com o método escolhido para a Camada Física 
 * Transmissora
 *
 * @param quadro que contém a mensagem a ser enquadrada, verificada ou corrigida e transmitida
 */
void CamadaEnlaceDadosTransmissora (std::vector<int> quadro);

/**
 * @brief Camada enlace de dados transmissora enquadramento
 * Reponsável por realizar o enquadramento do quadro de acordo com o método escolhido
 * e encaminhá-lo para a Camada Enlace Dados Transmissora e encaminhá-lo para a Camada Enlace Dados 
 * Transmissora
 *
 * @param quadro com o conjunto de bits a serem enquadrados
 * @return Conjunto composto pelos bits da mensagem
 */
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro);


/**
 * @brief Implementa o enquadramento por contagem de caracteres
 * Reponsável por realizar o enquadramento do conjunto de quadros utilizando a contagem de 
 * caracteres e inserindo a sua quantidade ao início de cada quadro e encaminhá-lo para a 
 * Camada Transmissora Enquadramento
 *
 * @param quadro com o conjunto de bits a serem enquadrados
 * @return Conjunto composto pelos quadros enquadrados
 */
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (std::vector<int> quadro);


/**
 * @brief Implementa o enquadramento por insercao de bytes
 * Responsável por realizar o enquadramento do conjunto de quadros utilizando a inserção de 
 * bytes do tipo flag ao início e final de cada quadro e encaminhá-lo para a Camada Transmissora 
 * Enquadramento
 * 
 * @param quadro com o conjunto de bits a serem enquadrados
 * @return Conjunto composto pelos quadros enquadrados em adição a seus respectivos tamanhos
 */
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (std::vector<int> quadro);


/**
 * @brief Camada enlace de dados transmissora controle de erro
 * Reponsável por realizar o controle de erro do conjunto de quadros de acordo com o método 
 * escolhido e encaminhá-lo para a Camada Enlace Dados Transmissora
 *
 * @param quadro com o conjunto de bits a serem verificados
 * @return Conjunto composto pelos quadros verificados
 */
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErro (std::vector<int> quadro);


/**
 * @brief Implementa o controle de erro por método bit paridade par
 * Responsável por adicionar ao conjunto de quadros um bit de paridade para cada um de seus 
 * quadros e encaminhá-lo para a Camada Transmissora Controle de Erro
 * 
 * @param quadro com o conjunto de bits a serem verificados
 * @return Conjunto composto pelos quadros e seu respectivo bit de paridade
 */
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (std::vector<int> quadro);

/**
 * @brief Implementa o controle de erro por método CRC
 * Responsável por adicionar ao conjunto de quadros um conjunto de bits de acordo com o polinômio
 * CRC32 e encaminhá-lo para a Camada Transmissora Controle de Erro
 *
 * @param quadro com o conjunto de bits a serem verificados
 * @return Conjunto composto pelos quadros e seu respectivo conjunto CRC de bits
 */
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC (std::vector<int> quadro);


/**
 * @brief Implementa o controle de erro por método de Hamming
 * Reponsável por adicionar ao conjunto de quadros 4 bits de paridade par em cada quadro
 * para corrigir posteriormente possíveis erros da transmissão e encaminhá-lo para a Camada 
 * Transmissora Controle de Erro
 *
 * @param quadro com o conjunto de bits a serem verificados
 * @return Conjunto composto pelos quadros e seus respectivos bits de paridade
 */
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(std::vector<int> quadro);


/**
 * @brief Camada enlace de dados receptora
 * Responsável por receber o conjunto de quadros para ser desenquadrado e encaminhá-lo para a Camada 
 * de Aplicação Receptora
 *
 * @param quadro com o conjunto de bits a serem desenquadrados e emcaminhados para a Camada 
 * de Aplicacao 
 */
void CamadaEnlaceDadosReceptora (std::vector<int> quadro);

/**
 * @brief Camada enlace de dados receptora desenquadramento
 * Reponsável por realizar o desenquadramento do conjunto de quadros de acordo com o método escolhido
 * e encaminhá-lo para a Camada Enlace Dados Receptora
 * 
 * @param quadro com o conjunto de bits a serem desenquadrados
 */
std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramento (std::vector<int> quadro);


/**
 * @brief Implementa o enquadramento por contagem de caracteres
 * Reponsável por realizar o denquadramento do conjunto de quadros utilizando a contagem de 
 * caracteres e removendo sua quantidade ao início de cada quadro e encaminhá-lo para a Camada Receptora
 * Desenquadramento
 *
 * @param quadro com o conjunto de bits a ser desenquadrado e encaminhá-lo para a Camada Receptora
 * Desenquadramento
 */
std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramentoContagemDeCaracteres (std::vector<int> quadro);

/**
 * @brief Implementa o enquadramento por insercao de bytes
 * Responsável por realizar o desenquadramento do conjunto de quadros utilizando a remoção de 
 * bytes do tipo flag ao início e final de cada quadro e encaminhá-lo para a Camada Receptora
 * Desenquadramento
 *
 * @param quadro quadro de bits a ser desenquadrado
 * @return conjunto de bits desenquadrado
 */
std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramentoInsercaoDeBytes (std::vector<int> quadro);


/**
 * @brief Camada enlace de dados receptora controle de erro
 * Reponsável por realizar o controle de erro do conjunto de quadros de acordo com o método 
 * escolhido e encaminhá-lo para a Camada Enlace Dados Receptora
 *
 * @param quadro com o conjunto de bits a serem verificados ou corrigidos
 * @return Conjunto composto pelos quadros verificados ou corrigidos
 */
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErro (std::vector<int> quadro);


/**
 * @brief Implementa o controle de erro por método bit paridade par
 * Responsável por adicionar ao conjunto de quadros um bit de paridade para cada um de seus 
 * quadros e encaminhá-lo para a Camada Receptora Controle de Erro
 *
 * @param quadro com o conjunto de bits a serem verificados
 * @return Conjunto composto pelos quadros com seus respectivos bits de paridade removidos
 */
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar (std::vector<int> quadro);


/**
 * @brief Implementa o controle de erro por método CRC
 * Responsável por verificar se o conjunto de bits com a sequência CRC de acordo com o polinômio
 * CRC32 possui erros, remover o conjunto de bits CRC e encaminhá-lo para a Camada Receptora 
 * Controle de Erro
 *
 * @param Conjunto composto pelos quadros e seu respectivo conjunto CRC de bits removido
 */
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC (std::vector<int> quadro);


/**
 * @brief Implementa o controle de erro por método de Hamming
 * Reponsável por remover do conjunto de quadros 4 bits de paridade par em cada quadro
 * corrigindo assim os erros da transmissão (se existentes) e encaminhá-lo para a Camada 
 * Receptora Controle de Erro
 *
 * @param quadro com o conjunto de bits a serem verificados
 * @return Conjunto composto pelos quadros e seus respectivos bits de paridade removidos
 */
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(std::vector<int> quadro);


/**
 * @brief Implementa a conversão de um número inteiro para um vetor de binários
 * Responsável por converter um número inteiro para um vetor de inteiros de 8 posições 
 * contendo os valores binários desse número inteiro respectivo
 *
 * @param Número inteiro
 * @return Conjunto de números inteiros
 */
std::vector<int> IntToBinary (int numberOfBytes);

/**
 * @brief Implementa a conversão de um número inteiro para um vetor de binários 
 * Responsável por converter um número inteiro para um vetor de inteiros de 32 posições 
 * contendo os valores binários desse número inteiro respectivo
 *
 @param Número inteiro
 @return Conjunto de números inteiros
 */
std::vector<int> IntToBinary32 (int numberOfBytes);

/**
 * @brief Implementa a conversão de um vetor de binários para um número inteiro
 * 
 * @param Vetor de inteiros
 * @return Número inteiro
 */
int BinaryToInt (std::vector<int> binaryVector);

/**
 * @brief Implementa o agrupamento de bytes
 * Responsável por separar o quadro em um conjunto de 8 bits contidos em um vetor 
 * de vetores, cada posição do vetor de vetores representa um byte
 * 
 * @param Quadro com o conjunto de bits a ser dividido
 * @param Numero de bytes contidos no quadro
 * 
 * @return Vetor de bytes
 */
std::vector<std::vector<int>> GroupBytes(std::vector<int> quadro, int numberOfBytes);


/**
 * @brief Implementa o agrupamento de um conjunto de bits
 * Responsável por separar o quadro em um conjunto de 12 bits contidos em um vetor 
 * de vetores, cada posição do vetor de vetores representa um conjunto de 12 bits
 *
 * @param Quadro com o conjunto de bits a ser dividido
 * @param Numero de bytes contidos no quadro
 * @return Vetor de bytes
 */
std::vector<std::vector<int>> Group12Bits(std::vector<int> quadro, int numberOfBytes);


/**
 * @brief Implementa a conversão de um vetor de binários para decimal 
 *
 * @param quadro Conjunto de bits a ser enquadrado e encaminhado para o meio fisico
 * @return Número inteiro
 */
int ConvertBinaryToDecimal(std::vector<int> bytes);


/**
 * @brief Implementa a contagem de paridade de Hamming
 * Responsável por contar a quantidade de bits 1 de um vetor de inteiros
 * de acordo com o tipo de paridade solicitada
 *
 * @param Vetor de inteiros
 * @param Número inteiro com o tipo de paridade
 */
int ParityCounter (std::vector<int> quadroComParidade, int parityType);

