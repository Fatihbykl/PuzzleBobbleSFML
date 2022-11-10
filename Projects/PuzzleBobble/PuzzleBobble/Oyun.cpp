#include "Oyun.hpp"
#include <iostream>

int USTDUVAR = 0;

void Oyun::saatiYenidenBaslat()
{
	m_saat.restart();
}

Oyun::Oyun()
{
	m_fps = 60;
	m_cerceveSuresi = sf::seconds(1.0f / m_fps);
}

Oyun::~Oyun()
{
}

void Oyun::setFps(int fps)
{
	m_fps = fps;
}

void Oyun::oyunuBaslat(unsigned int genislik, unsigned int yukseklik)
{
	cizgiEkle(500, 0, 1, sf::Color::Red, 0);
	cizgiEkle(500, 0, 660, sf::Color::Cyan, 0);
	cizgiEkle(700, 1, 0, sf::Color::Red, 90);
	cizgiEkle(700, 450, 0, sf::Color::Red, 90);
	patlayanDaireEkle(30, 30, 35, sf::Color::Red, false);
	patlayanDaireEkle(30, 90, 35, sf::Color::Red, false);
	patlayanDaireEkle(30, 150, 35, sf::Color::Red, false);
	patlayanDaireEkle(30, 210, 35, sf::Color::Red, false);
	patlayanDaireEkle(30, 330, 35, sf::Color::Yellow, false);
	patlayanDaireEkle(30, 390, 35, sf::Color::Yellow, false);

	m_pencere.olustur(genislik, yukseklik, "PuzzleBobble");

	oyunuAyarla();

	saatiYenidenBaslat();
	while (m_pencere.acikmi())
	{
		m_pencere.olayKontrol();
		if (m_saat.getElapsedTime() >= m_cerceveSuresi)
		{
			m_secilenToplar.clear();

			oyunKontrol();
			cizimFonksiyonu();
			carpismaKontrol();
			toplariPatlat();
			baglantisizlariSil();

			saatiYenidenBaslat();
		}
		else
		{
			sf::sleep(m_cerceveSuresi - m_saat.getElapsedTime());
		}
	}
}

void Oyun::patlayanDaireEkle(float boyut, float konumX, float konumY, sf::Color renk, bool hareket)
{
	auto yeniDaire = Daire::daireUret(boyut, renk, hareket, 0);

	yeniDaire->m_konum = sf::Vector2f(konumX, konumY);
	m_daireler.push_back(yeniDaire);
}

void Oyun::cizgiEkle(float boyut, float konumX, float konumY, sf::Color renk, int aci)
{
	auto yeniCizgi = Cizgi::cizgiUret(boyut, renk, aci);

	yeniCizgi->m_konum = sf::Vector2f(konumX, konumY);
	m_cizgiler.push_back(yeniCizgi);
}

void Oyun::klavyeBasildi(sf::Keyboard::Key tus)
{
	if (tus == sf::Keyboard::Left)
	{
		m_oyuncu.oyuncuyuDondur(YON::YON_SOL);
	}
	if (tus == sf::Keyboard::Right)
	{
		m_oyuncu.oyuncuyuDondur(YON::YON_SAG);
	}
	if (tus == sf::Keyboard::Space)
	{
		firlayanTopListeyeEkle();
	}
}

void Oyun::firlayanTopListeyeEkle()
{
	auto top = m_oyuncu.firlayanTopOlustur();
	if (top)
	{
		m_daireler.push_back(top);
		m_atilanTopSayisi++;
	}
}

void Oyun::olaylariBagla()
{
	m_pencere.tusBasmaFonkEkle(std::bind(&Oyun::klavyeBasildi, this, std::placeholders::_1));
}

void Oyun::oyunuAyarla()
{
	olaylariBagla();
}

void Oyun::cizimFonksiyonu()
{
	m_pencere.cizimeBasla();

	//m_grid.ciz(m_pencere); // hex grid

	for (auto cizgi : m_cizgiler)
	{
		cizgi->ciz(m_pencere);
	}

	for (auto daire : m_daireler)
	{
		if (daire != NULL && daire->m_aktifMi)
		{
			daire->ciz(m_pencere);
		}
	}
	m_oyuncu.oyuncuGetir()->ciz(m_pencere);
	m_oyuncu.oyuncuCizgisiGetir()->ciz(m_pencere);
	m_pencere.cizimiBitir();
}

