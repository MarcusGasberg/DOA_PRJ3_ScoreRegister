#pragma once
#include "SearchBar.h"
#include "ScoreRegister.h"
#include "Hash.h"

int ARRAY_SIZE = 100;

class SearchableScoreRegister
{
public:
	SearchableScoreRegister()
		:sr_(100)
	{
	}

	~SearchableScoreRegister()
	{
	}

	SearchBar sb_;

	void scoreLookup()
	{
		vector<std::string>& strings = sb_.getStrings();
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
	}

private:
	ScoreRegister sr_;
};
