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

	void autocomplete(std::string s)
	{
		container_.findAllWithPrefix(s, strings_);
	}

	void printAutoComplete() const
	{
		for (std::string s : strings_)
		{
			std::cout << s << std::endl;
		}
	}

	std::vector<std::string>& getStrings()
	{
		return strings_;
	}

	void addToSearchHistory(std::string toAdd)
	{	
		container_.insert(toAdd);
	}

	void deleteFromSearchHistory(std::string toDel)
	{
		container_.remove(toDel);
	}

private:
	Trie container_;
	std::vector<std::string> strings_;
};
