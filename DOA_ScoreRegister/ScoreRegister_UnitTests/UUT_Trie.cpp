#include "pch.h"
#include "../DOA_ScoreRegister/Trie.h"
#include <list>
#pragma region TestClasses
//================================================
// Test fixture for testing the Trie-function findAllWithPrefix
//================================================
class TrieTestFindAllWithPrefix : public testing::Test
{
public:
	TrieTestFindAllWithPrefix() : uut(nullptr) {}

protected:
	void SetUp() override { uut = new Trie(); strings.clear(); }
	void TearDown() override { delete uut; }
	Trie* uut;
	std::vector<std::string> strings;
};

//================================================
// Test fixture for testing the Trie-functions insert and search
//================================================
class TrieTestInsertSearch : public testing::Test
{
public:
	TrieTestInsertSearch() : uut(nullptr) {}

protected:
	void SetUp() override { uut = new Trie(); }
	void TearDown() override { delete uut; }
	Trie* uut;

};

//================================================
// Test fixture for testing the Trie-function remove
//================================================
class TrieTestRemove : public testing::Test
{
public:
	TrieTestRemove() : uut(nullptr) {}

protected:
	void SetUp() override { uut = new Trie(); }
	void TearDown() override { delete uut; }
	Trie* uut;

};

#pragma endregion

#pragma region TestFindAllWithPrefix

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_EmptyTrieEmptyPrefix_EmptyStringReturned) {
	uut->findAllWithPrefix("", strings);
	ASSERT_EQ(strings.size(), 1);
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_EmptyTrieNonEmptyPrefix_NoStringReturned) {
	uut->findAllWithPrefix("FOO", strings);
	ASSERT_EQ(strings.size(), 0);
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_NoStringsWithPrefix_NoStringsReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("BAD", strings);
	ASSERT_EQ(strings.size(), 0);
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_OneStringsWithPrefix_OneStringReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUNDANCE", strings);
	ASSERT_EQ(strings.size(), 1);
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_OneStringsWithPrefix_CorrectStringReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUNDANCE", strings);
	ASSERT_EQ(strings[0], "SUNDANCE");
}


TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_ThreeStringsWithPrefix_ThreeStringReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUN", strings);
	ASSERT_EQ(strings.size(), 3);
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_ThreeStringsWithPrefix_CorrectStringsReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUN", strings);

	ASSERT_TRUE(
		find(strings.begin(), strings.end(), "SUNDAY") != strings.end() &&
		find(strings.begin(), strings.end(), "SUN") != strings.end() &&
		find(strings.begin(), strings.end(), "SUNDANCE") != strings.end());
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_ManyStringsInsertedThreeStringsWithPrefix_CorrectStringsReturned) {
	uut->insert("BRAVOUR");
	uut->insert("BRAVO");
	uut->insert("BRAVE");
	uut->insert("BAD");

	uut->insert("SUNDAY");
	uut->insert("SU");
	uut->insert("SUN");
	uut->insert("SUNDANCE");
	uut->insert("SO");
	uut->insert("SAM");

	uut->insert("FIX");
	uut->insert("FINISH");
	uut->insert("FINNISH");
	uut->insert("FILE");


	uut->findAllWithPrefix("SUN", strings);

	ASSERT_TRUE(
		find(strings.begin(), strings.end(), "SUNDAY") != strings.end() &&
		find(strings.begin(), strings.end(), "SUN") != strings.end() &&
		find(strings.begin(), strings.end(), "SUNDANCE") != strings.end());
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_ManyStringsInsertedEmptyPrefix_AllStringsReturned) {
	uut->insert("BRAVOUR");
	uut->insert("BRAVO");
	uut->insert("BRAVE");
	uut->insert("BAD");

	uut->insert("SUNDAY");
	uut->insert("SU");
	uut->insert("SUN");
	uut->insert("SUNDANCE");
	uut->insert("SO");
	uut->insert("SAM");

	uut->insert("FIX");
	uut->insert("FINISH");
	uut->insert("FINNISH");
	uut->insert("FILE");


	uut->findAllWithPrefix("", strings);

	ASSERT_EQ(strings.size(), 14 + 1);	// Empty string always in Trie
}


#pragma endregion
#pragma region TestInsertSearch

TEST_F(TrieTestInsertSearch, Search_StringInsertedTwice_StringFound) {
	uut->insert("SUN");
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUN"));
}

TEST_F(TrieTestInsertSearch, Search_VanillaTrie_EmptyStringFound) {
	ASSERT_TRUE(uut->search(""));
}

TEST_F(TrieTestInsertSearch, Search_VanillaTrie_StringNotFound) {
	ASSERT_FALSE(uut->search("SUN"));
}

TEST_F(TrieTestInsertSearch, Search_StringInserted_StringFound) {
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUN"));
}


TEST_F(TrieTestInsertSearch, Search_StringInserted_PrefixNotFound) {
	uut->insert("SUNDAY");
	ASSERT_FALSE(uut->search("SUN"));
}

TEST_F(TrieTestInsertSearch, Search_PrefixStringInserted_StringFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUN"));
}

TEST_F(TrieTestInsertSearch, Search_PrefixStringInserted_OriginalStringFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUNDAY"));
}

#pragma endregion
#pragma region TestRemove
TEST_F(TrieTestRemove, Search_StringInsertedTwiceRemovedOnce_StringNotFound) {
	uut->insert("SUN");
	uut->insert("SUN");
	uut->remove("SUN");
	ASSERT_FALSE(uut->search("SUN"));
}


TEST_F(TrieTestRemove, Remove_OnlyWordInTrie_WordNotFound) {
	uut->insert("SUNDAY");
	uut->remove("SUNDAY");
	ASSERT_FALSE(uut->search("SUNDAY"));
}

TEST_F(TrieTestRemove, Remove_OnlyWordInTrie_EmptyStringStillFound) {
	uut->insert("SUNDAY");
	uut->remove("SUNDAY");
	ASSERT_TRUE(uut->search(""));
}

TEST_F(TrieTestRemove, Remove_WordReInserted_WordFound) {
	uut->insert("SUNDAY");
	uut->remove("SUNDAY");
	uut->insert("SUNDAY");
	ASSERT_TRUE(uut->search("SUNDAY"));
}

TEST_F(TrieTestRemove, Remove_NonPresentPrefixRemoved_WordStillFound) {
	uut->insert("SUNDAY");
	uut->remove("SUN");
	ASSERT_TRUE(uut->search("SUNDAY"));
}

TEST_F(TrieTestRemove, Remove_PrefixRemoved_CompleteWordStillFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUN");
	ASSERT_TRUE(uut->search("SUNDAY"));
}

TEST_F(TrieTestRemove, Remove_PrefixRemoved_PrefixNotFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUN");
	ASSERT_FALSE(uut->search("SUN"));
}

TEST_F(TrieTestRemove, Remove_LongWordRemoved_PrefixStillFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUNDAY");
	ASSERT_TRUE(uut->search("SUN"));
}

TEST_F(TrieTestRemove, Remove_LongWordRemoved_LongWordFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUNDAY");
	ASSERT_FALSE(uut->search("SUNDAY"));
}

TEST_F(TrieTestRemove, Remove_MoreWordsInTrieOneRemoved_OtherWordsFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->remove("SUNDAY");
	ASSERT_FALSE(uut->search("SUNDAY"));
	ASSERT_TRUE(uut->search("SUNDANCE"));
	ASSERT_TRUE(uut->search("SUN"));
}
#pragma endregion