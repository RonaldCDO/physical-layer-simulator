#include "camadaFisica.hpp"
#include "camadaEnlace.hpp"

//Escolha da codificação a ser utilizada no algoritmo
const int COD_ESCOLHIDA = COD_BINARIA;

//Conversão de string para um vetor de bits utilizando a função std::bitset 
//para obter os bits da string
std::vector<int> BinaryConversor (std::string mensagem){

    std::vector<int> fluxoBrutoDeBits;
    for(std::bitset<8> i : mensagem) {
        for(int j = i.size() - 1; j >= 0; j--){
            fluxoBrutoDeBits.push_back(i[j]);
        }
    }
    return fluxoBrutoDeBits;
}


//Método responsável pela conversão de vetor de inteiros com os valores binários para retornar a mensagem decodificada
//Foi utilizado uma string temporária chamada temp que copiou os valores binários
//e no último while a string foi varrida de forma a transformar o bitset
// que a cada 8 bits foi transformado para a mensagem original
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
    

//Método responsável pela obtenção da mensagem a ser codificada por meio da digitação do usuário
void AplicacaoTransmissora (void){

std::string mensagem;
std::cout<< "Digite uma mensagem -> ";
std::getline(std::cin, mensagem);
std::cout<<"\n";

CamadaDeAplicacaoTransmissora(mensagem);

}

//Método responsável pela convesão da string mensagem utilizando o método
//BinaryConversor
void CamadaDeAplicacaoTransmissora (std::string mensagem){
    std::vector<int> quadro = BinaryConversor(mensagem);
    
    CamadaEnlaceDadosTransmissora(quadro);
}


//Método responsável pela seleção de qual a codificação a ser utilizada
//ao chamar o método que contém a codificação, esse retorna o quadro codificado
//e o fluxoBrutoDeBits recebe o quadro codificado
void CamadaFisicaTransmissora (std::vector<int> quadro){

    std::cout<<"O quadro em binario a  ser codificado -> ";
   
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


//Método responsável pela codificação binária do quadro, como já houve a codificação para binário
//esse método só retorna o quadro recebido
std::vector<int> CamadaFisicaTransmissoraCodificacaoBinaria (std::vector<int> quadro){

    std::cout << std::endl;
    std::cout << "Utilizando a codificacao binaria para o quadro -> ";
    for(int i : quadro){
        std::cout<< i;
    }
    std::cout << std::endl;

    return quadro;
}


//Método responsável pela codificação manchester do quadro, para essa conversão, há uma varredura no vetor
//que contém os bits do quadro, a cada bit do quadro faz-se uma comparação com um suposto clock que gera
//o sinal 01, a codificação manchester utiliza o conceito lógico de XOR, na implementação foi usada o
//o operador ^ que faz essa comparação lógica do quadro com o clock.
std::vector<int> CamadaFisicaTransmissoraCodificacaoManchester (std::vector<int> quadro){
    
    int n = quadro.size();
    std::cout << std::endl;

    std::cout << "Utilizando a codificacao manchester para o quadro -> ";
    for(int i : quadro){
        std::cout<< i;
    }
    std::cout << std::endl;

    std::vector<int> retorno;

    for(int i = 0; i < n; i++){
        retorno.push_back((quadro[i] ^ 1));
        retorno.push_back((quadro[i] ^ 0));
    }

    std::cout << "Codificacao manchester retornou o quadro -> ";
    for(int i : retorno){
        std::cout<< i;
    }
    std::cout << std::endl;


    return retorno;
}


//Método responsável pela codificação bipolar do quadro, para essa conversão, há uma varredura no vetor
//que contém os bits do quadro, a cada bit do quadro faz-se uma comparação com um suposto clock que gera
//o sinal 01, a codificação bipolar utiliza o conceito de a cada bit da mensagem é feita a comparação com
//o clock utilizando o operador AND no caso de o bit da mensagem ser 0 e os operadores AND e NAND para os
//casos de 1, fazendo a convenção de 01 para Amplitude positiva e 10 para negativa
std::vector<int> CamadaFisicaTransmissoraCodificacaoBipolar (std::vector<int> quadro){

    std::vector<int> transfer;

    std::cout << std::endl;
    std::cout<<"Utilizando codificacao bipolar para o quadro -> ";
   
    for(int i : quadro)
    std::cout<<i;
    std::cout<<"\n";

    int aux = 0;
    int n = quadro.size();

    for (int i = 0 ; i < n ;  i++){
        
        if(quadro[i] == 0){

            transfer.push_back((quadro[i] & 0));
            transfer.push_back((quadro[i] & 1));

        } else if(aux % 2 == 0){

                transfer.push_back((quadro[i] & 0));
                transfer.push_back((quadro[i] & 1));

                aux = 1;
            } else{

                transfer.push_back(!(quadro[i] & 0));
                transfer.push_back(!(quadro[i] & 1));

                aux = 0;
            }
    }

    std::cout<<"Codificacao bipolar retornou -> ";
    for(int i : transfer)
    std::cout<<i;
    std::cout<< std::endl;

    return transfer;
}


//Método responsável pelo transporte do fluxoBrutoDeBits de um ponto A para um ponto B
void MeioDeComunicacao (std::vector<int> fluxoBrutoDeBits){


    std::vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
    int n = fluxoBrutoDeBitsPontoA.size();
    
    srand(time (NULL));
    
    std::cout << "A porcentagem de erro escolhida foi -> " << PORCENTAGEM_DE_ERRO << std::endl;
    for(int j = 0 ; j < n; j++){
        int erro = (rand()%100);
        if(erro < PORCENTAGEM_DE_ERRO) {
                fluxoBrutoDeBitsPontoB.push_back(!fluxoBrutoDeBitsPontoA[j]);
            }
            else
                fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[j]);
    }

    CamadaFisicaReceptora (fluxoBrutoDeBitsPontoB);
}


