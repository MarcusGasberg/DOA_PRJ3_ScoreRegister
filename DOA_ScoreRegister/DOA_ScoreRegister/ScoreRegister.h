#pragma once
#include <iostream>
#include <string>
#include "GameScore.h"
#include "OAHashMap.h"
#include "LinkedList.h"
#include "Hash.h"


class ScoreRegister
{
public:
	ScoreRegister(size_t mapSize)
		:hashMap_(mapSize,Hash::djb2)
	{
	}

	~ScoreRegister()
	{
	}

	void insertRegister(GameScore gs)
	{
		LinkedList::Node<GameScore>* n;
		if(hashMap_.search(gs.getTeam1(),n))
		{
			LinkedList::headInsert(n,gs);
		}
		else
		{
			hashMap_.insert(gs.getTeam1(), new LinkedList::Node<GameScore>(gs));
		}

		if (hashMap_.search(gs.getTeam2(), n))
		{
			LinkedList::headInsert(n, gs);
		}
		else
		{
			hashMap_.insert(gs.getTeam2(), new LinkedList::Node<GameScore>(gs));
		}
	}

	void scoreSearch(std::string s,LinkedList::Node<GameScore>*& n)
	{
		hashMap_.search(s, n);
	}

private:
	OAHashMap<std::string, LinkedList::Node<GameScore>*> hashMap_;
};
