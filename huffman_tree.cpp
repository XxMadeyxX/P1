#include "huffman_tree.h"


using namespace std;


/*
 Preconditions: file_name is the name of (and possibly path to) a text file
 Postconditions: Reads the contents of file_name and constructs a
 huffman tree based on the character frequencies of the file contents
 */
huffman_tree::huffman_tree(const string &file_name) {
    ifstream mainText(file_name); //takes in the text file
    char character; //character is whatever character you've landed on while iterating thorough the string.
    
    if (mainText.is_open()) {
        while (mainText.get(character)) {
            pair<char, int> dataPair(character, 1); // creates a data pair to reference throughout the code so it's easier to store the map values
            if (mainMap.count(character) > 0) {
                mainMap[character]++;
            }
            mainMap.emplace(dataPair);
        }
    }
    
    mainText.close(); //closes the file
    for (auto iterator = mainMap.begin(); iterator != mainMap.end(); iterator++) {  //iterates through the map automatically.
        mainVector.push_back(nodeFunction1((*iterator).second, (*iterator).first));
    }
    
    node* temp_1 = new node();
    node* temp_2 = new node();
    
    while (mainVector.size() > 1) {
        temp_1 = mainVector[0];
        mainVector.erase(mainVector.begin());
        temp_2 = mainVector[0];
        mainVector.erase(mainVector.begin());
        int total = temp_1 -> freq + temp_2 -> freq;
        node* parentNode = parent(total, temp_1, temp_2);
        if (mainVector.size() != 0)
        {
            for (auto it = mainVector.begin(); it != mainVector.end(); it++)
            {
                if ((*it) -> freq < parentNode -> freq)
                {
                    mainVector.insert(it, parentNode);
                    break;
                }
            }
        }
        else
        {
            mainVector.push_back(parentNode);
        }
        
    }
}

string huffman_tree::recurseEncode(node* currentNode, string str, char c) const {
    if (currentNode -> c != NULL)
    {
        if (currentNode -> c == c)
        {
            return str;
        }
        else
        {
            return "";
        }
    }
    else
    {
        string string_1 = recurseEncode(currentNode -> left, str + "0", c);
        string string_2 = recurseEncode(currentNode -> right, str + "1", c);
        if (string_1 == "" && string_2 == "")
        {
            return "";
        }
        else if (string_2 == "")
        {
            return string_1;
        }
        else
        {
            return string_2;
        }
    }
}

char huffman_tree::recurseDecode(node* currentNode, string str) const {
    if (currentNode -> c != NULL)
    {
        return currentNode -> c;
    }
    else
    {
        if (str[0] == '0')
        {
            return recurseDecode(currentNode -> left, str.substr(1, str.length()));
        }
        else if (str[0] == '1')
        {
            return recurseDecode(currentNode -> right, str.substr(1, str.length()));
        }
        else
        {
            return NULL;
        }
    }
}



huffman_tree::~huffman_tree() {
}



/*
 Preconditions: Character is a character with an ASCII value
 between 0 and 127 (inclusive).
 Postconditions: Returns the Huffman code for character if character is in the tree
 and an empty string otherwise.
 */
string huffman_tree::get_character_code(char character) const {
    if (mainVector.size() != 0)
    {
        return recurseEncode(mainVector[0], "", character);
    }
    else
    {
        return "";
    }
}



/*
 Preconditions: file_name is the name of (and possibly path to) a text file
 Postconditions: Returns the Huffman encoding for the contents of file_name
 if file name exists and an empty string otherwise.
 If the file contains letters not present in the huffman_tree,
 return an empty string
 */
string huffman_tree::encode(const string &file_name) const {
    ifstream mainText(file_name);
    if (!mainText)
    {
        return "";
    }
    char c;
    string str;
    if (mainText.is_open()) {
        while (mainText.get(c)) {
            string secretMessage;
            secretMessage = get_character_code(c);
            if (secretMessage != "")
            {
                str += get_character_code(c);
            }
            else
            {
                mainText.close();
                return "";
            }
        }
    }
    mainText.close(); //close the file
    return str;
}



/*
 Preconditions: string_to_decode is a string containing Huffman-encoded text
 Postconditions: Returns the plaintext represented by the string if the string
 is a valid Huffman encoding and an empty string otherwise
 */
string huffman_tree::decode(const string &string_to_decode) const {
    string secretMessage;
    unsigned int position = 0;
    if (mainVector.size() != 0)
    {
        while (position < string_to_decode.length())
        {
            char c = recurseDecode(mainVector[0], string_to_decode.substr(position, string_to_decode.length()));
            if (c == NULL)
            {
                return "";
            }
            else
            {
                secretMessage += c;
                position += get_character_code(c).length();
            }
        }
    }
    else
    {
        return "";
    }
    return secretMessage;
}
