#pragma once
#include "Fase.h"

namespace Fases {
	class Fase1 : public Fase {
	public:
		Fase1();
		~Fase1();
		void executar();
		void esvaziar();
		void criarPersonagens();
		void criarObstaculos();
	};
}
