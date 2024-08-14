#pragma once
#include <unordered_map>
#include <string>




class Trie {
	struct TrieNode {
		std::unordered_map<char, TrieNode*> hash;
		bool isWord;

		TrieNode() : hash(), isWord(false) {}
	};

	TrieNode* head;

	void remove(const std::string& word, int depth, TrieNode* node);
	bool searchRoot(const std::string& str, TrieNode* node);
	void DepthFirstSearch(TrieNode* node, std::string str, std::vector<std::string>& vec);

public:
	Trie();
	Trie(const std::string& word);

	void AddWord(const std::string& word);
	void DeleteWord(const std::string& word);

	std::vector<std::string> TrieToVector();
	
	
	bool search(const std::string& str);

};