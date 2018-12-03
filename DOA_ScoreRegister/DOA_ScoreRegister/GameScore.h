#pragma once
#include <iostream>
#include <string>

class GameScore
{
public:
	GameScore(std::string t1, std::string t2, int sc1, int sc2)
		:team1_(t1),team2_(t2),scoreTeam1_(sc1),scoreTeam2_(sc2)
	{	}

	virtual ~GameScore()
	{
	}

	virtual void printGameScore() const
	{
		std::cout << team1_ << " [" << scoreTeam1_ << " : " << scoreTeam2_ << "] " << team2_ << std::endl;
	}

	std::string getTeam1() const
	{
		return team1_;
	}

	std::string getTeam2() const
	{
		return team2_;
	}


private:
	std::string team1_;
	std::string team2_;
	int scoreTeam1_;
	int scoreTeam2_;
};
