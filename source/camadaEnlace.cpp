#include "camadaEnlace.hpp"
#include "camadaFisica.hpp"

void CamadaEnlaceDadosTransmissora (std::vector<int> quadro){

    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    // CamadaEnlaceDadosTransmissoraControleDeErro(quadro);

}

void CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro){
    int tipoDeEnquadramento = 0;
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

    std::cout << "Utilizando contagem de caracteres para o enquadramento de ->";

    for(int j : quadro) {
        std::cout << j;
    }
    std::cout << std::endl;

    int numberOfBytes = quadro.size()/8;
    
    std::vector<int> enquadrado;
    std::vector<std::vector<int>> bytes = groupBytes(quadro, numberOfBytes);
       
    int count = 1;
    for(size_t i = 0; i < bytes.size(); i++){

        if(FRAME_SIZE < 2){
            std::cout<<"Não foi possível enquadrar, devido ao tamanho de quadros ser invalido." <<std::endl;
            exit(1);
        }

        if(count == 1 && numberOfBytes == 0){
        break;
        }

        if(count == 1 && FRAME_SIZE <= numberOfBytes){
            
            std::vector<int> frameSizeBin = IntToBinary(FRAME_SIZE);
            enquadrado.insert(enquadrado.end(), frameSizeBin.begin(), frameSizeBin.end());
        
        } else if (FRAME_SIZE > numberOfBytes){
            std::vector<int> frameSizeBin = IntToBinary(numberOfBytes +1);
            enquadrado.insert(enquadrado.end(), frameSizeBin.begin(), frameSizeBin.end());
        } 
        
        if(FRAME_SIZE <= numberOfBytes){

            int temp = 0;

            while (count != FRAME_SIZE){
                enquadrado.insert(enquadrado.end(), bytes[i].begin(), bytes[i].end());
                count++;
                temp++;
            }
        
            numberOfBytes = numberOfBytes - temp;
            count = 1;
        
        } else if (numberOfBytes < FRAME_SIZE){
            
            int temp = 0;
            
            while (count != (numberOfBytes + 1)){
               
                enquadrado.insert(enquadrado.end(), bytes[i].begin(), bytes[i].end());
                count++;
                temp++;
            }
            
            numberOfBytes = numberOfBytes - temp;
            count = 1;

        }
    }

    std::cout << "O quadro gerado: ";

    for(int i : enquadrado) {
        std::cout << i ;
    }
    std::cout << std::endl;

    return enquadrado;
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

std::vector<int> IntToBinary (int numberOfBytes){
    std::bitset<8> frameToBitsetConversor (numberOfBytes);
    std::vector<int> numberOfBytesBin;

    for (int i = frameToBitsetConversor.size()-1 ; i >= 0; i--){
    numberOfBytesBin.push_back (frameToBitsetConversor[i]);
    }
    return numberOfBytesBin;
}

void CamadaEnlaceDadosReceptora (std::vector<int> quadro){
    
    CamadaEnlaceDadosReceptoraDesenquadramento (quadro);

    // CamadaEnlaceDadosRepectoraControleDeErro (quadro);

    // CamadaDeAplicacaoReceptora (quadro);
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
    
