#include "Pipe.h"
#include <iostream>
#include "Game.hpp"

void connectToPipe(Pipe& p)
{
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		std::cout << "cant connect to graphics" << std::endl;
		std::cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << std::endl;
		std::cin >> ans;

		if (ans == "0")
		{
			std::cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}
}

void main()
{
	Pipe chessPipe(0);
	connectToPipe(chessPipe);

	Pipe changePipe(1);
	connectToPipe(changePipe);

	char msgToGraphics[1024];

	strcpy_s(msgToGraphics, "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0"); // just example...
	Game game;
	chessPipe.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	std::string msgFromGraphics = chessPipe.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
	
		strcpy_s(msgToGraphics, std::to_string(static_cast<unsigned int>(game.move(msgFromGraphics))).c_str()); // msgToGraphics should contain the result of the operation

		// return result to graphics		
		chessPipe.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = chessPipe.getMessageFromGraphics();
	}

	chessPipe.close();
	changePipe.close();
}