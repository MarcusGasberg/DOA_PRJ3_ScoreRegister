#include "pch.h"
#include "../DOA_ScoreRegister/SearchBar.h"
class SearchBarTest : public testing::Test
{
protected:
	SearchBarTest()
	{
		sb_.addToSearchHistory(testString1_);
		sb_.addToSearchHistory(testString2_);
		sb_.addToSearchHistory(testString3_);
	}

	~SearchBarTest()
	{
	}


	// Test members
	SearchBar sb_;
	std::string testString1_ = "test1";
	std::string testString2_ = "test2";
	std::string testString3_ = "test3";
	std::vector<std::string> compareVec = { testString1_,testString2_,testString3_ };
};

TEST_F(SearchBarTest,Autocomplete_autocomplete_strings_correct) {
	sb_.autocomplete("test");
	std::vector<std::string> testVec = sb_.getStrings();
	for (size_t i = 0; i < testVec.size(); i++ )
	{
		ASSERT_EQ(compareVec[i], testVec[i]);
	}
}

TEST_F(SearchBarTest, Autocomplete_autocomplete_test1_correct) {
	sb_.autocomplete("test1");
	std::vector<std::string> testVec = sb_.getStrings();
	ASSERT_EQ(testVec.front(), testString1_);
}

TEST_F(SearchBarTest, Autocomplete_autocomplete_emptyString_empty) {
	sb_.autocomplete("");
	std::vector<std::string> testVec = sb_.getStrings();
	ASSERT_EQ(testVec.front(),"");
}

TEST_F(SearchBarTest, Autocomplete_autocomplete_wrongString_empty) { //Oh shit trie doesn't return if the word is wrong.
	sb_.autocomplete("test5");
	std::vector<std::string> testVec = sb_.getStrings();
	ASSERT_TRUE(testVec.empty());
}