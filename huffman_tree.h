#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <map>

#pragma once

using namespace std;

class huffman_tree {
public:
    
    struct node {
        int freq;
        char c;
        struct node *left, *right;
    };
    
    map<char, int> mainMap;
    vector<node*> mainVector;
    
    node* nodeFunction1(int frequency, char character) {
        node* newNode = new node();
        newNode -> freq = frequency;
        newNode -> c = character;
        return newNode;
    }
    node* parent(int sum, node* temp_1, node* temp_2) {
        node* newNode2 = new node();
        newNode2 -> freq = sum;
        newNode2 -> right = temp_1;
        newNode2 -> left = temp_2;
        return newNode2;
    }
    
    string recurseEncode(node* currentNode, string s, char c) const;
    char recurseDecode(node* currentNode, string s) const;
    
    huffman_tree(const string &file_name);
    ~huffman_tree();
    
    string get_character_code(char character) const;
    string encode(const string &file_name) const;
    string decode(const string &string_to_decode) const;
};


