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

	//Inserts a GameScore gs into the score register.
	void insertRegister(const GameScore& gs)
	{
		LinkedList::Node<GameScore>** n; //Pointer-pointer necessary to get address of the node in hashmap
		if(hashMap_.search(gs.getTeam1(),n))
		{
			LinkedList::headInsert(*n, gs);
		}
		else
		{
			hashMap_.insert(gs.getTeam1(), new LinkedList::Node<GameScore>(gs));
		}

		if (hashMap_.search(gs.getTeam2(), n))
		{
			LinkedList::headInsert(*n, gs);
		}
		else
		{
			hashMap_.insert(gs.getTeam2(), new LinkedList::Node<GameScore>(gs));
		}
	}

	//Searches the score register for the headptr to the GameScore linked list
	void scoreSearch(const std::string& s,LinkedList::Node<GameScore>**& n)
	{
		hashMap_.search(s, n);
	}

private:
	OAHashMap<std::string, LinkedList::Node<GameScore>*> hashMap_;
};
