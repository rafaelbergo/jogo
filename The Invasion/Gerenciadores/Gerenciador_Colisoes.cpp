﻿#include "Gerenciador_Colisoes.h"


Gerenciadores::Gerenciador_Colisoes* Gerenciadores::Gerenciador_Colisoes::pGerenciador_Colisoes = NULL;
Gerenciadores::Gerenciador_Colisoes::Gerenciador_Colisoes(){

}
Gerenciadores::Gerenciador_Colisoes::~Gerenciador_Colisoes() {
    cout << "destrutor do Gerenciador de colisoes" << endl;
    delete pGerenciador_Colisoes;
}
Gerenciadores::Gerenciador_Colisoes* Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes() {

    if (pGerenciador_Colisoes == NULL)
        pGerenciador_Colisoes = new Gerenciador_Colisoes();
    return pGerenciador_Colisoes;
}

void Gerenciadores::Gerenciador_Colisoes::incluiPersonagem(Personagem* pPerso){
    if (pPerso)
        vetor_personagens.push_back(pPerso);
    else
        cout << "erro: incluindo Personagem nulo no vetor_Personagens do Gerenciador de colisoes" << endl;
}

void Gerenciadores::Gerenciador_Colisoes::incluiInimigo(Personagens::Inimigo* pInimigo) {
    if (pInimigo){
        Personagem* pPerso = static_cast<Personagem*> (pInimigo);
        vetor_personagens.push_back(pPerso);
    }
    else
        cout << "erro: incluindo inimigo nulo no vetor_Personagens do Gerenciador de colisoes" << endl;
}
void Gerenciadores::Gerenciador_Colisoes::incluiObstaculo(Obstaculos::Obstaculo* pObs) {
    if (pObs)
        lista_obstaculos.push_back(pObs);
    else
        cout << "erro: incluindo ponteiro nulo no vetor_obstaculos do Gerenciador de colisoes" << endl;
}
void Gerenciadores::Gerenciador_Colisoes::testa_colisoes() {

    //colisão entre Personagens

    Entidade* pEnti_1 = NULL;
    Entidade* pEnti_2 = NULL;
    sf::Vector2f DistanciaExtremidades;
    bool Colidiu_em_x = false;
    int i = 0, j = 0;


    //testa colisões entre Personagens
    for (i = 0; i < (int)vetor_personagens.size(); i++){
        if(vetor_personagens[i]){
            pEnti_1 = static_cast<Entidade*> (vetor_personagens[i]);
            for(j = i + 1; j < (int)vetor_personagens.size(); j++){
                if(vetor_personagens[j]){
                    pEnti_2 = static_cast<Entidade*> (vetor_personagens[j]);
                    DistanciaExtremidades = Calcula_colisao(pEnti_1, pEnti_2);
                    if (DistanciaExtremidades.x < 0.0f && DistanciaExtremidades.y < 0.0f){
                        if(fabs(DistanciaExtremidades.x) > fabs(DistanciaExtremidades.y))
                            Colidiu_em_x = false;
                        else
                            Colidiu_em_x = true;
                        pEnti_1->colisao(pEnti_2, DistanciaExtremidades, Colidiu_em_x);
                        pEnti_2->colisao(pEnti_1, DistanciaExtremidades, Colidiu_em_x);
                    }
                }
                else
                    cout << "ponteiro nulo no vetor do gereniador de colisões" << endl;
            }
        }
        else
            cout << "ponteiro nulo no vetor do gereniador de colisões" << endl;
    }


   //Colisão entre Personagens e Obstaculos
    list<Obstaculos::Obstaculo*>::iterator it_obs = lista_obstaculos.begin();
    Obstaculos::Obstaculo* pObs;

    for (i = 0; i < (int)vetor_personagens.size(); i++){
        if(vetor_personagens[i]){
            pEnti_1 = static_cast<Entidade*> (vetor_personagens[i]);
            it_obs = lista_obstaculos.begin();
            while(it_obs != lista_obstaculos.end()){
                pObs = *it_obs;
                if(pObs){
                    pEnti_2 = static_cast<Entidade*> (pObs);
                    DistanciaExtremidades = Calcula_colisao(pEnti_1, pEnti_2);
                    if (DistanciaExtremidades.x < 0.0f && DistanciaExtremidades.y < 0.0f){
                        if(fabs(DistanciaExtremidades.x) > fabs(DistanciaExtremidades.y))
                            Colidiu_em_x = false;
                        else
                            Colidiu_em_x = true;
                        pEnti_1->colisao(pEnti_2, DistanciaExtremidades, Colidiu_em_x);
                        pEnti_2->colisao(pEnti_1, DistanciaExtremidades, Colidiu_em_x);
                    }
                }
                else
                    cout << "ponteiro nulo na Lista do gereniador de colisões" << endl;
                it_obs++;
            }
        }
        else
            cout << "ponteiro nulo no vetor do gereniador de colisões" << endl;
    }




    it_obs = lista_obstaculos.begin();
    list<Obstaculos::Obstaculo*>::iterator it_obs2 = lista_obstaculos.begin();
    Obstaculos::Obstaculo* pObs2;

    //testa colisoes entre obstaculos
    while(it_obs != lista_obstaculos.end()){
        pObs = *it_obs;
        if(pObs){
            it_obs2 = it_obs;
            it_obs2++;
            pEnti_1 = static_cast<Entidade*> (pObs);
            while(it_obs2 != lista_obstaculos.end()){
                pObs2 = *it_obs2;
                if(pObs2){
                    pEnti_2 = static_cast<Entidade*> (pObs2);
                    //Calcula_colisao retorna a distancia entre as duas extremidades mais proximas em cada eixp
                    DistanciaExtremidades = Calcula_colisao(pEnti_1, pEnti_2);
                    if (DistanciaExtremidades.x < 0.0f && DistanciaExtremidades.y < 0.0f){
                        if(fabs(DistanciaExtremidades.x) > fabs(DistanciaExtremidades.y))
                            Colidiu_em_x = false;
                        else
                            Colidiu_em_x = true;
                        pEnti_1->colisao(pEnti_2, DistanciaExtremidades, Colidiu_em_x);
                    }
                }
                else
                    cout << "ponteiro nulo na lista do Gerenciador de colisões" << endl;
                it_obs2++;
            }
        }
        else
            cout << "ponteiro nulo na lista do Gerenciador de colisões" << endl;
        it_obs++;
    }






}

