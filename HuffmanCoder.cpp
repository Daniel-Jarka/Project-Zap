/*
 *  HuffmanCoder.cpp
 *  Daniel Jarka
 *  11/11/24
 *
 *  CS 15 Project 3: Zap
 *
 *  This file contains the implementation of the
 *  HuffmanCoder class.
*/
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <istream>
#include <iostream>
#include <fstream>
#include <queue>
#include <utility>

#include "HuffmanCoder.h"

using namespace std;

/*
 * name:      encoder
 * purpose:   reduces the number of bits used to store text in a file.
 * arguments: a string that represents an input file name and a string that
 *            represents an output file name.
 * returns:   none
 * effects:   encodes a file into binary text, reducing the memory required
 *            to store text.
 */
void HuffmanCoder::encoder(const std::string &inputFile, 
const std::string &outputFile) {
    std::ifstream infile(inputFile);
    if (infile.fail()) {
        throw runtime_error("Unable to open file " + inputFile);
    }
    int c = infile.peek();
    if(c == EOF) {
        cout << inputFile << " is empty and cannot be compressed." << endl;
    }
    else {
        count_frequency(infile);
        infile.close();
        HuffmanTreeNode *root = build_tree();
        if (root->is_leaf()) {
            generate_code(root, "0");
        }
        else {
            generate_code(root, "");
        }
        infile.open(inputFile);
        std::string binary_code = encode(infile);
        infile.close();
        std::string serialized_tree = serialize_tree(root);
        writeZapFile(outputFile, serialized_tree, binary_code);
        cout << "Success! Encoded given text using " << binary_code.size() 
             << " bits." << endl;
        delete_tree(root);
    }
}

/*
 * name:      decoder
 * purpose:   decodes a binary text file to produce the original text file
 * arguments: a string that represents an input file name and a string that
 *            represents an output file name.
 * returns:   none
 * effects:   creates a file with the decoded text.
 */
void HuffmanCoder::decoder(const std::string &inputFile, 
const std::string &outputFile) {
    pair<std::string, std::string> info = readZapFile(inputFile);
    HuffmanTreeNode *root = deserialize_tree(info.first);
    int i = 0;
    std::string decoded_text = decode(root, info.second, i);
    std::ofstream outfile(outputFile);
    if (outfile.fail()) {
        throw runtime_error("Unable to open file " + outputFile);
    }
    printToFile(outfile, decoded_text);
    outfile.close();
    delete_tree(root);
    return;
}

/*
 * name:      count_frequency
 * purpose:   counts the frequency of each character in a text file
 * arguments: an istream object that is used to read inputs.
 * returns:   none
 * effects:   stores character frequencies in an array of size 256.
 */
void HuffmanCoder::count_frequency(std::istream &input) {
    char curr_char;
    while (input.get(curr_char)) {
        freq_array[int(curr_char)] += 1;
    }
}

/*
 * name:      build_tree
 * purpose:   creates a huffman tree that will be used to create binary
 *            encodings. 
 * arguments: none
 * returns:   pointer to the root of the huffman tree
 * effects:   builds a huffman tree
 */
HuffmanTreeNode* HuffmanCoder::build_tree() {
priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>,
                NodeComparator> pq;
    for (int i = 0; i < 256; ++i) {
        if (freq_array[i] != 0) {
            HuffmanTreeNode *new_node = 
                                new HuffmanTreeNode(char(i), freq_array[i]);
            pq.push(new_node);
        }
    }

    while (pq.size() > 1) {
        HuffmanTreeNode *min1 = pq.top();
        pq.pop();
        HuffmanTreeNode *min2 = pq.top();
        pq.pop();
        HuffmanTreeNode *parent = new HuffmanTreeNode('\0', 
                            min1->get_freq() + min2->get_freq(), min1, min2);
        pq.push(parent);
    }
    HuffmanTreeNode *root = pq.top();
    return root;
}

/*
 * name:      generate_code
 * purpose:   creates binary encodings for each leaf in the huffman tree.
 * arguments: pointer to the root of a huffman tree and a string that will
 *            update recursively to store binary encodings.
 * returns:   none
 * effects:   stores binary encodings of each character in huffman tree in a
 *            new array of size 256.
 */
void HuffmanCoder::generate_code(HuffmanTreeNode *root, std::string code) {
    if (root == nullptr) {
        return;
    }
    if (root->is_leaf()) {
        binary_code_array[int(root->get_val())] = code;
        return;
    }
    generate_code(root->get_left(), code + "0");
    generate_code(root->get_right(), code + "1");
}

/*
 * name:      encode
 * purpose:   converts input text into binary encoding
 * arguments: istream object that represents input to read from
 * returns:   a string that contains the binary encoding of the file or input
 * effects:   none
 */
