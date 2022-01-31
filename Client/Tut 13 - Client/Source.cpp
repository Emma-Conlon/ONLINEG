/*
Tutorial 13 Client Solution
Author: Pindrought
Date: 02/26/2017
*/
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif

#include "Game.h"
#include "Client.h"
#include <iostream>

int main()
{
	game game1;

	game1.run();
	//Create client to connect to server 127.0.0.1 [localhost] on port 1111
	
	return 0;
}

