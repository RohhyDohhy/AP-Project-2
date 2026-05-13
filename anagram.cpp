/*
* ========== Naming Convention Guideline ==========
* Classes, Structs & Enums: PascalCase
* Functions: camelCase
* Variables: lower_snake_case
* Constants: UPPER_SNAKE_CASE
* =================================================
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>


class Trie
{
public:
    Trie() { root = new Node; }

    ~Trie() { delete root; }

    void insert(const std::string& word);

    void findValidCombinations(std::multiset<char>& letters, std::vector<std::string>& valid_combinations)
    {
        std::string word;
        findValidCombinationsImpl(root, word, letters, valid_combinations);
    }



private:
    struct Node
    {
        std::map<char, Node*> children;
        bool is_end_of_word = false;

        ~Node()
        {
            for (auto& [letter, child]: children)
                delete child;
        }
    };

    Node* root;

    void findValidCombinationsImpl(Node* current, std::string& current_word, std::multiset<char>& letters, std::vector<std::string>& valid_combinations);

};

void Trie::insert(const std::string& word)
{
    Node* current = root;

    for (char letter: word)
    {
        if (current->children.find(letter) == current->children.end()) // Checks if current node has child node "letter"
            current->children[letter] = new Node;

        current = current->children[letter];
    }

    current->is_end_of_word = true;
}


void Trie::findValidCombinationsImpl(Node* current, std::string& current_word, std::multiset<char>& letters, std::vector<std::string>& valid_combinations) // Wrapper function
{
    if (current->is_end_of_word)
        valid_combinations.push_back(current_word);

    for (auto& [letter, child]: current->children)
    {
        auto it = letters.find(letter);
        if (it == letters.end())
            continue;
        
        current_word += letter; // Temporarily add letter to the end
        letters.erase(it);

        findValidCombinationsImpl(child, current_word, letters, valid_combinations);

        current_word.pop_back(); // Revert back to the original current_word
        letters.insert(letter);
    }
}

void readDictionary(Trie& dictionary)
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::string word;
        std::cin >> word;

        dictionary.insert(word);
    }
}

void readLetters(std::multiset<char>& letters)
{
    
    std::string line;
    getline(std::cin, line);
    std::stringstream ss{ line };

    char letter;
    while (ss >> letter)
        letters.insert(letter);
}


void processQuery(Trie& dictionary, std::vector<std::string>& valid_combinations)
{
    std::multiset<char> letters;
    readLetters(letters);

    dictionary.findValidCombinations(letters, valid_combinations);
}

void runGame()
{
    Trie dictionary;

    readDictionary(dictionary);

    int q;
    std::cin >> q;

    std::cin.ignore(1000, '\n'); // Clear leftover input in the buffer

    while (q--)
    {
        std::vector<std::string> valid_combinations;
        
        processQuery(dictionary, valid_combinations);

        std::sort(valid_combinations.begin(), valid_combinations.end());

        std::cout << valid_combinations.size() << std::endl;
        for (const std::string& valid_word: valid_combinations)
            std::cout << valid_word << std::endl;
    }
}

int main()
{
    runGame();
    return 0;
}