std::string HuffmanCoder::encode(std::istream &input) {
    char curr_char;
    std::string result;
    while (input.get(curr_char)) {
        result += binary_code_array[int(curr_char)];
    }
    return result; 
}

/*
 * name:      serialize_tree
 * purpose:   creates a serialization of the huffman tree used for decoding by
 *            another user
 * arguments: a pointer to the root of the huffman tree
 * returns:   a string that represents the serialization of the huffman tree
 * effects:   none
 */
std::string HuffmanCoder::serialize_tree(HuffmanTreeNode *root) {
    if (root == nullptr) {
        return "";
    }
    if (root->is_leaf()) {
        std::string s = "L";
        s += root->get_val();
        return s;
    }
    return "I" + serialize_tree(root->get_left()) + 
                    serialize_tree(root->get_right());
}

/*
 * name:      deserialize_tree
 * purpose:   converts a serialized string into a huffman tree
 * arguments: a string that represents a huffman tree serialization
 * returns:   pointer to the root of the deserialized huffman tree
 * effects:   builds a huffman tree
 */
HuffmanTreeNode* HuffmanCoder::deserialize_tree(const std::string &s) {
    int index = 0;
    return deserialize_tree_helper(s, index);

}


/*
 * name:      deserialize_tree_helper
 * purpose:   helper function to convert a serialized string into a huffman 
 *            tree
 * arguments: a string that represents a huffman tree serialization and an
 *            integer pointer that represents a universal index to keep track
 *            each character to read
 * returns:   pointer to the root of the deserialized huffman tree
 * effects:   builds a huffman tree
 */
HuffmanTreeNode* HuffmanCoder::deserialize_tree_helper(const std::string &s, 
                                                                int &index){
    if (index >= int(s.length())) {
        return nullptr;
    }
    if (s[index] == 'L') {
        char leaf = s[++index];
        ++index;
        HuffmanTreeNode *new_node = new HuffmanTreeNode
        (leaf, freq_array[int(leaf)], nullptr, nullptr);
        return new_node;
    }
    if (s[index] == 'I') {
        ++index;
        HuffmanTreeNode *new_node = new HuffmanTreeNode
        (deserialize_tree_helper(s, index), deserialize_tree_helper(s, index));
        return new_node;
    }

    return nullptr;

}

/*
 * name:      decode
 * purpose:   decodes binary text using a huffman tree to produce the original
 *            text file.
 * arguments: a pointer to the root of a huffman tree, a string that represents
 *            the binary text to decode, and an integer pointer that represents
 *            a universal index to keep track of which character is read.
 * returns:   a string that represents the content of the original text file.
 * effects:   none
 */
std::string HuffmanCoder::decode(HuffmanTreeNode *root, 
                                    const std::string &b_code, int &i) {
    std::string result = "";
    if (root->is_leaf()) {
        for (i = 0; i < int(b_code.size()); ++i) {
            result += root->get_val();
        }
    }
    while (i < int(b_code.length())) {
        HuffmanTreeNode *current = root;

        while (not current->is_leaf()) {
            if (i >= int(b_code.length())) {
                throw runtime_error("Encoding did not match Huffman tree.");
            }
            if (b_code[i] == '0') {
                current = current->get_left();
            }
            else if (b_code[i] == '1') {
                current = current->get_right();
            }
            ++i;
        }

        result += current->get_val();
    }

    return result;
}

/*
 * name:      printToFile
 * purpose:   prints text to a file
 * arguments: a string that represents the name of the output file and a string
 *            that represents the text to send to the file.
 * returns:   none
 * effects:   none
 */
void HuffmanCoder::printToFile(std::ostream &outFile, const std::string text) {
    outFile << text;
    return;
}

/*
 * name:      delete_tree
 * purpose:   frees the heap allocated memory of the huffman tree
 * arguments: a pointer to the root of a huffman tree
 * returns:   none
 * effects:   deletes the huffman trees and frees the dynamically allocated
 *            memory of the tree.
 */
void HuffmanCoder::delete_tree(HuffmanTreeNode *root) {
    if (root == nullptr) {
        return;
    }

    delete_tree(root->get_left());
    delete_tree(root->get_right());

    delete root;
}

/*
 * name:      getFreqArray
 * purpose:   getter function used for testing
 * arguments: none
 * returns:   the character frequency array
 * effects:   none
 */
int* HuffmanCoder::getFreqArray() {
    return freq_array;
}

/*
 * name:      getBinaryArray
 * purpose:   getter function used for testing
 * arguments: none
 * returns:   the array containing the binary encoding for each character
 * effects:   none
 */
std::string* HuffmanCoder::getBinaryArray() {
    return binary_code_array;
}

