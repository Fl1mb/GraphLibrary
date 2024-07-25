#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Trie.h"

void show(const std::vector<std::string>& vec) {
	for (const std::string& str : vec) {
		std::cout << str << " ";
 	}
	std::cout << std::endl;
}

int main() {
	Trie trie;
	trie.AddWord("Dog");
	trie.AddWord("Fuck");
	trie.AddWord("Hello!");

	std::vector <std::string> vec = trie.TrieToVector();
	show(vec);

	return 0;
}