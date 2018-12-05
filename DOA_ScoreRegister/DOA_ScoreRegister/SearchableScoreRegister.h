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

	void searchScoreRegister(std::string teamname)
	{
		sb_.autocomplete(teamname);
		scoreLookup();
	}

	void scoreLookup()
	{
		std::vector<std::string>& strings = sb_.getStrings();
		for (std::string s : strings)
		{
			LinkedList::Node<GameScore>* n = nullptr;
			sr_.scoreSearch(s,n);
			while ( n != nullptr)
			{
				n->info.printGameScore();
				n = n->next;
			}
		}
	}

	void insertGame(GameScore gs)
	{
		sr_.insertRegister(gs);
		sb_.addToSearchHistory(gs.getTeam1());
		sb_.addToSearchHistory(gs.getTeam2());
	}

private:
	ScoreRegister sr_;
	SearchBar sb_;
};
