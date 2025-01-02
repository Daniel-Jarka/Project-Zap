/*
 *  unit_tests.h
 *  Daniel Jarka
 *  11/10/24
 *
 *  CS 15 Project 3 Zap
 *
 *  Uses Matt Russell's unit_test framework to 
 *  test the HuffmanCoder class.
 */
#include "HuffmanCoder.h"
#include "ZapUtil.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void dummy_test() {}

/*
void frequency_test() {
    HuffmanCoder coder;
    string input = "Bro is cool and mysterious \nand the best";
    std::istringstream iss(input);
    coder.count_frequency(iss);
    int *arr = coder.getFreqArray();
    for (int i = 0; i < 256; ++i) {
        if (arr[i] != 0) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
}

void frequency_single_char_test() {
    HuffmanCoder coder;
    string input = "                 ";
    std::istringstream iss(input);
    coder.count_frequency(iss);
    int *arr = coder.getFreqArray();
    for (int i = 0; i < 256; ++i) {
        if (arr[i] != 0) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
}

void build_tree_test() {
    HuffmanCoder coder;
    string input = "wwwhhtwwwwhhyy";
    std::istringstream iss(input);
    coder.count_frequency(iss);
    HuffmanTreeNode *root = coder.build_tree();
    printTree(root, '\0');
    coder.delete_tree(root);
}

void single_char_tree() {
    HuffmanCoder coder;
    string input = "wwwwwwww";
    std::istringstream iss(input);
    coder.count_frequency(iss);
    HuffmanTreeNode *root = coder.build_tree();
    printTree(root, '\0');
    coder.delete_tree(root);
}

void banana_test() {
    HuffmanCoder coder;
    std::ifstream infile("banana.txt");
    coder.count_frequency(infile);
    HuffmanTreeNode *root = coder.build_tree();
    printTree(root, '\0');
    coder.delete_tree(root);
}

void whitespace_test() {
    HuffmanCoder coder;
    string input = " ";
    std::istringstream iss(input);
    coder.count_frequency(iss);
    HuffmanTreeNode *root = coder.build_tree();
    printTree(root, '\0');
    coder.delete_tree(root);
}

void generate_code_test() {
    HuffmanCoder coder;
    HuffmanTreeNode *root = makeFigure1Tree('\0');
    coder.generate_code(root, "");
    std::string *arr = coder.getBinaryArray();
    for (int i = 0; i < 256; ++i) {
        if (arr[i] != "") {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
    coder.delete_tree(root);
}

void generate_single_code_test() {
    HuffmanCoder coder;
    HuffmanTreeNode *root = new HuffmanTreeNode('c', 3);
    coder.generate_code(root, "0");
    std::string *arr = coder.getBinaryArray();
    for (int i = 0; i < 256; ++i) {
        if (arr[i] != "") {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
    coder.delete_tree(root);
}

void binary_test() {
    HuffmanCoder coder;
    std::istringstream iss("abcdef");
    HuffmanTreeNode *root = makeFigure1Tree('\0');
    coder.generate_code(root, "");
    std::string s = coder.encode(iss);
    assert(s == "0000011011010011");
    coder.delete_tree(root);
}

void binary_single_char_test() {
    HuffmanCoder coder;
    std::istringstream iss("aaaaa");
    HuffmanTreeNode *root = makeFigure1Tree('\0');
    coder.generate_code(root, "");
    std::string s = coder.encode(iss);
    assert(s == "000000000000000");
    coder.delete_tree(root);
}

void binary_file_test() {
    HuffmanCoder coder;
    std::ifstream infile("banana.txt");
    coder.count_frequency(infile);
    infile.close();
    HuffmanTreeNode *root = coder.build_tree();
    coder.generate_code(root, "");
    infile.open("banana.txt");
    std::string s = coder.encode(infile);
    assert(s == "11001110100");
    coder.delete_tree(root);
}

void serial_test() {
    HuffmanCoder coder;
    HuffmanTreeNode *root = makeFigure1Tree('\0');
    std::string s = coder.serialize_tree(root);
    assert(s == "IIILaLbILeLfILcLd");
    coder.delete_tree(root);
}

void serial_single_test() {
    HuffmanCoder coder;
    HuffmanTreeNode *root = new HuffmanTreeNode('c', 3);
    std::string s = coder.serialize_tree(root);
    assert(s == "Lc");
    coder.delete_tree(root);
}

void deserial_test() {
    HuffmanCoder coder;
    string s = "IIILaLbILeLfILcLd";
    std::istringstream iss(s);
    HuffmanTreeNode *root1 = coder.deserialize_tree(s);
    HuffmanTreeNode *root2 = makeFigure1Tree('\0');
    assert(treeEquals(root1, root2, false, false));
    coder.delete_tree(root1);
    coder.delete_tree(root2);
}

void deserial_root_test() {
    HuffmanCoder coder;
    string s = "La";
    std::istringstream iss(s);
    HuffmanTreeNode *root1 = coder.deserialize_tree(s);
    printTree(root1, '\0');
    coder.delete_tree(root1);
}

void deserial_empty_test() {
    HuffmanCoder coder;
    string s = "I";
    std::istringstream iss(s);
    HuffmanTreeNode *root1 = coder.deserialize_tree(s);
    printTree(root1, '\0');
    coder.delete_tree(root1);
}

void deserial_and_serial_test() {
    HuffmanCoder coder;
    string s = "IIILaLbILeLfILcLd";
    std::istringstream iss(s);
    coder.count_frequency(iss);
    HuffmanTreeNode *root = coder.deserialize_tree(s);
    std::string ss = coder.serialize_tree(root);
    assert(s == ss);
    coder.delete_tree(root);
}

void decode_binary_test() {
    HuffmanCoder coder;
    HuffmanTreeNode *root = makeFigure1Tree('\0');
    int i = 0;
    std::string s = coder.decode(root, "10000011010", i);
    assert(s == "cafe");
    coder.delete_tree(root);
}

void decode_single_test() {
    HuffmanCoder coder;
    HuffmanTreeNode *root = makeFigure1Tree('\0');
    int i = 0;
    std::string s = coder.decode(root, "000000", i);
    assert(s == "aa");
    coder.delete_tree(root);
}

void print_test() {
    HuffmanCoder coder;
    HuffmanTreeNode *root = makeFigure1Tree('\0');
    int i = 0;
    std::string s = coder.decode(root, "10000011010", i);
    coder.printToFile(cout, s);
    coder.delete_tree(root);
}

*/
