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

	//Find all known auto completes for the string s
	void autocomplete(const std::string& s)
	{
		container_.findAllWithPrefix(s, strings_);
	}

	//Prints the auto completed strings. Usually called after autocomplete.
	void printAutoComplete() const
	{
		for (const std::string& s : strings_)
		{
			std::cout << s << std::endl;
		}
	}

	//Returns a vector with the autocompleted strings
	const std::vector<std::string>& getStrings()
	{
		return strings_;
	}

	//Adds a string toAdd to the strings_ that can be autocompleted to
	void addToSearchHistory(const std::string& toAdd)
	{	
		container_.insert(toAdd);
	}

	//Deletes a string from the strings_ that can be autocompleted to
	void deleteFromSearchHistory(const std::string& toDel)
	{
		container_.remove(toDel);
	}

private:
	Trie container_;
	std::vector<std::string> strings_;
};
