#pragma once
#include <functional>
#include <SFML/Graphics.hpp>

typedef std::function<void(sf::Keyboard::Key)>	KlavyeFonksiyonu;

typedef std::vector<KlavyeFonksiyonu>			KlavyeFonksiyonListesi;
typedef std::vector<sf::Color>					RenkListesi;

enum class YON 
{
	YON_SOL,
	YON_SAG
};