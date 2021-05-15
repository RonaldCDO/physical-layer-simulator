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
    std::vector<std::vector<int>> bytes = GroupBytes(quadro, numberOfBytes);
       
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

    std::cout << "O quadro gerado -> ";

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

    std::vector<std::vector<int>> bytes = GroupBytes(quadro, numberOfBytes);

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
    std::cout << "O quadro gerado -> ";

    for(int i : enquadrado) {
        std::cout << i ;
    }
    std::cout << std::endl;

    return enquadrado;
}

std::vector<std::vector<int>> GroupBytes(std::vector<int> quadro, int numberOfBytes) {
    std::vector<std::vector<int>> bytes(numberOfBytes);
    for(int i = 0; i < numberOfBytes; i++) {
        for(int j = 0; j < 8; j++) {
            bytes[i].push_back(quadro[i*8+j]);
        }
    }
    return bytes;
}

std::vector<std::vector<int>> GroupTwelveBits(std::vector<int> quadro, int numberOfBytes) {
    std::vector<std::vector<int>> bytes(numberOfBytes);
    for(int i = 0; i < numberOfBytes; i++) {
        for(int j = 0; j < 12; j++) {
            bytes[i].push_back(quadro[i*12+j]);
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

std::vector<int> IntToBinary32 (int numberOfBytes){
    std::bitset<32> frameToBitsetConversor (numberOfBytes);
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

int tipoDeControleDeErro = 2;

switch (tipoDeControleDeErro){

    case 0 : quadro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (quadro);
    break;

    case 1 : quadro = CamadaEnlaceDadosTransmissoraControleDeErroCRC (quadro);
    break;

    case 2: quadro = CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
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

int ConvertBinary(std::vector<int> bytes){
    int decimal = 0;
    int i, bin;
    for(bin = 0, i = 7; i >= 0; i--, bin++){
        decimal = decimal + (pow(2, bin) * bytes[i]);
    }
    return decimal;
}

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC (std::vector<int> quadro){

    int numberOfBytes = quadro.size()/8;
    std::vector<std::vector<int>> bytes = GroupBytes(quadro, numberOfBytes);

    std::cout << "Enviando para conversor" << std::endl;

    uint32_t remainder = 0xffffffff;
    for(int i = 0; i < numberOfBytes; i++){
        int j;
        uint32_t aux;
        long transformed = ConvertBinary(bytes[i]);
        
        uint32_t partial = ((remainder >> 24) ^ transformed) & 255;
        for(aux = partial << 24 , j=8; j>0; --j){             
            if (aux & 0x80000000)
            {
                aux = (aux << 1) ^ 0x04c11db7;
            }
            else
            {
                aux = (aux << 1);
            }
        }
        remainder = (remainder << 8) ^ aux;
    }

    std::vector<int> crcBits = IntToBinary32(remainder);
    for(int w : crcBits) {
        quadro.push_back(w);
    }
    std::cout << std::endl;

    return quadro;
}

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(std::vector<int> quadro) {

    std::cout << std::endl;
    std::cout << "Inserindo bits de paridade por hamming no quadro -> ";
    for(int i : quadro) {
        std::cout << i ;
    }
    std::cout << std::endl;

    int numberOfBytes = quadro.size()/8;
    std::vector<std::vector<int>> bytes = GroupBytes(quadro, numberOfBytes);

    std::vector<int> quadroComParidade;

    int j;
    for(std::vector<int> byte : bytes){
        // contador dos bits de paridade
        int parity1 = 0;
        int parity2 = 0;
        int parity4 = 0;
        int parity8 = 0;
        for(j = 0; j < 8; j++){
            switch (j)
            {
            case 0:
                parity1 += byte[j];
                parity2 += byte[j];
                break;
            case 1:
                parity1 += byte[j];
                parity4 += byte[j];
                break;        
            case 2:
                parity2 += byte[j];
                parity4 += byte[j];
                break;
            case 3:
                parity1 += byte[j];
                parity2 += byte[j];
                parity4 += byte[j];
                break;
            case 4:
                parity1 += byte[j];
                parity8 += byte[j];
                break;
            case 5:
                parity2 += byte[j];
                parity8 += byte[j];
                break;
            case 6:
                parity1 += byte[j];
                parity2 += byte[j];
                parity8 += byte[j];
                break;
            case 7:
                parity4 += byte[j];
                parity8 += byte[j];
                break;
            default:
                break;
            }
        }
        byte.insert(byte.begin(), parity1%2);
        byte.insert(byte.begin() + 1, parity2%2);
        byte.insert(byte.begin() + 3, parity4%2);
        byte.insert(byte.begin() + 7, parity8%2);
        quadroComParidade.insert(quadroComParidade.end(), byte.begin(), byte.end());
    }


    std::cout << "Quadro gerado com bits de paridade -> ";
    for(int w : quadroComParidade) {
        std::cout << w;
    }
    std::cout << std::endl << std::endl;

    return quadroComParidade;
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
    std::vector<std::vector<int>> bytes = GroupBytes (quadro, numberOfBytes);

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

    std::vector<std::vector<int>> bytes = GroupBytes(quadro, numberOfBytes);
    
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
    std::cout << "O desenquadramento retornou -> ";

    for(int i : desenquadrado) {
        std::cout << i ;
    }
    std::cout << std::endl;

    return desenquadrado;
}


std::vector<int> CamadaEnlaceDadosReceptoraControleDeErro (std::vector<int> quadro){

int tipoDeControleDeErro = 2;

switch (tipoDeControleDeErro){

    case 0 : quadro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar (quadro);
    break;

    case 1 : quadro = CamadaEnlaceDadosReceptoraControleDeErroCRC (quadro);
    break;

    case 2: quadro = CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro);
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

    int numberOfBytes = quadro.size()/8;
    std::vector<std::vector<int>> bytes = GroupBytes(quadro, numberOfBytes);

    uint32_t remainder = 0xffffffff;
    for(int i = 0; i < numberOfBytes; i++){
        int j;
        uint32_t aux;
        long transformed = ConvertBinary(bytes[i]);
        
        uint32_t partial = ((remainder >> 24) ^ transformed) & 255;
        for(aux = partial << 24 , j=8; j>0; --j){             
            if (aux & 0x80000000)
            {
                aux = (aux << 1) ^ 0x04c11db7;
            }
            else
            {
                aux = (aux << 1);
            }
        }
        remainder = (remainder << 8) ^ aux;
    }
    int quadroSize = quadro.size();
    for(int j = 0; j < quadroSize; j++){
        if((quadroSize - j) <= 32){
            quadro.pop_back();
        }
    }    
    if (remainder != 0){
        std::cout << "Verificacao de crc encontrou erro!!" << std::endl;
    }
    return quadro;
}

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(std::vector<int> quadro){

    std::cout << std::endl;
    std::cout << "Checando bits de paridade por hamming no quadro -> ";
    for(int i : quadro) {
        std::cout << i ;
    }

    int numberOfBytes = quadro.size()/12;
    std::vector<std::vector<int>> bytes = GroupTwelveBits(quadro, numberOfBytes);

    std::vector<int> quadroCorrigido;



    
    for (std::vector<int> quadroDeHamming : bytes)
    {
    int errorCheck =0;
    int errorPos = 0;

    if (ParityCounter (quadroDeHamming, 1) != quadroDeHamming[0]%2)
    errorCheck += 0;
    if (ParityCounter (quadroDeHamming, 2) != quadroDeHamming[1]%2)
    errorCheck += 1;
    if (ParityCounter (quadroDeHamming, 4) != quadroDeHamming[3]%2)
    errorCheck += 3;
    if (ParityCounter (quadroDeHamming, 8) != quadroDeHamming[7]%2)
    errorCheck += 7;

    errorPos += errorCheck;

    if (errorCheck!= 0)
    quadroDeHamming.insert(quadroDeHamming.begin()+errorPos, !quadroDeHamming[errorPos]);

    quadroDeHamming.erase(quadroDeHamming.begin());

    quadroDeHamming.erase(quadroDeHamming.begin());

    quadroDeHamming.erase(quadroDeHamming.begin()+1);

    quadroDeHamming.erase(quadroDeHamming.begin()+4);

  

    quadroCorrigido.insert(quadroCorrigido.end(), quadroDeHamming.begin(), quadroDeHamming.end());

    std::cout<<"A correcao de erros retornou -> ";
    for (int f : quadroCorrigido)
    std::cout<<f;
    std::cout<<std::endl; 


    }

  
    return quadroCorrigido;
    }


    int ParityCounter (std::vector<int> quadroComParidade, int parityType){
        int count = 0;
        int paridade1 = 0, paridade2 = 1, paridade4 = 3, paridade8 = 7;
        int n = quadroComParidade.size();
        switch (parityType){
        case 1:
            for(int i=0; i<= n; i +=2){
                if (i == paridade1){
                } else if(quadroComParidade[i] == 1 ){
                count++;
                
                }
            }
        break;
        
        case 2:
            for(int i=1; i<= n; i+=4){
                if (i == paridade2){
                } else if(quadroComParidade[i] == 1)
                count++;
                if (quadroComParidade[i+1] == 1)
                count++;
            }
        break;

        case 4:
            for(int i = 3; i<= n; i+=8){
                if(paridade4 == i){
                }else if(quadroComParidade[i] == 1)
                count++;
                if(quadroComParidade[i+1] == 1)
                count++;
                if(quadroComParidade[i+2] == 1)
                count++;
                if(quadroComParidade[i+3] == 1)
                count++;
            }
        break;

        case 8:
            for(int i=7; i<= n; i+=16){
                if (i == paridade8){
                } else if(quadroComParidade[i] == 1)
                count++;
                if(quadroComParidade[i+1] == 1)
                count++;
                if(quadroComParidade[i+2] == 1)
                count++;
                if(quadroComParidade[i+3] == 1)
                count++;
                if(quadroComParidade[i+4] == 1)
                count++;
                if(quadroComParidade[i+5] == 1)
                count++;
                if(quadroComParidade[i+6] == 1)
                count++;
                if(quadroComParidade[i+7] == 1)
                count++;
            }
        break;

        default:
            std::cout <<"Tipo invalido!"<< std::endl; 
        break;
    }


        return (count%2);
    }

