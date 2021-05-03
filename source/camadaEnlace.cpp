#include "camadaEnlace.hpp"
#include "camadaFisica.hpp"

void CamadaEnlaceDadosTransmissora (std::vector<int> quadro){

    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);

    CamadaFisicaTransmissora(quadro);
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

}


std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres (std::vector<int> quadro){

}


std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes (std::vector<int> quadro){

}

void CamadaEnlaceDadosReceptora (std::vector<int> quadro){
    
    CamadaEnlaceDadosReceptoraDesenquadramento (quadro);

    CamadaEnlaceDadosRepectoraControleDeErro (quadro);

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
    
