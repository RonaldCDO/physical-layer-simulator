#include "camadaEnlace.hpp"
#include "camadaFisica.hpp"

void CamadaEnlaceDadosTransmissora (std::vector<int> quadro){

    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    // CamadaEnlaceDadosTransmissoraControleDeErro(quadro);

}

void CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro){
    int tipoDeEnquadramento = 1;
    std::vector<int> quadroEnquadrado;

    switch (tipoDeEnquadramento){
        case 0 : 
            quadroEnquadrado = 
                CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
                break;
        case 1 :
            quadroEnquadrado = 
                CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
                break;
    }

    CamadaFisicaTransmissora(quadroEnquadrado);

}


std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (std::vector<int> quadro){
    return quadro;
}


std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (std::vector<int> quadro){

    std::cout << "Utilizando insercao de bytes para o enquadramento de ->";

    for(int j : quadro) {
        std::cout << j;
    }
    std::cout << std::endl;

    int numberOfBytes = quadro.size()/8;
    std::vector<int> enquadrado;

    std::vector<std::vector<int>> bytes = groupBytes(quadro, numberOfBytes);

    int count = 0;
    for(size_t i = 0; i < bytes.size(); i++) {
        if(count == 0) {
            enquadrado.insert(enquadrado.end(), flag.begin(), flag.end());
        }
        
        if(bytes[i] == flag || bytes[i] == escape) {
            enquadrado.insert(enquadrado.end(), escape.begin(), escape.end());
        }
        enquadrado.insert(enquadrado.end(), bytes[i].begin(), bytes[i].end());

        if(count == FRAME_SIZE) {
            enquadrado.insert(enquadrado.end(), flag.begin(), flag.end());
            count = 0;
        } else if(i < bytes.size()) {
            count++;
        }        
    }
    if(count <= FRAME_SIZE) {
        enquadrado.insert(enquadrado.end(), flag.begin(), flag.end());
    }
    std::cout << "O quadro gerado: ";

    for(int i : enquadrado) {
        std::cout << i ;
    }
    std::cout << std::endl;

    return enquadrado;
}

std::vector<std::vector<int>> groupBytes(std::vector<int> quadro, int numberOfBytes) {
    std::vector<std::vector<int>> bytes(numberOfBytes);
    for(int i = 0; i < numberOfBytes; i++) {
        for(int j = 0; j < 8; j++) {
            bytes[i].push_back(quadro[i*8+j]);
        }
    }
    return bytes;
}

void CamadaEnlaceDadosReceptora (std::vector<int> quadro){
    
    CamadaEnlaceDadosReceptoraDesenquadramento (quadro);

    // CamadaEnlaceDadosRepectoraControleDeErro (quadro);

    // CamadaDeAplicacaoReceptora (quadro);
}


void CamadaEnlaceDadosReceptoraDesenquadramento (std::vector<int> quadro){
    int tipoDeDesenquadramento = 1;
    std::vector<int> quadroDesenquadrado;

    switch (tipoDeDesenquadramento){
        case 0 : 
            quadroDesenquadrado = 
                CamadaEnlaceDadosReceptoraDesenquadramentoContagemDeCaracteres(quadro);
        break;

        case 1 :
            quadroDesenquadrado =
                CamadaEnlaceDadosReceptoraDesenquadramentoInsercaoDeBytes (quadro);
        break;

    }

    CamadaDeAplicacaoReceptora (quadroDesenquadrado);
}

std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramentoContagemDeCaracteres (std::vector<int> quadro){
    return quadro;
}

std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramentoInsercaoDeBytes (std::vector<int> quadro) {
    
    std::cout << std::endl;
    std::cout << "Utilizando insercao de bytes para o desenquadramento para o quadro -> ";
    for(int j : quadro){
        std::cout << j;
    }
    std::cout << std::endl;

    int numberOfBytes = quadro.size()/8;
    std::vector<int> desenquadrado;

    std::vector<std::vector<int>> bytes = groupBytes(quadro, numberOfBytes);
    
    int escaped = 0;
    for(size_t i = 0; i < bytes.size() - 1; i++) {
        if((bytes[i] != flag && bytes[i] != escape) || (escaped == 1)){
            desenquadrado.insert(desenquadrado.end(), bytes[i].begin(), bytes[i].end());
            escaped = 0;            
        }
        else if(bytes[i] == escape) {     
            escaped = 1;
        }
    }
    std::cout << "O desenquadramento retornou: ";

    for(int i : desenquadrado) {
        std::cout << i ;
    }
    std::cout << std::endl;

    return desenquadrado;
}
    
