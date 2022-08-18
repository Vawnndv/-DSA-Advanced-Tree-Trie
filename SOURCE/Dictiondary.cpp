#include <iostream>
#include <fstream>
#include <string>
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

// Find the item in a trie
bool find(TrieNode *root, string key){
	if (isTrieEmpty(root))
		return false;
	TrieNode *pCrawl = root;

	cout << "Root" << endl;
	for (int i = 0; i < key.length(); i++){
		int index = key[i] - 'a';
		if (!pCrawl->children[index]){
			cout << "Fail." << endl;
			return false;
		}
		else
			cout << key[i] << endl;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl->isEndOfWord);
}


// Insert a new item into the trie
void insert(TrieNode *root, string key){
	TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++){
		int index = key[i] - 'a';       // xĂ¡c Ä‘á»‹nh vá»‹ trĂ­ cá»§a kĂ­ tá»±
		if (!pCrawl->children[index])   
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	pCrawl->isEndOfWord = true;
}

// Build a trie from given item 
TrieNode *buildTrie(string *key, int n){
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

// Show the trie built
void showTrie(TrieNode *root, int t){
    if(root->isEndOfWord == true)
        cout << "-------------\n";
    
    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(root->children[i]){
            cout << (char)(i + 97);
            if(t != -1)
                cout << " - " << char(t + 97) << endl;
            else
                cout << " - Root" << endl;
            showTrie(root->children[i], i);
        }
    }
}

// Read input in file
string * readInput(string filename, unsigned int &n){
    fstream f;
	string * key;
    f.open(filename, ios::in);
    f >> n;
    key = new string [n];
    for (int i = 0; i < n; i++)
        f >> key[i];
    f.close();
	return key;
}

// Menu
void menu(TrieNode *root){
	int enter;
	cout << "\n*** Welcome to Dictionary Program ***\n";
	
	cout << "\nAll funtion of my program are below: \n";
	cout << "1. Insert a word to Trie. " << endl;
	cout << "2. Looking up word." << endl;
    cout << "3. Show the Trie Built." << endl;
	cout << "4. Exit." << endl;
	
	cout << "Your Selection: "; 
	cin >> enter;
	
	if (enter == 1){
		string str;
		cout << "\nEnter the word you want to insert: ";
		cin >> str;
		insert(root,str);
		cout << "Done!" << endl;
		cout << "\nThanks for using my program !!!\n";
		cout << "--------------------------------------" << endl;
		menu(root);
	} 
	else if (enter == 2){
		string str;
		cout << "\nEnter the word you want to look up: ";
		cin >> str;
		if (find(root, str))
			cout << "Exist!" << endl;
		else	
			cout << "Doesn't exit!" << endl;	
		cout << "\n*** Thanks for using my program ***\n";
		cout << "--------------------------------------" << endl;
		menu(root);
	} 
	else if(enter == 3){
        showTrie(root, -1);
		cout << "\n*** Thanks for using my program ***\n";
		cout << "--------------------------------------" << endl << endl;
		menu(root);
	} 
	else if(enter == 4){
		cout << "\n*** Thanks for using my program ***\n";
		cout << "--------------------------------------" << endl;
	}
	else{
		string select;
		cout << "\nDo not have this function in my program!\n";
		cout <<  "\nDo you want to see menu and choose again?(yes or no): ";
		cin >> select;
		if(select == "yes"){
			cout << "--------------------------------------" << endl;
			menu(root);
		}
		else{
			cout << "\n*** Thanks for using my program ***\n";
			cout << "--------------------------------------" << endl;
		}
	}
}

int main(){
    unsigned int n;
    string *key = readInput("input.txt",n);

    TrieNode * root = buildTrie(key,n);

	menu(root);
    
    root = removeTrie(root); 
	return 0;
}