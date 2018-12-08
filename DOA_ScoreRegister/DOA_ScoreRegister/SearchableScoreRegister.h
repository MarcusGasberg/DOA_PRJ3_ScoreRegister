#pragma once
#include "SearchBar.h"
#include "ScoreRegister.h"
#include "Hash.h"

int ARRAY_SIZE = 100;

class SearchableScoreRegister
{
public:
	SearchableScoreRegister()
		:sr_(ARRAY_SIZE)
	{
	}

	~SearchableScoreRegister()
	{
	}

	//Searches the score register for all teamnames with the prefix string teamname
	void searchScoreRegister(const std::string& teamname)
	{
		sb_.autocomplete(teamname);
		scoreLookup();
	}

	//Inserts a game into the score register, and registers the teams for autocompletion
	void insertGame(const GameScore& gs)
	{
		sr_.insertRegister(gs);
		sb_.addToSearchHistory(gs.getTeam1());
		sb_.addToSearchHistory(gs.getTeam2());
	}

private:
	ScoreRegister sr_;
	SearchBar sb_;

	//Helper function for looking up scores and printing them.
	void scoreLookup()
	{
		const std::vector<std::string>& strings = sb_.getStrings();
		for (const std::string& s : strings)
		{
			LinkedList::Node<GameScore>** n = nullptr;
			sr_.scoreSearch(s, n);
			while ((*n) != nullptr)
			{
				(*n)->info.printGameScore();
				(*n) = (*n)->next;
			}
		}
	}
};
