#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

class GameScore
{
public:
	GameScore()
		:team1_("Team 1"), team2_("Team 2"), scoreTeam1_(0), scoreTeam2_(0),timeStamp_(std::chrono::system_clock::now())
	{	}

	GameScore(const std::string& t1, const std::string& t2, int sc1, int sc2)
		:team1_(t1), team2_(t2), scoreTeam1_(sc1), scoreTeam2_(sc2), timeStamp_(std::chrono::system_clock::now())
	{	}

	virtual ~GameScore()
	{
	}

	//Prints the teams and the score between them
	virtual void printGameScore() const
	{
		std::time_t t = std::chrono::system_clock::to_time_t(timeStamp_);
		std::cout << "\t" << team1_ << " [" << scoreTeam1_ << " : " << scoreTeam2_ << "] " << team2_;
		std::cout << ". Game finished: " << std::ctime(&t);
	}

	const std::string& getTeam1() const
	{
		return team1_;
	}

	const std::string& getTeam2() const
	{
		return team2_;
	}


private:
	std::string team1_;
	std::string team2_;
	int scoreTeam1_;
	int scoreTeam2_;
	const std::chrono::system_clock::time_point timeStamp_;
};
