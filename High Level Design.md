# Chess - High Level Design

The User decides if he wants to play against a bot or play against another person.

* When its a real player turn: the server requests a move from the graphics (the player moves the pieces on the graphics).

* When its a `Bot` turn, it asks an `Api` what the move should be and sends that move to the graphics.

	> The server and the api talk through a pipe