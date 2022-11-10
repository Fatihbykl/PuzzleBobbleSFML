#include "Cizgi.hpp"
#include "Pencere.hpp"

Cizgi::Cizgi(float boyut, sf::Color renk, int aci)
{
    this->m_boyut = boyut;
    this->m_aci = aci;
    m_sekil.setSize(sf::Vector2f(boyut, 2));
    m_sekil.setFillColor(renk);
    m_sekil.rotate(aci);
}
sf::RectangleShape Cizgi::sekilGetir()
{
    return m_sekil;
}
int Cizgi::aciGetir()
{
    return m_aci;
}
void Cizgi::aciAyarla(int aci)
{
    m_aci = aci;
    m_sekil.setRotation(m_aci);
}
CizgiPtr Cizgi::cizgiUret(float boyut, sf::Color renk, int aci)
{
    return std::make_shared<Cizgi>(boyut, renk, aci);
}

void Cizgi::ciz(Pencere& pencere)
{
    m_sekil.setPosition(m_konum);
    pencere.ciz(m_sekil);
}
