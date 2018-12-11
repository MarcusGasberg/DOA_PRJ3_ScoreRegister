#include "SearchableScoreRegister.h"

int main()
{
	SearchableScoreRegister ssr;
	ssr.insertGame(GameScore("Hello", "Bawler", 2, 0));
	ssr.insertGame(GameScore("Hey", "Bawler", 0, 3));
	ssr.insertGame(GameScore("Fiesta", "Face", 0, 3));
	ssr.insertGame(GameScore("Hello", "Fiesta", 6, 0));
	ssr.insertGame(GameScore("Hey", "Fiesta", 0, 4));
	ssr.insertGame(GameScore("Heydan", "Hey", 0, 6));
	ssr.insertGame(GameScore("Suck", "Memes", 5, 0));
	ssr.insertGame(GameScore("Suck", "Hey", 1, 0));
	std::string searchString;
	std::cin >> searchString;
	std::cout << "Search: " << searchString <<	std::endl;
	ssr.searchScoreRegister(searchString);
}