#include "Daire.hpp"
#include "Pencere.hpp"

static const double PI = 3.14159265358979323846;

Daire::Daire(float yaricap, sf::Color renk, bool hareket, float aci)
{
	this->m_yaricap = yaricap;
	this->m_hareketEdiyorMu = hareket;
	this->m_aci = aci;
	m_sekil.setRadius(yaricap);
	m_sekil.setOrigin(sf::Vector2f(yaricap, yaricap));
	m_sekil.setFillColor(renk);
}

bool Daire::getirHareketEdiyorMu()
{
	return m_hareketEdiyorMu;
}

void Daire::hareketAyarla(bool hareket)
{
	m_hareketEdiyorMu = hareket;
}

sf::Color Daire::renkGetir()
{
	return m_sekil.getFillColor();
}

DairePtr Daire::daireUret(float boyut, sf::Color renk, bool hareket, float aci)
{
	return std::make_shared<Daire>(boyut, renk, hareket, aci);
}

void Daire::renkAyarla(sf::Color renk)
{
	m_sekil.setFillColor(renk);
}

void Daire::ciz(Pencere& pencere)
{
	m_sekil.setPosition(m_konum);
	pencere.ciz(m_sekil);
	hareketEttir();
}

void Daire::hareketEttir()
{
	if (m_hareketEdiyorMu)
	{
		float yonY = 15 * std::sin((360 - m_aci) * PI / 180);
		float yonX = m_bounceX * 15 * std::cos((360 - m_aci) * PI / 180);

		m_konum = sf::Vector2f(m_sekil.getPosition().x + yonX, m_sekil.getPosition().y - yonY);
	}
}

void Daire::bounceAyarla()
{
	if (m_bounceX == 1){ m_bounceX = -1; }
	else if (m_bounceX == -1) { m_bounceX = 1; }
}

std::vector<std::shared_ptr<Daire>> Daire::komsuGetir()
{
	return m_komsular;
}

void Daire::komsuEkle(DairePtr daire)
{
	
	if (std::find(m_komsular.begin(), m_komsular.end(), daire) != m_komsular.end()) {
		// zaten listede var
	}
	else if(daire != NULL)
	{
		m_komsular.push_back(daire);
	}
}
