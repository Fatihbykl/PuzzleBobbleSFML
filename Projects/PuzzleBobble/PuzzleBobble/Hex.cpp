#include "Hex.hpp"
#include "Pencere.hpp"

Hex::Hex(float yaricap, float aci)
{
    this->m_boyut = yaricap;
    this->m_aci = aci;
    m_sekil.setRadius(yaricap);
    m_sekil.setOrigin(sf::Vector2f(yaricap, yaricap));
    m_sekil.setPointCount(6);
    m_sekil.setOutlineThickness(5);
    m_sekil.setFillColor(sf::Color::Transparent);
}

std::shared_ptr<Hex> Hex::hexUret(float boyut, float aci)
{
    return std::make_shared<Hex>(boyut, aci);
}

void Hex::ciz(Pencere& pencere)
{
    m_sekil.setPosition(m_konum);
    pencere.ciz(m_sekil);
}

bool Hex::icindeMi(DairePtr daire)
{
    auto dKonum = daire->m_konum;
    if (dKonum.x > (m_konum.x - 35) && dKonum.x < (m_konum.x + 35) &&
        dKonum.y > (m_konum.y - 35) && dKonum.y < (m_konum.y + 35))
    {
        return true;
    }
    else
    {
        return false;
    }
}

