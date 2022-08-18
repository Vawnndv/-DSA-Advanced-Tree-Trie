#include <iostream>
using namespace std;

const int ALPHABET_SIZE = 26;

// Trie node
struct TrieNode{
	TrieNode *children[ALPHABET_SIZE];
	bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
TrieNode *getNode(){
	TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

// Test whether a trie empty
bool isTrieEmpty(TrieNode *root){
	if (!root)
		return true;
	TrieNode *pCrawl = root;
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (pCrawl->children[i])
			return false;
	return true;
}

// Get the number of items in a trie
unsigned int numberOfItem(TrieNode *root){
	int result = 0;
	if (isTrieEmpty(root))
		return 0;
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i]){
			if (root->children[i]->isEndOfWord)
				result += 1 + numberOfItem(root->children[i]);
			else
				result += numberOfItem(root->children[i]);
		}
	return result;
}

// Find the item in a trie
bool find(TrieNode *root, string key){
	if (isTrieEmpty(root))
		return false;
	TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++){
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl->isEndOfWord);
}


// Insert a new item into the trie
void insert(TrieNode *root, string key){
	TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++){
		int index = key[i] - 'a';       // xác định vị trí của kí tự
		if (!pCrawl->children[index])   
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	pCrawl->isEndOfWord = true;
}

// Remove an item from the trie
TrieNode* remove(TrieNode* root, string key, int depth = 0){
    // Khi Trie rỗng
    if (!root)
        return NULL;
 
    // Khi ở kí tự cuối cùng
    if (depth == key.size()) {
 
        // Nếu là Node cuối của chuỗi nhưng vẫn còn liên kết với Node khác
        if (root->isEndOfWord)
            root->isEndOfWord = false;
 
        // Nếu là Node cuối cùng thì xóa Node đó
        if (isTrieEmpty(root)) {
            delete (root);
            root = NULL;
        }
 
        return root;
    }
 
    // Khi không ở kí tự cuối cùng
    int index = key[depth] - 'a';
	root->children[index] = remove(root->children[index], key, depth + 1);

	// Nếu root không còn liên kết với Node khác và không phải kết thúc chuỗi
    if (isTrieEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = NULL;
    }
 
    return root;
}

// Build a trie from given item 
TrieNode *buildTrie(string key[], int n){
	TrieNode * temp = getNode();
	for (int i = 0; i < n; i++)
		insert(temp,key[i]);
	return temp;
}

// Remove all element from the trie
TrieNode *removeTrie(TrieNode *root){
	if (isTrieEmpty(root)){
		delete (root);
		root = NULL;
		return root;
	}
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			removeTrie(root->children[i]);
	delete (root);
	root = NULL;
	return root;
}