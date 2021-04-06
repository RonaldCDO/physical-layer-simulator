#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <sstream>

#define COD_BINARIA 0
#define COD_MANCHESTER 1
#define COD_BIPOLAR 2

/**
 * @brief Converte string para vetor binário
 *
 * @param mensagem Mensagem a ser transformada
 * @return vetor de inteiros que representa o quadro de bits
 */
std::vector<int> BinaryConversor (std::string mensagem);

/**
 * @brief Converte um vetor binário para string
 *
 * @param fluxoBrutoDeBits Vetor de inteiros que será interpretado para string
 * @return string com o valor obtido a partir do vetor de entrada
 */
std::string StringConversor (std::vector<int> fluxoBrutoDeBits);

/**
 * @brief Função que representa a primeira camada do fluxo da aplicação
 */
void AplicacaoTransmissora (void);

/**
 * @brief Camada de aplicação transmissora
 * Reponsável por executar a conversão da mensagem de entrada e enviá-la para a 
 * camada fisica transmissora
 *
 * @param mensagem Mensagem a ser convertida e encaminhada para camada inferior
 */
void CamadaDeAplicacaoTransmissora (std::string mensagem);

/**
 * @brief Camada física transmissora
 * Reponsável por reconhecer e executar a codificação escolhida para o quadro de bits
 * e encaminhá-lo para o meio de comunicação
 *
 * @param quadro Quadro de bits a ser codificado e encaminhado para o meio de comunicação
 */
void CamadaFisicaTransmissora (std::vector<int> quadro);

/**
 * @brief Implementa a codificação binária para o quadro
 *
 * @param quadro quadro de bits a ser codificado
 * @return quadro de bits codificado
 */
std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (std::vector<int> quadro);

/**
 * @brief Implementa a codificação manchester para o quadro
 *
 * @param quadro quadro de bits a ser codificado
 * @return quadro de bits codificado
 */
std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester (std::vector<int> quadro);

/**
 * @brief Implementa a codificação bipolar para o quadro
 *
 * @param quadro quadro de bits a ser codificado
 * @return quadro de bits codificado
 */
std::vector<int> CamadaFisicaTransmissoraCodificacaoBipolar (std::vector<int> quadro);

/**
 * @brief Simula a transmissão dos dados por um meio
 * encaminha o quadro de bits para a camada de recepção da mensagem
 * @param fluxoBrutoDeBits quadro de bits a ser transmitido
 */
void MeioDeComunicacao (std::vector<int> fluxoBrutoDeBits);

/**
 * @brief Camada física receptora
 * Reponsável por reconhecer e executar a decodificação escolhida para o quadro de bits
 * e encaminhá-lo para a camada fisica receptora
 *
 * @param fluxoBrutoDeBitsPontoB Quadro de bits a ser decodificado e encaminhado para a camada fisica receptora
  @return quadro de bits a ser decodificado
 */
void CamadaFisicaReceptora (std::vector<int> fluxoBrutoDeBitsPontoB);

/**
 * @brief Implementa a decodificação binaria para o quadro
 *
 * @param quadro quadro de bits a ser decodificado
 * @return quadro de bits decodificado
 */
std::vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (std::vector<int> quadro);

/**
 * @brief Implementa a decodificação manchester para o quadro
 *
 * @param quadro quadro de bits a ser decodificado
 * @return quadro de bits decodificado
 */
std::vector<int> CamadaFisicaReceptoraDecodificacaoManchester (std::vector<int> quadro);


/**
 * @brief Implementa a decodificação bipolar para o quadro
 *
 * @param quadro quadro de bits a ser decodificado
 * @return quadro de bits decodificado
 */
std::vector<int> CamadaFisicaReceptoraDecodificacaoBipolar (std::vector<int> quadro);

/**
 * @brief Camada de aplicação transmissora
 * Reponsável por executar a conversão do quadro recebido e enviá-lo para a 
 * aplicação transmissora
 *
 * @param quadro vetor de bits a ser convertido para string
 */
void CamadaDeAplicacaoReceptora (std::vector<int> fluxoBrutoDeBits);

/**
 * @brief Aplicação receptora
 * camada final da recepção, responsável por mostrar a mensagem recebida ao usuário
 *
 * @param mensagem Mensagem a ser exibida
 */
void AplicacaoReceptora (std::string mensagem);
