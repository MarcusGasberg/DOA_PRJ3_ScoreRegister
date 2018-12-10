#include "pch.h"
#include "../DOA_ScoreRegister/Node.h"
#include "../DOA_ScoreRegister/LinkedList.h"

using namespace LinkedList;
#define LARGE_LIST_SIZE 10000
//================================================
// Test fixture for LLToolkit
//================================================
class LLToolkitTest : public testing::Test
{
protected:
	LLToolkitTest()
	{
		valToInsert = 2;// In some tests, explicitly declared value to insert
						//	pointer is necessary due to strict typing in templates
		valToTest = 9;

		emptyList = nullptr;
		singleElementList = new Node<int>(valToInsert);

		n3 = new Node<int>(3);
		n2 = new Node<int>(2, n3);
		n1 = new Node<int>(1, n2);
		largeList = new Node<int>(0);
		for (int i = 0; i < LARGE_LIST_SIZE; i++)
		{
			headInsert(largeList, i);
		}
	}

	~LLToolkitTest()
	{
	}


	// Test members
	Node<int>* emptyList;
	Node<int>* singleElementList;
	Node<int>* largeList;
	int valToInsert;
	int valToTest;
	int buildTestArray[3] = { 1,2,3 };
	int buildSingleArray[1] = { 9 };

	Node<int>* n1;
	Node<int>* n2;
	Node<int>* n3;
};
#pragma region HeadInsert Tests

TEST_F(LLToolkitTest, HeadInsert_EmptyList_HeadValueIsCorrect)
{
	Node<int>* head = nullptr;

	headInsert(head, valToInsert);
	EXPECT_EQ(head->info, valToInsert);
}

TEST_F(LLToolkitTest, HeadInsert_NonEmptyList_HeadValueIsCorrect)
{
	headInsert(n1, valToInsert);
	EXPECT_EQ(n1->info, valToInsert);
}


TEST_F(LLToolkitTest, HeadInsert_NonEmptyList_HeadNextCorrect)
{
	Node<int>* oldN1 = n1;
	headInsert(n1, valToInsert);
	EXPECT_EQ(n1->next, oldN1);
}

#pragma endregion

#pragma region HeadRemove Tests
TEST_F(LLToolkitTest, HeadRemove_EmptyList_NullptrException)
{
	ASSERT_ANY_THROW(
	try
	{
		headRemove(emptyList);
	}
	catch (const std::exception& e)
	{
		EXPECT_STREQ("Nullptr exception", e.what() );
		throw;
	}, std::exception);
}

TEST_F(LLToolkitTest, HeadRemove_SingleList_HeadCorrect)
{
	Node<int>* head = singleElementList;
	headRemove(head);
	EXPECT_EQ(head,nullptr);
}

TEST_F(LLToolkitTest, HeadRemove_NonEmptyList_HeadCorrect)
{
	Node<int>* head = n1;
	headRemove(head);
	EXPECT_EQ(head, n2);
}
#pragma endregion

#pragma region Insert Tests
TEST_F(LLToolkitTest, Insert_EmptyList_PrevPtrCorrect)
{
	ASSERT_ANY_THROW(
		try
	{
		headRemove(emptyList);
	}
	catch (const std::exception& e)
	{
		EXPECT_STREQ("Nullptr exception", e.what());
		throw;
	}, std::exception);
}

TEST_F(LLToolkitTest, Insert_SingleList_PrevPtrNextCorrect)
{
	Node<int>* prev = singleElementList;
	insert(prev, valToTest);
	EXPECT_EQ(prev->next->info, valToTest);
}

TEST_F(LLToolkitTest, Insert_NonEmptyList_EndOfList)
{
	Node<int>* prev = n3;
	insert(prev, valToTest);
	EXPECT_EQ(prev->next->info, valToTest);
}

TEST_F(LLToolkitTest, Insert_NonEmptyList_StartOfList)
{
	Node<int>* prev = n1;
	insert(prev, valToTest);
	EXPECT_EQ(prev->next->info, valToTest);
}

TEST_F(LLToolkitTest, Insert_NonEmptyList_MidOfList)
{
	Node<int>* prev = n2;
	insert(prev, valToTest);
	EXPECT_EQ(prev->next->info, valToTest);
}
#pragma endregion

#pragma region Remove Tests

TEST_F(LLToolkitTest, Remove_EmptyList_NullptrException)
{
	ASSERT_ANY_THROW(
	try
	{
		remove(emptyList);
	}
	catch (const std::exception& e)
	{
		EXPECT_STREQ("Nullptr exception", e.what());
		throw;
	}, std::exception);
}

