#include "camadaEnlace.hpp"
#include "camadaFisica.hpp"

void CamadaEnlaceDadosTransmissora (std::vector<int> quadro){

    std::vector<int> quadro2, quadro3;
    quadro2 = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    quadro3 = CamadaEnlaceDadosTransmissoraControleDeErro(quadro2);

    CamadaFisicaTransmissora(quadro3);


}

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento (std::vector<int> quadro){
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
    return quadroEnquadrado;
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
    for(size_t i = 0; i < bytes.size(); ){

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
                if(i< bytes.size()){
                enquadrado.insert(enquadrado.end(), bytes[i].begin(), bytes[i].end());
                count++;
                temp++;
                i++;
                }
            }
        
            numberOfBytes = numberOfBytes - temp;
            count = 1;
        
        } else if (numberOfBytes < FRAME_SIZE){
            
            int temp = 0;
            
            while (count != (numberOfBytes + 1)){
               if(i< bytes.size()){
                enquadrado.insert(enquadrado.end(), bytes[i].begin(), bytes[i].end());
                count++;
                temp++;
                i++;
               }
                
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

int BinaryToInt (std::vector<int> binaryVector){
    int number = 0;
    int reverseIndex = 0;
    int final = -1;
        for (int i = binaryVector.size()- 1; i > final; i--){
        if(binaryVector[i]!= 0){
        number = number + pow(2, reverseIndex);
        }
        reverseIndex++;      
    }
    
    return number;
}


std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErro (std::vector<int> quadro){

int tipoDeControleDeErro = 0;

switch (tipoDeControleDeErro){

    case 0 : quadro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (quadro);
    break;

    case 1 : quadro = CamadaEnlaceDadosTransmissoraControleDeErroCRC (quadro);
    break;

    default:
    std::cout << "Verificação de erros invalida.";
    break;

    }

    return quadro;
}


std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (std::vector<int> quadro){
    
    std::vector<int> quadroChecado = quadro;

    int count = 0;
    int n = quadro.size();

    for(int i = 0; i < n; i++){
        if(quadro[i] == 1)
        count++;
    }
        if (count % 2 == 1){
        quadroChecado.push_back(1);
        } else quadroChecado.push_back(0);

    return quadroChecado;
}

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC (std::vector<int> quadro){
    return quadro;
}

void CamadaEnlaceDadosReceptora (std::vector<int> quadro){
    
    std::vector<int> quadro2, quadro3;
    quadro2 =CamadaEnlaceDadosReceptoraControleDeErro (quadro);

    quadro3 = CamadaEnlaceDadosReceptoraDesenquadramento (quadro2);

    CamadaDeAplicacaoReceptora (quadro3);
}


std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramento (std::vector<int> quadro){
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

    return quadroDesenquadrado;
}

std::vector<int> CamadaEnlaceDadosReceptoraDesenquadramentoContagemDeCaracteres (std::vector<int> quadro){

    std::cout << "Utilizando contagem de caracteres para o desenquadramento  do quadro -> ";
    for(int j : quadro){
        std::cout << j;
    }
    std::cout << std::endl;

    int numberOfBytes = quadro.size()/8;
    std::vector<std::vector<int>> bytes = groupBytes (quadro, numberOfBytes);

    int count = 1;
    int size = 0;
    std::vector<int> frameToRemove, desenquadrado;


    for(size_t i = 0; i <  bytes.size(); )
    {
        if (count == 1 && i == 0){
            frameToRemove.insert(frameToRemove.end(), bytes[i].begin(), bytes[i].end());
            size = BinaryToInt(frameToRemove);
            i++;
        } else if (count != size){
            desenquadrado.insert(desenquadrado.end(), bytes[i].begin(), bytes[i].end());
            i++;
            count++;
        } else if( count == size){
            count = 1;
        }

    }
    
    std::cout<<"O enquadramento retornou -> ";
    for(int j : desenquadrado) {
        std::cout << j ;
    }
    std::cout << std::endl;
       
    

    return desenquadrado;
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


std::vector<int> CamadaEnlaceDadosReceptoraControleDeErro (std::vector<int> quadro){

int tipoDeControleDeErro = 0;

switch (tipoDeControleDeErro){

    case 0 : quadro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar (quadro);
    break;

    case 1 : quadro = CamadaEnlaceDadosReceptoraControleDeErroCRC (quadro);
    break;

    default:
    std::cout << "Verificação de erros invalida.";
    break;

    }
    return quadro;
}


std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar (std::vector<int> quadro){
    
    std::vector<int> quadroVerificado = quadro;

    int bitParidade = quadroVerificado[quadro.size()-1];
    quadroVerificado.pop_back();
    for(int i : quadroVerificado)
    std::cout << i;
    std::cout <<std::endl;

    int count = 0, n = quadroVerificado.size();

    for (int i = 0; i< n; i++){
        if (quadroVerificado[i] == 1){
        count++;
        }
    }

    if (count % 2 != bitParidade)
        std::cout << "Erro detectado!" << std::endl;
    
    return quadroVerificado;
}

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC (std::vector<int> quadro){
    return quadro;
}