void Oyun::carpismaKontrol()
{
	for (auto daire : m_daireler)
	{
		if (!daire->m_aktifMi) { continue; }
		if (daire->m_konum.x - 30 <= 1 || daire->m_konum.x + 30 >= 450) // sag veya sol duvara çarptý
		{
			daire->bounceAyarla();
		}
		if (daire->m_konum.y - 35 <= USTDUVAR) // üst duvara çarptý
		{
			daireYerlestir();
			daire->hareketAyarla(false);
			m_oyuncu.topYoldaMiAyarla(false);
		}
		for (auto daire2 : m_daireler)
		{
			if (daire == daire2 || !daire2->m_aktifMi) { continue; }

			float dx = daire->m_konum.x - daire2->m_konum.x;
			float dy = daire->m_konum.y - daire2->m_konum.y;
			float distance = std::sqrt((dx * dx) + (dy * dy));
			if (distance <= 60)
			{
				daire->hareketAyarla(false);
				daireYerlestir();
				m_oyuncu.topYoldaMiAyarla(false);
				
				daire->komsuEkle(daire2);
				daire2->komsuEkle(daire);
				
				if (daire == m_daireler.back())
				{
					renkKontrolu(daire, daire2->m_sekil.getFillColor());
				}
				
			}
		}
	}
}

void Oyun::daireYerlestir()
{
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			auto daire = m_daireler.back();
			auto hex = m_grid.m_hexGrid[y][x];
			bool icinde = hex->icindeMi(daire);
			if (icinde && !daire->getirHareketEdiyorMu())
			{
				daire->m_konum = hex->m_konum;
			}
		}
	}
}

void Oyun::renkKontrolu(DairePtr daire, sf::Color renk)
{
	if (daire != NULL)
	{
		if (daire->m_sekil.getFillColor() == renk)
		{
			if (std::find(m_secilenToplar.begin(), m_secilenToplar.end(), daire) != m_secilenToplar.end())
			{
				return;
			}
			m_secilenToplar.push_back(daire);
			for (auto d : daire->komsuGetir())
			{
				renkKontrolu(d, renk);
			}
		}
		else
		{
			return;
		}
	}
}

void Oyun::stateSifirla()
{
	for (auto d : m_daireler)
	{
		d->m_ziyaretEdildiMi = false;
	}
}

bool Oyun::baglantisiVarMi(DairePtr daire)
{
	if (daire != NULL && !daire->m_ziyaretEdildiMi && daire->m_aktifMi)
	{
		daire->m_ziyaretEdildiMi = true;
		if (daire->m_konum.y - 35 <= USTDUVAR)
		{
			return true;
		}
		else
		{
			for (auto d : daire->komsuGetir())
			{
				if (baglantisiVarMi(d))
				{
					return true;
				}
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

void Oyun::baglantisizlariSil()
{
	for (auto d : m_daireler)
	{
		stateSifirla();
		if (!baglantisiVarMi(d) && !d->getirHareketEdiyorMu() && d->m_aktifMi)
		{
			d->m_aktifMi = false;
		}
	}
}

void Oyun::toplariPatlat()
{
	if (m_secilenToplar.size() >= 3)
	{
		for (auto s : m_secilenToplar)
		{
			s->m_aktifMi = false;
		}
	}
}

int Oyun::aktifTopSayisi()
{
	int aktifTop = 0;
	for (auto d : m_daireler)
	{
		if (d->m_aktifMi)
			aktifTop++;
	}
	return aktifTop;
}

void Oyun::oyunKontrol()
{
	if (m_atilanTopSayisi > 7) // üst duvarý aþaðýya çek
	{
		USTDUVAR += 100;
		m_cizgiler[0]->m_konum.y = USTDUVAR;
		for (auto d : m_daireler)
		{
			if (d->m_aktifMi)
			{
				d->m_konum.y += 100;
			}
		}
		m_atilanTopSayisi = 0;
	}
	if (!m_daireler.back()->getirHareketEdiyorMu() && m_daireler.back()->m_konum.y > 585)
	{
		std::cout << "*------------------* Kaybettiniz! * ------------------ *" << std::endl;
		m_pencere.pencereKapat();
	}
	if (aktifTopSayisi() <= 0)
	{
		std::cout << "*------------------* Kazandiniz! * ------------------ *" << std::endl;
		m_pencere.pencereKapat();
	}
}




