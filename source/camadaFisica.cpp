#include "camadaFisica.hpp"



std::vector<int> BinaryConversor (std::string mensagem){

    std::vector<int> fluxoBrutoDeBits;
    for(std::bitset<8> i : mensagem) {
        for(int j = i.size() - 1; j >= 0; j--){
            fluxoBrutoDeBits.push_back(i[j]);
        }
    }
    return fluxoBrutoDeBits;
}


std::string StringConversor (std::vector<int> fluxoBrutoDeBits){
    
    std::string temp;
    std::string mensagem;

    for (int i : fluxoBrutoDeBits){
    temp += std::to_string(i);
}
std::stringstream sstream(temp);

while(sstream.good()){
    std::bitset<8> bits;
    sstream >> bits;
    char c = char(bits.to_ulong());
    mensagem +=c;
}

return mensagem;
}
    

void AplicacaoTransmissora (void){

std::string mensagem;
std::cout<< "Digite uma mensagem: " <<std::endl;
std::getline(std::cin, mensagem);

CamadaDeAplicacaoTransmissora(mensagem);

}

void CamadaDeAplicacaoTransmissora (std::string mensagem){
    std::vector<int> quadro = BinaryConversor(mensagem);
    
    CamadaFisicaTransmissora(quadro);
}

void CamadaFisicaTransmissora (std::vector<int> quadro){

    std::vector<int> fluxoBrutoDeBits;
    int tipoDeCodificacao = 0;

    switch (tipoDeCodificacao){
        case 0:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2:
            CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
        default:
            break;
    }


    MeioDeComunicacao(fluxoBrutoDeBits);

}


std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (std::vector<int> quadro){
    return quadro;
}


std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester (std::vector<int> quadro){
    
    
    return quadro;
}


std::vector<int> CamadaFisicaTransmissoraCodificacaoBipolar (std::vector<int> quadro){
    
    
    return quadro;
}


void MeioDeComunicacao (std::vector<int> fluxoBrutoDeBits){

    std::vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;


    for(int j = 0; j < fluxoBrutoDeBitsPontoA.size(); j++){
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[j]);
    }


    CamadaFisicaReceptora (fluxoBrutoDeBitsPontoB);
}

void CamadaFisicaReceptora (std::vector<int> fluxoBrutoDeBitsPontoB){

    int tipoDeCodificacao = 0;
    std::vector<int> fluxoBrutoDeBits, quadro;

    quadro = fluxoBrutoDeBitsPontoB;

    switch (tipoDeCodificacao){
        case 0:
            fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
            break;
        case 2:
            CamadaFisicaReceptoraDecodificacaoBipolar(quadro);
            break;
    }

    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}


std::vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits = quadro;

    return fluxoBrutoDeBits;
}


std::vector<int> CamadaFisicaReceptoraDecodificacaoManchester (std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;

    return fluxoBrutoDeBits;
}


std::vector<int> CamadaFisicaReceptoraDecodificacaoBipolar (std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits;

    return fluxoBrutoDeBits;
}

void CamadaDeAplicacaoReceptora (std::vector<int> fluxoBrutoDeBits){
    
    std::string mensagem = StringConversor(fluxoBrutoDeBits);

    AplicacaoReceptora (mensagem);
}

void AplicacaoReceptora (std::string mensagem){

    std::cout<< "A mensagem recebida foi: " << mensagem << std::endl;
}