//Método responsável por receber o fluxoBrutoDeBitsPontoB, transformar em quadro a ser decodificado
//e transformado em fluxoDeBits 
void CamadaFisicaReceptora (std::vector<int> fluxoBrutoDeBitsPontoB){


    int tipoDeCodificacao = COD_ESCOLHIDA;

    std::vector<int> fluxoDeBits, quadro;
    quadro = fluxoBrutoDeBitsPontoB;

    switch (tipoDeCodificacao){
        case 0:
            fluxoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
            break;
        case 2:
            fluxoDeBits = CamadaFisicaReceptoraDecodificacaoBipolar(quadro);
            break;
    }

    CamadaEnlaceDadosReceptora(fluxoDeBits);
}


//Método responsável pela decodificação binária do quadro, como o quadro já possui os bits
//originais da mensagem, o quadro só é repassado para o fluxoDeBits
std::vector<int> CamadaFisicaReceptoraDecodificacaoBinaria (std::vector<int> quadro){
    std::vector<int> fluxoDeBits = quadro;

    std::cout << "Utilizando a decodificacao binaria para o quadro -> ";
    for(int i : quadro){
        std::cout<< i;
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "A decodificacao binaria retornou -> ";
    for(int i : quadro){
        std::cout<< i;
    }
    std::cout << std::endl;

    return fluxoDeBits;
}


//Método responsável pela decodificação manchester do quadro, para essa decodificação, há uma varredura no vetor
//que contém os bits do quadro, a cada par de bits do quadro faz-se uma comparação com o clock, no caso 
//de o par de bits ser diferente dos bits do clock, retorna o valor 1, caso contrário, retorna 0 
std::vector<int> CamadaFisicaReceptoraDecodificacaoManchester (std::vector<int> quadro){

    std::vector<int> fluxoDeBits;

    std::cout << "Utilizando decodificacao manchester para o quadro -> ";
    for(int i : quadro){
        std::cout<< i;
    }
    std::cout << std::endl;

    int n = quadro.size();

    for(int i = 0; i < n; i+=2) {
        if( !(quadro[i]|0) && quadro[i+1]&1 ){
            fluxoDeBits.push_back(1);
        }else {
            fluxoDeBits.push_back(0);
        }
    }

    std::cout << std::endl;
    std::cout << "A decodificacao manchester retornou o quadro -> ";
    for(int i : fluxoDeBits){
        std::cout<< i;
    }
    std::cout << std::endl;

    return fluxoDeBits;
}


//Método responsável pela decodificação bipolar do quadro, para essa decodificação, há uma varredura no vetor
//que contém os bits do quadro, a cada par de bits do quadro codificado, faz-se uma comparação 1 pra 1, caso 
//os bits forem iguais, retorna 0, se forem diferentes, retorna 1
std::vector<int> CamadaFisicaReceptoraDecodificacaoBipolar (std::vector<int> quadro){
    
    std::vector<int> fluxoDeBits;
    int n = quadro.size();

    std::cout<<"Utilizando decodificacao bipolar para o quadro -> ";
   
    for(int i : quadro)
    std::cout<<i;
    std::cout<<"\n";
    
    for(int i = 0; i < n; i+=2){
        if(quadro[i] == quadro [i+1]){
        fluxoDeBits.push_back(0);
        } else{
            fluxoDeBits.push_back(1);
        }

    }
    std::cout<<"\n";
    std::cout<<"Decodificacao bipolar retornou -> ";
    for(int i : fluxoDeBits)
    std::cout<<i;
    std::cout<<"\n";


    return fluxoDeBits;
}


//Método responsável por receber o fluxoDeBits e converter para a mensagem original
void CamadaDeAplicacaoReceptora (std::vector<int> fluxoDeBits){
    
    std::string mensagem = StringConversor(fluxoDeBits);

    AplicacaoReceptora (mensagem);
}


//Método responsável por exibir a mensagel original na tela
void AplicacaoReceptora (std::string mensagem){

    std::cout << "\n";
    std::cout<< "A mensagem recebida foi -> " << mensagem << std::endl;
}

