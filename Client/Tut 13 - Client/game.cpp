#include "game.h"

game::game() :
	m_window{ sf::VideoMode{ 1800u, 1200u, 32u }, "Tag" },
	m_exitgame{ false },myClient("127.0.0.1", 1111)
{
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		throw std::exception("sorry");
	}
	timer.restart();
	setupShapes();
	
}

game::~game()
{

}

void game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // Run as many times as possible
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // Run at a minimum of 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // Run as many times as possible
	}
}

void game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type) // check if the close window button is clicked on.
		{
			m_window.close();
		}

		if (sf::Event::KeyPressed == nextEvent.type)
		{
			if (!gameOver)
			{
				if (nextEvent.key.code == sf::Keyboard::Left)
				{
					if (myClient.Identify == "0")
					{
						m_circle.setPosition(m_circle.getPosition().x - 10, m_circle.getPosition().y);
					}
					if (myClient.Identify == "1")
					{
						m_circle2.setPosition(m_circle2.getPosition().x - 10, m_circle2.getPosition().y);
					}
					if (myClient.Identify == "2" && bc == false)
					{
						m_circle3.setPosition(m_circle3.getPosition().x - 10, m_circle3.getPosition().y);
					}
				}
				if (nextEvent.key.code == sf::Keyboard::Right)
				{
					if (myClient.Identify == "0")
					{
						m_circle.setPosition(m_circle.getPosition().x + 10, m_circle.getPosition().y);
					}
					if (myClient.Identify == "1")
					{
						m_circle2.setPosition(m_circle2.getPosition().x + 10, m_circle2.getPosition().y);
					}
					if (myClient.Identify == "2" && bc == false)
					{
						m_circle3.setPosition(m_circle3.getPosition().x + 10, m_circle3.getPosition().y);
					}
				}
				if (nextEvent.key.code == sf::Keyboard::Down)
				{
					if (myClient.Identify == "0")
					{
						m_circle.setPosition(m_circle.getPosition().x, m_circle.getPosition().y + 10);
					}
					if (myClient.Identify == "1")
					{
						m_circle2.setPosition(m_circle2.getPosition().x, m_circle2.getPosition().y + 10);
					}
					if (myClient.Identify == "2" && bc == false)
					{
						m_circle3.setPosition(m_circle3.getPosition().x, m_circle3.getPosition().y+10);
					}
				}
				if (nextEvent.key.code == sf::Keyboard::Up)
				{
					if (myClient.Identify == "0")
					{
						m_circle.setPosition(m_circle.getPosition().x, m_circle.getPosition().y - 10);
					}
					if (myClient.Identify == "1")
					{
						m_circle2.setPosition(m_circle2.getPosition().x, m_circle2.getPosition().y - 10);
					}
					if (myClient.Identify == "2" && bc==false)
					{
						m_circle3.setPosition(m_circle3.getPosition().x, m_circle3.getPosition().y - 10);
					}
				}
			}
		}
	}
}

