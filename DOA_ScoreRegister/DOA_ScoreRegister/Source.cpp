#include "SearchableScoreRegister.h"

int main()
{
	SearchableScoreRegister ssr;
	ssr.insertGame(GameScore("Hello", "Baller", 2, 0));
	ssr.insertGame(GameScore("Hey", "Baller", 0, 3));
	ssr.insertGame(GameScore("Fuck", "Face", 0, 3));
	ssr.insertGame(GameScore("Hello", "Fuck", 6, 0));
	ssr.insertGame(GameScore("Hey", "Fuck", 0, 4));
	ssr.insertGame(GameScore("Heydan", "Hey", 0, 6));
	ssr.insertGame(GameScore("Suck", "Memes", 5, 0));
	ssr.insertGame(GameScore("Suck", "Hey", 1, 0));
	std::string searchString;
	std::cin >> searchString;
	std::cout << "Search: " << searchString <<	std::endl;
	ssr.searchScoreRegister(searchString);
}