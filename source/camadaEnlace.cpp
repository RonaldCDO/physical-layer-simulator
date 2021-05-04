#include "camadaEnlace.hpp"
#include "camadaFisica.hpp"

void CamadaEnlaceDadosTransmissora (std::vector<int> quadro){

    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    // CamadaEnlaceDadosTransmissoraControleDeErro(quadro);

    CamadaFisicaTransmissora(quadro);
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

}


std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (std::vector<int> quadro){
    return quadro;
}


std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (std::vector<int> quadro){

    std::cout << "Utilizando insercao de bytes para o enquadramento" << std::endl;

    int numberOfBytes = quadro.size()/8;
    std::vector<int> flag{5,5,5,5};
    std::vector<int> enquadrado;

    std::vector<std::vector<int>> bytes = groupBytes(quadro, numberOfBytes);

    int count = 0;
    for(std::vector<int> byte : bytes) {
        std::cout << "O byte apresentado: ";

        for(int i : byte) {
            std::cout << i ;
        }
        std::cout << std::endl;

        if(count == 0) {
            std::cout << "inicio" << std::endl;

            enquadrado.insert(enquadrado.end(), flag.begin(), flag.end());
        }
        
        if(byte == flag) {
            enquadrado.insert(enquadrado.end(), flag.begin(), flag.end());
        }
        enquadrado.insert(enquadrado.end(), byte.begin(), byte.end());

        if(count == 2) {
            enquadrado.insert(enquadrado.end(), flag.begin(), flag.end());
            count = 0;
        } else {
            count++;
        }
        std::cout << "Enquadramento: ";

        for(int i : enquadrado) {
            std::cout << i ;
        }
        std::cout << std::endl;
        std::cout << count << std::endl;
        
    }
    if(count < 2) {
        enquadrado.insert(enquadrado.end(), flag.begin(), flag.end());
    }

    std::cout << "Enquadramento final: ";

        for(int i : enquadrado) {
            std::cout << i ;
        }
        std::cout << std::endl;


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

    CamadaDeAplicacaoReceptora (quadro);
}


void CamadaEnlaceDadosReceptoraDesenquadramento (std::vector<int> quadro){
    int tipoDeDesenquadramento = 0;
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
    return quadro;
}
    