TEST_F(LLToolkitTest, Remove_SingleList_NullptrException)
{

	ASSERT_ANY_THROW(
		try
	{
		remove(singleElementList);
	}
	catch (const std::exception& e)
	{
		EXPECT_STREQ("Nullptr exception", e.what());
		throw;
	}, std::exception);
}

TEST_F(LLToolkitTest, Remove_NonEmptyList_EndOfList)
{
	Node<int>* prev = n2;
	remove(prev);
	EXPECT_EQ(prev->next, nullptr);
}

TEST_F(LLToolkitTest, Remove_NonEmptyList_MidOfList)
{

	Node<int>* prev = n1;
	remove(prev);
	EXPECT_EQ(prev->next->info, 3);
}
#pragma endregion

#pragma region Copy Tests

TEST_F(LLToolkitTest, Copy_NonEmptyList_AllInfoEqual)
{
	int sumOriginal = 0;
	int sumCopy = 0;
	Node<int>* original = n1;
	Node<int>* theCopy = copy(n1);
	for (original; original != nullptr; original = original->next)
	{
		sumOriginal += original->info;
	}
	for (theCopy; theCopy != nullptr; theCopy = theCopy->next)
	{
		sumCopy += theCopy->info;
	}
	EXPECT_EQ(sumOriginal, sumCopy);
}

TEST_F(LLToolkitTest, Copy_HugeList_AllInfoEqual)
{
	int sumOriginal = 0;
	int sumCopy = 0;
	Node<int>* original = largeList;
	Node<int>* theCopy = copy(largeList);
	for (original; original != nullptr; original = original->next)
	{
		sumOriginal += original->info;
	}
	for (theCopy; theCopy != nullptr; theCopy = theCopy->next)
	{
		sumCopy += theCopy->info;
	}
	EXPECT_EQ(sumOriginal, sumCopy);
}


TEST_F(LLToolkitTest, Copy_NonEmptyList_CopyPtrNotEqualOriginal)
{
	bool originalEqualCopy = false;
	Node<int>* original = n1;
	Node<int>* theCopy = copy(n1);
	for (original; original != nullptr; original = original->next)
	{
		if (original == theCopy)
		{
			originalEqualCopy = true;
		}
		theCopy = theCopy->next;
	}
	EXPECT_FALSE(originalEqualCopy);
}


TEST_F(LLToolkitTest, Copy_EmptyList_CopyPtrEqualNull)
{
	Node<int>* theCopy = copy(emptyList);
	ASSERT_EQ(theCopy, nullptr);
}


TEST_F(LLToolkitTest, Copy_SingleElementList_CopyPtrNotEqualOriginal)
{

	bool originalEqualCopy = false;
	Node<int>* original = singleElementList;
	Node<int>* theCopy = copy(singleElementList);
	for (original; original != nullptr; original = original->next)
	{
		if (original == theCopy)
		{
			originalEqualCopy = true;
		}
		theCopy = theCopy->next;
	}
	EXPECT_FALSE(originalEqualCopy);
}
#pragma endregion

#pragma region Clone Tests

TEST_F(LLToolkitTest, Clone_NonEmptyList_AllInfoEqual)
{
	int sumOriginal = 0;
	int sumClone = 0;
	Node<int>* original = n1;
	Node<int>* theClone = clone(n1);
	for (original; original != nullptr; original = original->next)
	{
		sumOriginal += original->info;
	}
	for (theClone; theClone != nullptr; theClone = theClone->next)
	{
		sumClone += theClone->info;
	}
	EXPECT_EQ(sumClone, sumOriginal);
}

TEST_F(LLToolkitTest, Clone_HugeList_AllInfoEqual)  //Slower than copy???
{
	int sumOriginal = 0;
	int sumClone = 0;
	Node<int>* original = largeList;
	Node<int>* theClone = clone(largeList);
	for (original; original != nullptr; original = original->next)
	{
		sumOriginal += original->info;
	}
	for (theClone; theClone != nullptr; theClone = theClone->next)
	{
		sumClone += theClone->info;
	}
	EXPECT_EQ(sumClone, sumOriginal);
}

TEST_F(LLToolkitTest, Clone_NonEmptyList_CopyPtrNotEqualOriginal)
{
	bool originalEqualCopy = false;
	Node<int>* original = n1;
	Node<int>* theClone = clone(n1);
	for (original; original != nullptr; original = original->next)
	{
		if (original == theClone)
		{
			originalEqualCopy = true;
		}
		theClone = theClone->next;
	}
	EXPECT_FALSE(originalEqualCopy);
}


TEST_F(LLToolkitTest, Clone_EmptyList_CopyPtrEqualNull)
{
	Node<int>* theClone = clone(emptyList);
	ASSERT_EQ(theClone, nullptr);
}


