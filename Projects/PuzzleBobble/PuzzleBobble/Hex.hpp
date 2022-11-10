#pragma once
#include "Cizilebilir.hpp"
#include "Daire.hpp"

class Hex : public Cizilebilir
{
private:
	sf::CircleShape m_sekil;
	float			m_boyut;
	int				m_aci;
	DairePtr		m_daire;
public:
	Hex(float yaricap, float aci);
	static std::shared_ptr<Hex> hexUret(float boyut, float aci);
	virtual void ciz(Pencere& pencere) override;
	bool icindeMi(DairePtr daire);
};
typedef std::shared_ptr<Hex>	HexPtr;