#pragma once
#include <map>
#include <vector>

using namespace std;

class Trie
{
	class TrieNode;

	typedef map<char, TrieNode*> TrieMap;
	typedef map<char, TrieNode*>::iterator TrieMapIter;

	// Internal TrieNode class - not relevant outside Trie
	class TrieNode
	{
	public:
		TrieNode(char c = '\0', bool cw = false, TrieNode* p = nullptr) :
			val(c), parent(p), completesWord(cw)
		{
			children.clear();
		}

		char val;
		TrieNode* parent;
		bool completesWord;
		TrieMap children;
	};



public:
	Trie()
	{
		root = new TrieNode('\0', true);
	}


	~Trie()
	{

	}


	void insert(string str) const
	{
		TrieNode* cur = root;
		TrieMapIter res;
		int i = 0;
		for (; i < str.length(); i++)
		{
			if ((res = cur->children.find(str[i])) != cur->children.end())
			{
				cur = res->second;
			}
			else
			{
				cur->children[str[i]] = new TrieNode(str[i],false,cur);
				if((res = cur->children.find(str[i])) != cur->children.end())
					cur = res->second;
			}
		}
		cur->completesWord = true;
	}


	bool search(string str) const
	{
		if (str.empty())
		{
			return true;
		}
		TrieNode* cur = root;
		TrieMapIter res;

		for (size_t i = 0; i < str.length(); i++)
		{
			if ((res = cur->children.find(str[i])) != cur->children.end())
			{
				cur = res->second;
			}
			else
			{
				return false;
			}
		}

		return cur->completesWord;
	}


	void remove(string str) const
	{
		TrieNode* cur = root;
		TrieMapIter res;
		int i = 0;
		for (; i < str.length(); i++)
		{
			if ((res = cur->children.find(str[i])) != cur->children.end())
			{
				cur = res->second;
			}
			else return;
		}
		if (cur->completesWord)
		{
			cur->completesWord = false;
			while (cur->completesWord == false && cur->children.empty())
			{
				cur->children.erase(str[i--]);
				cur = cur->parent;
			}
		}
	}

	void findAllWithPrefix(string prefix, vector<string>& strings) const
	{
		strings.clear();
		if (prefix.empty()) {
			strings.push_back(prefix);
		}
		TrieNode* cur = root;
		if (findPrefixEnd(prefix, cur))
			recursiveFindWords(prefix, cur, strings);
	}



private:

	// findPrefixEnd: 
	// Sets the parameter end to the last node in the prefix of str and returns the length of the prefix
	unsigned int findPrefixEnd(string str, TrieNode*& end) const
	{
		TrieNode* cur = root;
		TrieMapIter res;
		unsigned int i = 0;

		// Find (part of) key already in trie
		for (; i < str.length(); i++)
		{
			if ((res = cur->children.find(str[i])) != cur->children.end())
			{
				cur = res->second;
			}
			else break;
		}

		end = cur;
		return i;
	}

	void recursiveFindWords(string prefix,TrieNode* prefixEndNode, vector<string>& strings) const
	{
		if (prefixEndNode->completesWord)
			strings.push_back(prefix);
		for (TrieMapIter i = prefixEndNode->children.begin(); i != prefixEndNode->children.end(); ++i)
		{
			recursiveFindWords(prefix + i->first,i->second, strings);
		}
	}


	TrieNode* root;
};