TEST_F(LLToolkitTest, Clone_SingleElementList_CopyPtrNotEqualOriginal)
{

	bool originalEqualCopy = false;
	Node<int>* original = singleElementList;
	Node<int>* theClone = clone(singleElementList);
	for (original; original != nullptr; original = original->next)
	{
		if (original == theClone)
		{
			originalEqualCopy = true;
		}
		theClone = theClone->next;
	}
	EXPECT_FALSE(originalEqualCopy);
}
#pragma endregion

#pragma region Clear Tests

TEST_F(LLToolkitTest, Clear_NonEmptyList_HeadIsNull)
{
	clear(n1);
	EXPECT_EQ(n1, nullptr);
}


TEST_F(LLToolkitTest, Clear_NonEmptyList_AllCleared)
{
	bool allCleared = false;
	clear(n1);
	EXPECT_TRUE(n3->info != 3 && n2->info != 2);
}
#pragma endregion

#pragma region Print Tests

TEST_F(LLToolkitTest, Print_NonEmptyList_123)
{
	testing::internal::CaptureStdout();
	print(n1);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "1-2-3-/");
}

TEST_F(LLToolkitTest, Print_EmptyList_123)
{
	testing::internal::CaptureStdout();
	print(emptyList);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "/");
}

TEST_F(LLToolkitTest, Print_SingleElementList_1)
{
	testing::internal::CaptureStdout();
	print(singleElementList);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "2-/");
}
#pragma endregion

#pragma region Reverse Tests

TEST_F(LLToolkitTest, Reverse_NonEmptyList_321)
{
	reverse(n1);
	testing::internal::CaptureStdout();
	print(n1);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "3-2-1-/");
}

TEST_F(LLToolkitTest, Reverse_SingleElementList_2)
{
	reverse(singleElementList);
	testing::internal::CaptureStdout();
	print(singleElementList);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "2-/");
}


TEST_F(LLToolkitTest, Reverse_EmptyList_Null)
{
	reverse(emptyList);
	EXPECT_EQ(emptyList, nullptr);
}
#pragma endregion

#pragma region Split Tests

TEST_F(LLToolkitTest, Split_NonEmptyList_23)
{
	split(n1);
	testing::internal::CaptureStdout();
	print(n2);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "2-3-/");
}

TEST_F(LLToolkitTest, Split_NonEmptyList_1)
{
	split(n1);
	testing::internal::CaptureStdout();
	print(n1);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "1-/");
}

TEST_F(LLToolkitTest, Split_EmptyList_NullPtrException)
{
	split(n1);
	testing::internal::CaptureStdout();
	print(n1);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "1-/");
}

TEST_F(LLToolkitTest, Split_EmptyList_NullptrException)
{
	ASSERT_ANY_THROW(
		try
	{
		split(emptyList);
	}
	catch (const std::exception& e)
	{
		EXPECT_STREQ("Nullptr exception", e.what());
		throw;
	}, std::exception);
}

TEST_F(LLToolkitTest, Split_SingleElementList_NextIsNullptr)
{
	split(singleElementList);
	EXPECT_EQ(singleElementList->next, nullptr);
}

#pragma endregion

#pragma region Build Tests


TEST_F(LLToolkitTest, Build_NonEmptyList_123)
{
	Node<int>* buildPtr = build<int>(buildTestArray, 3);
	testing::internal::CaptureStdout();
	print(n1);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "1-2-3-/");
}

TEST_F(LLToolkitTest, Build_SingleList_9)
{
	Node<int>* buildPtr = build<int>(buildSingleArray, 1);
	EXPECT_EQ(buildPtr->info, 9);
}

TEST_F(LLToolkitTest, Build_EmptyList_nullptrException)
{
	ASSERT_ANY_THROW(
		try
	{
		Node<int>* buildPtr = build<int>(nullptr, 0);
	}
	catch (const std::exception& e)
	{
		EXPECT_STREQ("Nullptr exception", e.what());
		throw;
	}, std::exception);

}

#pragma endregion


TEST_F(LLToolkitTest, Join_NonEmptyList_123)
{
	join(n1, singleElementList);
	testing::internal::CaptureStdout();
	print(n1);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), "1-2-3-2-/");
}

TEST_F(LLToolkitTest, Join_SingleListToSelf_123)
{
	ASSERT_ANY_THROW(
	try
	{
		join(singleElementList, singleElementList);
	}
	catch (const std::exception& e)
	{
		EXPECT_STREQ("head1 is equal to head2", e.what());
		throw;
	}, std::exception);
}


TEST_F(LLToolkitTest, Join_NonEmptyListToSelf_123)
{
	ASSERT_ANY_THROW(
	try
	{
		join(n1, n1);
	}
	catch (const std::exception& e)
	{
		EXPECT_STREQ("head1 is equal to head2", e.what());
		throw;
	}, std::exception);
}
