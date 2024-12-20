// Anisha Hossain Megha (U43189731), team member: Alina Pineda Lopez (U79400432)
// HUFFMAN TREE SOURCE FILE

#include "HuffmanTree.hpp"
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <iostream>
#include <stack>

// this function compresses the input string - returns binary
std::string HuffmanTree::compress(const std::string inputStr){
    // need these maps to keep track of stuff
    std::map<char, size_t> charMap;
    std::map<char, size_t>::iterator it;

    // counts how many times each char shows up
    size_t count[256] = {0};
    for (size_t i = 0; i < inputStr.size(); i++) {
        count[(unsigned char)inputStr[i]]++;
    }

    // only add chars that actually appear in the string
    for(int i=0; i<256; i++){
        if(count[i] != 0){
            charMap.insert(std::pair<char, size_t>((char)i, count[i]));
        }
    }

    // make priority queue for huffman tree
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> PQ;

    // put all the nodes in the priority queue
    for(it = charMap.begin(); it != charMap.end(); ++it){
        HuffmanNode* node = new HuffmanNode(it->first, it->second);
        PQ.insert(node);
    }

    // build the tree - keep combining nodes until we only have one left
    while (PQ.size() != 1){
        HuffmanNode * node1 = PQ.min();  // get smallest
        PQ.removeMin();
        HuffmanNode* node2 = PQ.min();   // get next smallest
        PQ.removeMin();
        size_t frequencyT = (node1->getFrequency() + node2->getFrequency());
        // make new parent node and connect everything
        HuffmanNode* parentN1N2 = new HuffmanNode('\0', frequencyT, nullptr, node1, node2);
        node1->parent = parentN1N2;
        node2->parent = parentN1N2;
        PQ.insert(parentN1N2);
    }

    root = PQ.min();
    std::map<char, std::string> codeMap;
    std::string code = "";
    std::string output = "";

    // get the codes for each character - uses helper function
    for (it= charMap.begin(); it != charMap.end(); ++it){
        findCode(root, codeMap, code);
    }

    // finally, build the compressed string
    for(auto i: inputStr){
        output += codeMap[i];
    }

    return output;
}

// turns the tree into a string so we can save it
std::string HuffmanTree::serializeTree() const {
    if (root == nullptr) {
        return "";
    }
    std::string serializedTree;
    serialize(root, serializedTree);
    return serializedTree;
}

// takes the compressed string and tree string and gets back original text
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
    std::string output;
    std::stack<HuffmanNode*> treeStack;  // need stack to rebuild tree

    // rebuild the tree from the serialized string
    // L means leaf node (actual character)
    // B means branch node (internal node)
    for(size_t i = 0; i < serializedTree.length(); i++) {
        if(serializedTree[i] == 'L') {
            i++;  // skip the L to get to the actual character
            if(i < serializedTree.length()) {
                HuffmanNode* leaf = new HuffmanNode(serializedTree[i], 0);
                treeStack.push(leaf);
            }
        }
        else if(serializedTree[i] == 'B') {
            // need two nodes to make a branch
            if(treeStack.size() >= 2) {
                HuffmanNode* right = treeStack.top();
                treeStack.pop();
                HuffmanNode* left = treeStack.top();
                treeStack.pop();
                // connect them with a new parent
                HuffmanNode* branch = new HuffmanNode('\0', 0, nullptr, left, right);
                left->parent = branch;
                right->parent = branch;
                treeStack.push(branch);
            }
        }
    }

    if(treeStack.empty()) {
        return output;  // something went wrong
    }

    // now decode the actual message
    HuffmanNode* root = treeStack.top();
    HuffmanNode* current = root;

    // follow the 1s and 0s down the tree
    // 0 = go left, 1 = go right
    for(char bit : inputCode) {
        if(current == nullptr) {
            current = root;  // start over at root if we get lost
        }

        if(bit == '0') {
            current = current->left;
        } else if(bit == '1') {
            current = current->right;
        }

        // if we hit a leaf, we found a character
        if(current && current->isLeaf()) {
            output += current->getCharacter();
            current = root;  // start over for next character
        }
    }

    return output;
}
