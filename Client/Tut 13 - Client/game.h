#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Client.h"
#include <iostream>
#include <sstream>
#include "PacketStructs.h"
#include <iomanip>

class game
{
public:

	game();
	~game();

	void run();
	void returnPos();
	void returnPos2();
	void returnPos3();
	void returnY1();
	void returnY2();
	void returnY3();
	double decimalplace(double timed);
	std::vector<std::string> splitString(const std::string& s, char delimiter);
	
private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void setupShapes();
	bool gameOver = false;
	bool yc = false;
	bool bc = false;
	double timed;
	sf::Clock timer;
	sf::RenderWindow m_window;
	bool m_exitgame;
	std::vector<std::string> data;
	sf::CircleShape m_circle;
	sf::CircleShape m_circle2;
	sf::CircleShape m_circle3;
	std::string uqholder;
	Client myClient;
	int identity;
	sf::Text yellow;
	sf::Text blue;
	sf::Text red;
	sf::Font m_font;
};

#endif // !GAME

