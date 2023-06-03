﻿#include "Gerenciador_Colisoes.h"


Gerenciadores::Gerenciador_Colisoes* Gerenciadores::Gerenciador_Colisoes::pGerenciador_Colisoes = NULL;
Gerenciadores::Gerenciador_Colisoes::Gerenciador_Colisoes(): pJogadores(NULL, NULL), vetor_Projeteis() {

}
Gerenciadores::Gerenciador_Colisoes::~Gerenciador_Colisoes(){
    cout << "destrutor do Gerenciador de colisoes" << endl;
    delete pGerenciador_Colisoes;
}
Gerenciadores::Gerenciador_Colisoes* Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes() {

    if (pGerenciador_Colisoes == NULL)
        pGerenciador_Colisoes = new Gerenciador_Colisoes();
    return pGerenciador_Colisoes;
}

void Gerenciadores::Gerenciador_Colisoes::incluiPersonagem(Personagem* pPerso){
    cout << "erro: incluindo Personagem Gerenciador de colisoes" << endl;
}

void Gerenciadores::Gerenciador_Colisoes::incluiInimigo(Personagens::Inimigo* pInimigo) {
    if (pInimigo){
        vetor_inimigos.push_back(pInimigo);
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
void Gerenciadores::Gerenciador_Colisoes::incluiProjetil(Projetil* pProj){
    if (pProj){
        vetor_Projeteis.push_back(pProj);
    }
    else
        cout << "erro: incluindo Projetil nulo no vetor_Personagens do Gerenciador de colisoes" << endl;

}

void Gerenciadores::Gerenciador_Colisoes::removerProjetil(Projetil* pProj){
    std::vector<Projetil*>::iterator it = std::find(vetor_Projeteis.begin(), vetor_Projeteis.end(), pProj);
    if (it != vetor_Projeteis.end())
        vetor_Projeteis.erase(it);

}
void Gerenciadores::Gerenciador_Colisoes::testa_colisoes() {
    ColisaoInimigoObstaculo();
    ColisaoJogadorObstaculo();
    ColisaoJogadorInimigo();
    ColisaoEntreObstaculos();
    ColisaoProjetilEntidade();

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
        if(pJogadores.first == NULL)
            pJogadores.first = pJogaAux;
        else{
            pJogadores.second = pJogaAux;
            cout << "teste" << endl;
        }
    }
    else
        cout << "erro: incluindo jogador nulo no vetor_Personagens do Gerenciador de colisoes" << endl;
}

void Gerenciadores::Gerenciador_Colisoes::limpar(){
    vetor_Projeteis.clear();
    vetor_inimigos.clear();
    lista_obstaculos.clear();
    pJogadores.first = NULL;
    pJogadores.second = NULL;

    cout << "Gerenciador de colisoes limpo" << endl;

    cout << lista_obstaculos.size() << endl;
    cout << vetor_inimigos.size() << endl;
}

void Gerenciadores::Gerenciador_Colisoes::ColisaoJogadorInimigo(){

    if(pJogadores.first){
        sf::Vector2f DistanciaExtremidades;
        for(int i = 0; i < (int) vetor_inimigos.size(); i++){
            if(vetor_inimigos[i]){
                DistanciaExtremidades = Calcula_colisao(pJogadores.first, vetor_inimigos[i]);
                if (DistanciaExtremidades.x < 0.0f && DistanciaExtremidades.y < 0.0f){
                    vetor_inimigos[i]->danar(pJogadores.first);
                    //pAux->Atacar(vetor_inimigos[i]);
                }
            }
        }
    }
    if(pJogadores.second){
        sf::Vector2f DistanciaExtremidades;
        for(int i = 0; i < (int) vetor_inimigos.size(); i++){
            if(vetor_inimigos[i]){
                DistanciaExtremidades = Calcula_colisao(pJogadores.second, vetor_inimigos[i]);
                if (DistanciaExtremidades.x < 0.0f && DistanciaExtremidades.y < 0.0f){
                    vetor_inimigos[i]->danar(pJogadores.second);
                    //pJogadores.second->Atacar(vetor_inimigos[i]);
                }
            }
        }
    }

}
void Gerenciadores::Gerenciador_Colisoes::ColisaoJogadorObstaculo(){

    sf::Vector2f DistanciaExtremidades;
    list<Obstaculos::Obstaculo*>::iterator it_obs = lista_obstaculos.begin();
    Obstaculos::Obstaculo* pObs;
    bool Colidiu_em_x;

    if(pJogadores.first){
        while(it_obs != lista_obstaculos.end()){
            pObs = *it_obs;
            if(pObs){
                DistanciaExtremidades = Calcula_colisao(static_cast<Entidade*>(pObs), static_cast<Entidade*>(pJogadores.first));
                if (DistanciaExtremidades.x <= 0.0f && DistanciaExtremidades.y <= 0.0f){
                        if(fabs(DistanciaExtremidades.x) > fabs(DistanciaExtremidades.y))
                            Colidiu_em_x = false;
                        else
                            Colidiu_em_x = true;
                        pObs->obstar(pJogadores.first, DistanciaExtremidades, Colidiu_em_x);
                        //pJogadores.first->colisao(pEnti_1, DistanciaExtremidades, Colidiu_em_x);

                }
            }
            else
                cout << "ponteiro nulo na Lista do gereniador de colisões" << endl;
            it_obs++;
        }
    }
    else
        cout << "Jogador 1 ponteiro nulo no gereniador de colisões" << endl;



    it_obs = lista_obstaculos.begin();
    if(pJogadores.second){
        while(it_obs != lista_obstaculos.end()){
            pObs = *it_obs;
            if(pObs){
                DistanciaExtremidades = Calcula_colisao(static_cast<Entidade*>(pObs), static_cast<Entidade*>(pJogadores.second));
                if (DistanciaExtremidades.x <= 0.0f && DistanciaExtremidades.y <= 0.0f){
                        if(fabs(DistanciaExtremidades.x) > fabs(DistanciaExtremidades.y))
                            Colidiu_em_x = false;
                        else
                            Colidiu_em_x = true;
                        pObs->obstar(pJogadores.second, DistanciaExtremidades, Colidiu_em_x);
                        //pJogadores.second->colisao(pEnti_1, DistanciaExtremidades, Colidiu_em_x);

                }
            }
            else
                cout << "ponteiro nulo na Lista do gereniador de colisões" << endl;
            it_obs++;
        }
    }


}



void Gerenciadores::Gerenciador_Colisoes::ColisaoInimigoObstaculo(){
    sf::Vector2f DistanciaExtremidades;
    list<Obstaculos::Obstaculo*>::iterator it_obs = lista_obstaculos.begin();
    Obstaculos::Obstaculo* pObs;
    bool Colidiu_em_x;

    for(int i = 0; i < (int) vetor_inimigos.size(); i++){
        if(vetor_inimigos[i]){
            it_obs = lista_obstaculos.begin();
            while(it_obs != lista_obstaculos.end()){
                pObs = *it_obs;
                if(pObs){
                    DistanciaExtremidades = Calcula_colisao(static_cast<Entidade*>(pObs), static_cast<Entidade*>(vetor_inimigos[i]));
                    if (DistanciaExtremidades.x < 0.0f && DistanciaExtremidades.y < 0.0f){
                            if(fabs(DistanciaExtremidades.x) > fabs(DistanciaExtremidades.y))
                                Colidiu_em_x = false;
                            else
                                Colidiu_em_x = true;
                            pObs->obstar(vetor_inimigos[i], DistanciaExtremidades, Colidiu_em_x);
                            //vetor_inimigos[i]->colisao(pEnti_1, DistanciaExtremidades, Colidiu_em_x);
                    }
                }
                else
                    cout << "ponteiro nulo na Lista do gereniador de colisões" << endl;
                it_obs++;
            }

        }
        else
            cout << "Ponteiro Inimigo  nulo no gereniador de colisões" << endl;
    }

}
void Gerenciadores::Gerenciador_Colisoes::ColisaoEntreObstaculos(){

    list<Obstaculos::Obstaculo*>::iterator it_obs = lista_obstaculos.begin();
    list<Obstaculos::Obstaculo*>::iterator it_obs2 = lista_obstaculos.begin();
    Obstaculos::Obstaculo* pObs1;
    Obstaculos::Obstaculo* pObs2;
    sf::Vector2f DistanciaExtremidades;
    bool Colidiu_em_x;

    //testa colisoes entre obstaculos
    while(it_obs != lista_obstaculos.end()){
        pObs1 = *it_obs;
        if(pObs1){
            it_obs2 = it_obs;
            //++ para não colidir com ele proprio
            it_obs2++;
            while(it_obs2 != lista_obstaculos.end()){
                pObs2 = *it_obs2;
                if(pObs2){
                    //Calcula_colisao retorna a distancia entre as duas extremidades mais proximas em cada eixp
                    DistanciaExtremidades = Calcula_colisao(static_cast<Entidade*>(pObs1), static_cast<Entidade*>(pObs2));
                    if (DistanciaExtremidades.x <= 0.0f && DistanciaExtremidades.y <= 0.0f){
                        if(fabs(DistanciaExtremidades.x) > fabs(DistanciaExtremidades.y))
                            Colidiu_em_x = false;
                        else
                            Colidiu_em_x = true;
                        pObs1->obstar(pObs2, DistanciaExtremidades, Colidiu_em_x);
                        pObs2->obstar(pObs1, DistanciaExtremidades, Colidiu_em_x);

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
void Gerenciadores::Gerenciador_Colisoes::ColisaoProjetilEntidade(){

    list<Obstaculos::Obstaculo*>::iterator it_obs = lista_obstaculos.begin();
    Obstaculos::Obstaculo* pObs;
    sf::Vector2f DistanciaExtremidades;

    /// testa colisão entre Projetil e Obstaculo/Jogadores (Projetil não atinge Inimigos)
    for(int i = 0; i < (int) vetor_Projeteis.size(); i++){
        it_obs = lista_obstaculos.begin();
        while(it_obs != lista_obstaculos.end()){
            pObs = *it_obs;
            if(pObs){
                DistanciaExtremidades = Calcula_colisao(static_cast<Entidade*>(pObs), static_cast<Entidade*>(vetor_Projeteis[i]));
                /// se Projetil colide com obstculo ele é destruido
                if (DistanciaExtremidades.x < 0.0f && DistanciaExtremidades.y < 0.0f)
                    vetor_Projeteis[i]->ApagarProjetil();
            }
            else
                cout << "ponteiro nulo na Lista do gereniador de colisões" << endl;
            it_obs++;
        }

        /// se Projetil colide com Jogador ele o da Dano
        if(pJogadores.first){
            DistanciaExtremidades = Calcula_colisao(static_cast<Entidade*>(pJogadores.first), static_cast<Entidade*>(vetor_Projeteis[i]));
            if (DistanciaExtremidades.x < 0.0f && DistanciaExtremidades.y < 0.0f)
                vetor_Projeteis[i]->AcertouJogador(pJogadores.first);
        }
        if(pJogadores.second){
        DistanciaExtremidades = Calcula_colisao(static_cast<Entidade*>(pJogadores.second), static_cast<Entidade*>(vetor_Projeteis[i]));
        if (DistanciaExtremidades.x < 0.0f && DistanciaExtremidades.y < 0.0f)
            vetor_Projeteis[i]->AcertouJogador(pJogadores.second);
        }
    }


}