void game::update(sf::Time t_deltaTime)
{
	if (m_exitgame)
	{
		m_window.close();
	}
	if (myClient.Identify == "0")
	{
		returnPos();
	}
	if(myClient.Identify == "1")
	{
		returnPos2();
	}
	if (myClient.Identify == "2")
	{
		returnPos3();
	}
    uqholder = myClient.holder;
	data = splitString(uqholder,',');
	
	for (std::string a : data)
	{
		std::cout << a << std::endl ;
	}
	if (myClient.Identify == "1")
	{
		m_circle.setPosition(std::stof(data.at(0)), std::stof(data.at(1)));
	}
	if (myClient.Identify == "3")
	{
		m_circle2.setPosition(std::stof(data.at(0)), std::stof(data.at(1)));
	}
	if (myClient.Identify == "0")
	{
		m_circle3.setPosition(std::stof(data.at(0)), std::stof(data.at(1)));
	}

	if (!gameOver && m_circle.getGlobalBounds().intersects(m_circle2.getGlobalBounds()))
	{
		yc = true;
		yellow.setString("Yellow is out\nLasted for  " + std::to_string(timer.getElapsedTime().asSeconds()) + " seconds!");
		yellow.setPosition(700, 600);
	}
	if (!gameOver && m_circle2.getGlobalBounds().intersects(m_circle3.getGlobalBounds()))
	{
		bc = false;
		std::string("UNFORZEN")
		blue.setString("Blue is out\nLasted for " + std::to_string(timed) + " seconds!");
	
	}
	if (!gameOver && m_circle.getGlobalBounds().intersects(m_circle3.getGlobalBounds()))
	{
		bc = true;
		timed = timer.getElapsedTime().asSeconds();
		decimalplace(timed);
		blue.setString("Blue is out\nLasted for " + std::to_string(timed) + " seconds!");
		

	}
	if (bc && yc)
	{
		gameOver = true;
		red.setString("RED WON");
	}
	if (gameOver)
	{
		yellow.setPosition(700, 600);
		blue.setPosition(700, 800);
		red.setPosition(700, 400);
	}
}

void game::render()
{
	m_window.clear();

	m_window.draw(m_circle);
	m_window.draw(m_circle2);
	m_window.draw(m_circle3);
	if (gameOver)
	{
		m_window.draw(yellow);
		m_window.draw(blue);
		m_window.draw(red);
	}
	m_window.display();
}

void game::setupShapes()
{
	/// <summary>
	/// player  1
	/// </summary>
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setRadius(30.0f);
	m_circle.setPosition(400.0f, 300.0f);

	m_circle2.setFillColor(sf::Color::Yellow);
	m_circle2.setRadius(30.0f);
	m_circle2.setPosition(200.0f, 150.0f);

	m_circle3.setFillColor(sf::Color::Blue);
	m_circle3.setRadius(30.0f);
	m_circle3.setPosition(500.0f, 450.0f);
	
	m_font.loadFromFile("C:/Windows/Fonts/comic.ttf");
	yellow.setFont(m_font);
	yellow.setCharacterSize(44);
	yellow.setFillColor(sf::Color::Yellow);

	blue.setFont(m_font);
	blue.setCharacterSize(44);
	blue.setFillColor(sf::Color::Blue);

	red.setFont(m_font);
	red.setCharacterSize(44);
	red.setFillColor(sf::Color::Red);
}

void game::returnPos()
{
	std::string s;

	s += std::to_string(static_cast<int>(m_circle.getPosition().x));
	s += ",";
	s += std::to_string(static_cast<int>(m_circle.getPosition().y));

	myClient.SendString(s);
}
void game::returnPos2()
{
	std::string s;

	s += std::to_string(static_cast<int>(m_circle2.getPosition().x));
	s += ",";
	s += std::to_string(static_cast<int>(m_circle2.getPosition().y));

	myClient.SendString(s);
}
void game::returnPos3()
{
	std::string s;

	s += std::to_string(static_cast<int>(m_circle3.getPosition().x));
	s += ",";
	s += std::to_string(static_cast<int>(m_circle3.getPosition().y));

	myClient.SendString(s);
}
void game::returnY1()
{
	myClient.SendString(std::to_string(m_circle.getPosition().y));
}
void game::returnY2()
{
	myClient.SendString(std::to_string(m_circle2.getPosition().y));
}
void game::returnY3()
{
	myClient.SendString(std::to_string(m_circle3.getPosition().y));
}
double game::decimalplace(double timed)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << timed;
	std::string s = stream.str();

	return timed;
}
std::vector<std::string> game::splitString(const std::string& s, char delimiter)
{
	std::vector<std::string> splits;
	std::string split;
	std::istringstream ss(s);
	while (std::getline(ss, split, delimiter))
	{
		splits.push_back(split);
	}
	return splits;
}