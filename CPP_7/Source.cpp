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

bool showDialogBot()
{
	int ans = MessageBox(NULL, "Play against the computer?", "Playing Method", MB_YESNO);
	return(ans == IDYES ? true : false);
}

void main()
{
	bool isBotPlaying = showDialogBot();

	Pipe chessPipe(0);
	Pipe changePipe(1);

	connectToPipe(chessPipe);
	connectToPipe(changePipe);

	char msgToGraphics[1024];

	strcpy_s(msgToGraphics, "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0"); // just example...
	Game game(chessPipe, changePipe, isBotPlaying);
	chessPipe.sendMessageToGraphics(msgToGraphics);   // send the board string

	std::string msgFromGraphics = "";

	while (msgFromGraphics != "quit")
	{
		if (game.isBotPlaying()) // if bot is playing need to get one turn form api, one from player
		{
			if (Utils::WhoseTurnIsIt(game._players) != BOT_TURN)
			{
				msgFromGraphics = chessPipe.getMessageFromGraphics();
				if (msgFromGraphics == "quit")
				{
					exit(0);
				}
				strcpy_s(msgToGraphics, std::to_string(static_cast<unsigned int>(game.move(msgFromGraphics))).c_str()); // msgToGraphics should contain the result of the operation
				chessPipe.sendMessageToGraphics(msgToGraphics);
			}
			else
			{
				msgFromGraphics = game.getMoveFromBot();
				MoveCode moveCode = game.move(msgFromGraphics);

				if (moveCode == MoveCode::CheckMate) // if bot lost or won
				{
					exit(0);
				}
			}
		}
		else
		{
			msgFromGraphics = chessPipe.getMessageFromGraphics();
			if (msgFromGraphics == "quit")
			{
				exit(0);
			}
			strcpy_s(msgToGraphics, std::to_string(static_cast<unsigned int>(game.move(msgFromGraphics))).c_str()); // msgToGraphics should contain the result of the operation

			// return result to graphics		
			chessPipe.sendMessageToGraphics(msgToGraphics);
		}
	}

	chessPipe.close();
	changePipe.close();
}