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
		hashMap_.insert(gs.getTeam1(),gs);
		hashMap_.insert(gs.getTeam2(), gs);
	}

	void printScores() const
	{

	}

private:
	OAHashMap<std::string, LinkedList::Node<GameScore>> hashMap_;
};
