// Anisha Hossain Megha (U43189731), team member: Alina Pineda Lopez (U79400432)
// HUFFMAN TREE HEADER FILE
#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP

// header files
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>

// HuffmanTree class that inherits from HuffmanTreeBase
class HuffmanTree : public HuffmanTreeBase{
    private:
        // Root node of our Huffman tree
        HuffmanNode* root;

    public:
        // Required override functions from base class
        
        // Compresses input string into binary code
        // Returns: compressed binary string (1s and 0s)
        std::string compress(const std::string inputStr) override;

        // Creates a string representation of the tree structure
        // Returns: string with L (leaf) and B (branch) markers
        std::string serializeTree() const override;

        // Takes compressed code and tree structure to rebuild original string
        // Returns: original uncompressed string
        std::string decompress(const std::string inputCode, const std::string serializedTree) override;

        // Helper function to create mapping of characters to their binary codes
        void findCode(const HuffmanNode* node, std::map<char, std::string>& codeMap, std::string code){
            if(node == nullptr){
                return;
            }
            if(node->isLeaf()){
                codeMap[node->getCharacter()] = code;
                return;
            }
            // Recursively build codes: add '0' for left path, '1' for right path
            findCode(node->left, codeMap, code + "0");
            findCode(node->right, codeMap, code + "1");
        }

        // Helper function to create string representation of the tree
        void serialize(const HuffmanNode* node, std::string &outString) const{
            if(node == nullptr){
                return;
            }
            // Post-order traversal of the tree
            serialize(node->left, outString);
            serialize(node->right, outString);

            // Mark leaf nodes with 'L' followed by the character
            if(node->isLeaf()){
                outString = outString + "L" + node->getCharacter();
            }

            // Mark branch nodes with 'B'
            if(node->isBranch()){
                outString += "B";
            }
        }
};

#endif 

/*
 * - Tree serialization uses post-order traversal
 * - Binary codes: left = 0, right = 1
 */
