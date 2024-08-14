#include "Trie.h"

void Trie::remove(const std::string& word, int depth, TrieNode* node)
{
    if (!node)return;

    if (depth == word.size()) {
        if (node->isWord)
            node->isWord = false;
    }

    remove(word, depth + 1, node->hash[word[depth]]);
}

bool Trie::searchRoot(const std::string& str, TrieNode* node)
{
    for (int i = 0; i < str.size(); i++) {
        char ch = str[i];

        if (!node->hash.count(ch)) {
            if (ch == '.') {
                for (auto it : node->hash) {
                    TrieNode* temp = it.second;
                    if (searchRoot(str.substr(i + 1), temp)) {
                        return true;
                    }
                }
            }
            return false;
        }
        else {
            node = node->hash[ch];
        }

    }
    return node->isWord;
}

void Trie::DepthFirstSearch(TrieNode* node, std::string str, std::vector<std::string>& vec)
{
    if (!node)return;

    if (node->isWord)
        vec.push_back(str);

    for (const auto& pair : node->hash) {
        std::string temp = str + pair.first;
        DepthFirstSearch(pair.second, temp, vec);
    }
}

Trie::Trie()
{
	head = new TrieNode;
}

Trie::Trie(const std::string& word)
{
	head = new TrieNode;
	AddWord(word);
}

void Trie::AddWord(const std::string& word)
{
	TrieNode* node = head;

	for (char it : word) {
		if (!node->hash[it])
			node->hash[it] = new TrieNode;
		node = node->hash[it];
	}
	node->isWord = true;
}

void Trie::DeleteWord(const std::string& word)
{
    if (search(word)) {
        remove(word, 0, head);
    }
}

std::vector<std::string> Trie::TrieToVector()
{
    std::vector<std::string> result;
    DepthFirstSearch(head, "", result);
    return result;
}

bool Trie::search(const std::string& str)
{
    return searchRoot(str, head);
}
