#include "camadaFisica.hpp"

void AplicacaoTransmissora (void){
    std::string mensagem;
    std::cout<< "Digite uma mensagem: " <<std::endl;
    std::cin>> mensagem;

    CamadaDeAplicacaoTransmissora(mensagem);

}

void CamadaDeAplicacaoTransmissora (std::string mensagem){
    //int quadro[];

    //CamadaFisicaTransmissora(quadro);
}

// void CamadaFisicaTransmissora(int quadro[]){
//     int tipoDeCodificacao = 0;
//     int fluxoBrutoDeBits [];

//     switch (tipoDeCodificacao){
//         case 0:
//             fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
//             break;
//         case 1:
//             fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
//             break;
//         case 2:
//             CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
//             break;
//     }

//     MeioDeComunicacao(fluxoBrutoDeBits);

// }

std::vector<int> strToBinary (std:: string input, std::vector<int> output){
    int n  = input.length();
    std::vector<int>::iterator it;

    for(int i = 0; i< n; i++){
        it = output.begin();
        output.insert = std::bitset<8>(input[i]);
    }
    
    return output;
}

std::vector<int> teste (std::vector<int> input){
    std::vector<int> output = {1,2,3};

    int n = output.size();
    
    for(int i =0; i< n; i++)
    std::cout<< output[i]<<std::endl;

    return output;
}


