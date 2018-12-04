#include "SearchableScoreRegister.h"

int main()
{
	SearchableScoreRegister ssr;
	ssr.sb_.addToSearchHistory("Hello");
	ssr.sb_.addToSearchHistory("Hey");
	ssr.sb_.addToSearchHistory("Heydan");
	ssr.sb_.autocomplete("He");
	ssr.insertGame(GameScore("Hello", "Baller", 2, 0));
	ssr.insertGame(GameScore("Hey", "Baller",0 , 3));
	ssr.insertGame(GameScore("Fuck", "Face", 0, 3));
	ssr.insertGame(GameScore("Heydan", "Hey", 0, 3));
	ssr.scoreLookup();
}