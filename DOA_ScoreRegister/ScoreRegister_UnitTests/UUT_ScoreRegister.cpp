#include "pch.h"
#include "../DOA_ScoreRegister/ScoreRegister.h"

int ARRAY_SIZE = 10;

//================================================
// Test fixture for testing the ScoreRegister
//================================================
class ScoreRegisterTest : public testing::Test
{
protected:
	ScoreRegisterTest():
		sr_(ARRAY_SIZE)
	{
	}

	~ScoreRegisterTest()
	{
	}


	// Test members
	ScoreRegister sr_;
	GameScore g1 = { "Team1","Team2",0,1 };
	GameScore g2 = { "Team2","Team3",6,0 };
	GameScore g3 = { "Team3","Team2",0,3 };
	LinkedList::Node<GameScore>** testNode = nullptr;
	std::vector<GameScore> compareVec = { g1,g2,g3};
};


TEST_F(ScoreRegisterTest, insertSearch_getTeam1_correcTeam) {
	sr_.insertRegister(g1);
	sr_.scoreSearch("Team1", testNode);
	ASSERT_EQ((*testNode)->info.getTeam1(), g1.getTeam1());
}

TEST_F(ScoreRegisterTest, insertSearch_getTeam2_correctTeam) {
	sr_.insertRegister(g1);
	sr_.scoreSearch("Team1", testNode);
	ASSERT_EQ((*testNode)->info.getTeam2(), g1.getTeam2());
}

TEST_F(ScoreRegisterTest, insertSearch_2inserted_insertCorrect) {
	sr_.insertRegister(g1);
	sr_.insertRegister(g2);
	sr_.scoreSearch("Team2", testNode);
	ASSERT_EQ((*testNode)->next->info.getTeam2(), g1.getTeam2());
}