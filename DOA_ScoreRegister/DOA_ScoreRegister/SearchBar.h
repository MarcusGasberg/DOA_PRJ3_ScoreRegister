#pragma once
#include <iostream>
#include <string>
#include "Trie.h"

class SearchBar
{
public:
	SearchBar()
	{
	}

	~SearchBar()
	{
	}

	void autocomplete(std::string prefix)
	{
		container_.findAllWithPrefix(prefix,strings_);
	}

	void autocomplete()
	{
		container_.findAllWithPrefix(wordSearched_, strings_);
	}

	void printAutoComplete() const
	{
		for (std::string s : strings_)
		{
			std::cout << s << std::endl;
		}
	}

	void addToSearchHistory(std::string toAdd)
	{
		container_.insert(toAdd);
	}

	void deleteFromSearchHistory(std::string toDel)
	{
		container_.remove(toDel);
	}

	friend istream& operator>>(istream &input, SearchBar sb)
	{
		input >> sb.wordSearched_;
		return input;
	}
private:
	Trie container_;
	vector<std::string> strings_;
	std::string wordSearched_;
};
