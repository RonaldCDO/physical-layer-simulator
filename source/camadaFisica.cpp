#include "camadaFisica.hpp"

int COD_ESCOLHIDA = COD_BIPOLAR;

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
std::cout<< "Digite uma mensagem: ";
std::getline(std::cin, mensagem);
std::cout<<"\n";

CamadaDeAplicacaoTransmissora(mensagem);

}

void CamadaDeAplicacaoTransmissora (std::string mensagem){
    std::vector<int> quadro = BinaryConversor(mensagem);
    
    CamadaFisicaTransmissora(quadro);
}

void CamadaFisicaTransmissora (std::vector<int> quadro){

    std::cout<<"O quadro em binario a  ser codificado --> ";
   
    for(int i : quadro)
    std::cout<<i;
    std::cout<<"\n";

    std::vector<int> fluxoBrutoDeBits;

    int tipoDeCodificacao = COD_ESCOLHIDA;


    switch (tipoDeCodificacao){
        case 0:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
        default:
            break;
    }


    MeioDeComunicacao(fluxoBrutoDeBits);

}



std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (std::vector<int> quadro){

    std::cout << std::endl;
    std::cout << "Utilizando a codificacao binaria para o quadro --> ";
    for(int i : quadro){
        std::cout<< i;
    }
    std::cout << std::endl;

    return quadro;
}


std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester (std::vector<int> quadro){
    
    int n = quadro.size();
    std::cout << std::endl;

    std::cout << "Utilizando a codificacao manchester para o quadro --> ";
    for(int i : quadro){
        std::cout<< i;
    }
    std::cout << std::endl;


    std::vector<int> retorno;


    for(int i = 0; i < n; i++){
        retorno.push_back((quadro[i] ^ 1));
        retorno.push_back((quadro[i] ^ 0));
    }

    std::cout << "Codificacao manchester retornou o quadro --> ";
    for(int i : retorno){
        std::cout<< i;
    }
    std::cout << std::endl;


    return retorno;
}


std::vector<int> CamadaFisicaTransmissoraCodificacaoBipolar (std::vector<int> quadro){

    std::vector<int> transfer;

    std::cout << std::endl;
    std::cout<<"Utilizando codificacao bipolar para o quadro --> ";
   
    for(int i : quadro)
    std::cout<<i;
    std::cout<<"\n";

    int aux = 0;
    int n = quadro.size();

    for (int i = 0 ; i < n ;  i++){
        
        if(quadro[i] == 0){

            transfer.push_back((quadro[i] & 1));
            transfer.push_back((quadro[i] & 0));


        }
        else if(aux % 2 == 0){

                transfer.push_back(!(quadro[i] & 1));
                transfer.push_back(!(quadro[i] & 0));

                aux = 1;
            }
            else{

                transfer.push_back(quadro[i] & 1);
                transfer.push_back(quadro[i] & 0);

                aux = 0;
            }
    }

    std::cout<<"Codificacao bipolar retornou --> ";
    for(int i : transfer)
    std::cout<<i;

    std::cout<< std::endl;

    return transfer;
}


void MeioDeComunicacao (std::vector<int> fluxoBrutoDeBits){


    std::vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
    int n = fluxoBrutoDeBitsPontoA.size();

    for(int j = 0; j < n; j++){
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[j]);
    }


    CamadaFisicaReceptora (fluxoBrutoDeBitsPontoB);
}

void CamadaFisicaReceptora (std::vector<int> fluxoBrutoDeBitsPontoB){


    int tipoDeCodificacao = COD_ESCOLHIDA;

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
            fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBipolar(quadro);
            break;
    }

    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}


std::vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (std::vector<int> quadro){
    std::vector<int> fluxoBrutoDeBits = quadro;

    std::cout << "Utilizando a decodificacao binaria para o quadro --> ";
    for(int i : quadro){
        std::cout<< i;
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "A decodificacao binaria retornou --> ";
    for(int i : quadro){
        std::cout<< i;
    }
    std::cout << std::endl;

    return fluxoBrutoDeBits;
}



std::vector<int> CamadaFisicaReceptoraDecodificacaoManchester (std::vector<int> quadro){


    std::vector<int> fluxoBrutoDeBits;


    std::cout << "Utilizando decodificacao manchester para o quadro --> ";
    for(int i : quadro){
        std::cout<< i;
    }
    std::cout << std::endl;

    std::vector<int> retorno;
    int n = quadro.size();

    for(int i = 0; i < n; i+=2) {
        if( !(quadro[i]|0) && quadro[i+1]&1 ){
            retorno.push_back(1);
        }else {
            retorno.push_back(0);
        }
    }

    std::cout << std::endl;
    std::cout << "A decodificacao manchester retornou o quadro --> ";
    for(int i : retorno){
        std::cout<< i;
    }
    std::cout << std::endl;


    return retorno;
}


std::vector<int> CamadaFisicaReceptoraDecodificacaoBipolar (std::vector<int> quadro){
    
    std::vector<int> fluxoBrutoDeBits;
    int n = quadro.size();

    std::cout<<"Utilizando decodificacao bipolar para o quadro --> ";
   
    for(int i : quadro)
    std::cout<<i;
    std::cout<<"\n";
    
    for(int i = 0; i < n; i+=2){
        if(quadro[i] == quadro [i+1]){
        fluxoBrutoDeBits.push_back(0);
        } else{
            fluxoBrutoDeBits.push_back(1);
        }

    }
    std::cout<<"\n";
    std::cout<<"Decodificacao bipolar retornou --> ";
    for(int i : fluxoBrutoDeBits)
    std::cout<<i;
    std::cout<<"\n";


    return fluxoBrutoDeBits;
}

void CamadaDeAplicacaoReceptora (std::vector<int> fluxoBrutoDeBits){
    
    std::string mensagem = StringConversor(fluxoBrutoDeBits);

    AplicacaoReceptora (mensagem);
}

void AplicacaoReceptora (std::string mensagem){

    std::cout << "\n";
    std::cout<< "A mensagem recebida foi: " << mensagem << std::endl;
}