sf::Vector2f Gerenciadores::Gerenciador_Colisoes::Calcula_colisao(Entidade* pEnti1, Entidade* pEnti2) {

    sf::Vector2f tamanho_1 = pEnti1->getSize(), tamanho_2 = pEnti2->getSize();
    sf::Vector2f pos_1 = pEnti1->getPosition(), pos_2 = pEnti2->getPosition();
    sf::Vector2f distanciaCentros(
        fabs((pos_1.x + (tamanho_1.x / 2.0f)) - (pos_2.x + (tamanho_2.x / 2.0f))),
        fabs((pos_1.y + (tamanho_1.y / 2.0f)) - (pos_2.y + (tamanho_2.y / 2.0f)))
    );
    //calcula Distancia das extremidades fazendo Distancia dos centros menos a metade dos tamanhos
    sf::Vector2f DistanciaExtremidades(
        distanciaCentros.x - (tamanho_1.x / 2.0f + tamanho_2.x / 2.0f),
        distanciaCentros.y - (tamanho_1.y / 2.0f + tamanho_2.y / 2.0f)
    );
    return DistanciaExtremidades;

}

void Gerenciadores::Gerenciador_Colisoes::setJogador(Personagens::Jogador* pJogaAux){
    if (pJogaAux){
        Personagem* pPerso = static_cast<Personagem*> (pJogaAux);
        vetor_personagens.push_back(pPerso);
    }
    else
        cout << "erro: incluindo jogador nulo no vetor_Personagens do Gerenciador de colisoes" << endl;
}

void Gerenciadores::Gerenciador_Colisoes::limpar(){
    vetor_personagens.clear();
    lista_obstaculos.clear();
    cout << "Gerenciador de colisoes limpo" << endl;
   
    cout << lista_obstaculos.size() << endl;
    cout << vetor_personagens.size() << endl;
}
