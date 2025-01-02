#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

/*
 *  HuffmanCoder.h
 *  Daniel Jarka
 *  11/11/24
 *
 *  CS 15 Project 3: Zap
 *
 *  HuffmanCoder is a class that represents a compression program that 
 *  compresses and decompresses a text file. These are the only functions of
 *  this program, the main logic of which are hidden from the client. This
 *  program reads from an input file and sends the resulting encoding/decoding
 *  to an output file. Encoding is accomplished using the huffman coding
 *  algorithm. This program additionally creates serialized text to represent
 *  the huffman tree used for encoding. HuffmanCoder uses constant size arrays
 *  to store character frequencies and binary encodings. This program decodes
 *  text by building a huffman tree from a serialized string and traversing
 *  this tree based on the binary encoding.
 * 
*/

#include <string>
#include "HuffmanTreeNode.h"
#include "ZapUtil.h"

class HuffmanCoder {

   public:
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);

   private:
    int freq_array[256] = {0};
    std::string binary_code_array[256] = {""};

    void count_frequency(std::istream &input);
    HuffmanTreeNode *build_tree();
    void generate_code(HuffmanTreeNode *root, std::string code);
    std::string encode(std::istream &input);
    std::string serialize_tree(HuffmanTreeNode *root);
    HuffmanTreeNode *deserialize_tree(const std::string &s);
    HuffmanTreeNode *deserialize_tree_helper(const std::string &s, int &index);
    std::string decode(HuffmanTreeNode *root, const std::string &b_code, 
                                                                    int &i);
    void printToFile(std::ostream &outFile, const std::string text);
    void delete_tree(HuffmanTreeNode *root);
    int *getFreqArray();
    std::string *getBinaryArray();
};

#endif