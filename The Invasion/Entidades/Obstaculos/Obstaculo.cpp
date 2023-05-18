#include "../../stdafx.h"
#include "Obstaculo.h"


Entidades::Obstaculos::Obstaculo::Obstaculo(sf::Vector2f tam_corpo, float pos_x, float pos_y) :
    Entidade(tam_corpo, "Obstaculo")
{
    //corpo.setFillColor(sf::Color::Green);
    corpo.setPosition(pos_x, pos_y);
    textura = pGrafico->carregarTextura("The Invasion/assets/obstaculos/plataformas/plataforma1.png");
    corpo.setTexture(&textura);

}
Entidades::Obstaculos::Obstaculo::~Obstaculo() {

}
void Entidades::Obstaculos::Obstaculo::executar() {

}
void Entidades::Obstaculos::Obstaculo::colisao(Entidade* pOutra, sf::Vector2f DistanciaExtremidades, bool Colidiu_em_x) {


}
