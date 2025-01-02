/*
 *  main.cpp
 *  Daniel Jarka
 *  11/11/24
 *
 *  CS 15 Project 3 Zap
 * 
 *  This file contains the driver that allows the user to create an instance
 *  of a HuffmanCoder and run it. To use the HuffmanCoder, the client must
 *  enter either "zap" or "unzap" to encode or decode respectively. If an
 *  incorrect command or number of arguments is entered, the program will print
 *  to cerr the correct usage of the ./zap program. 
 * 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "HuffmanCoder.h"

using namespace std;

int main(int argc, char *argv[])
{
    HuffmanCoder coder;
    std::string command = argv[1];
    if (command == "zap" and argc == 4) {
        coder.encoder(argv[2], argv[3]);
    }
    else if (command == "unzap" and argc == 4) {
        coder.decoder(argv[2], argv[3]);
    }
    else {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
        return EXIT_FAILURE;
    }
    
    return 0;
}
