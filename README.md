/******************************************************************************
* Project 3: Zap
* CS 15
* README
* Author: Daniel Jarka djarka01
******************************************************************************/

B. Program Purpose:

     Zap is a compression program used for compressing and decompressing text
     files using the Huffman coding algorithm. The client has no access to the
     underlying logic that compresses and decompresses text files, but they can
     run two commands from the terminal being "zap" for compression and "unzap"
     for decompression. The client will have to additionally specify the input
     file to read from and the output file to send the compressed or 
     decompressed text to.

C. Acknowledgements: 

    I used the following reference to read about pairs:
    https://cplusplus.com/reference/utility/pair/pair/

    This reference for priority queues:
    https://cplusplus.com/reference/queue/priority_queue/

    And this reference for using the peek function:
    https://cplusplus.com/reference/istream/istream/peek/

D. Files: 

     HuffmanCoder.cpp:
          Implementation of HuffmanCoder class. Used to compress and decompress
          text files using the huffman coding algorithm.

     HuffmanCoder.h:
          Interface of HuffmanCoder class

     main.cpp:
          Driver file which can be interacted with by the user to create an
          instance of HuffmanCoder.

     unit_test.h:
          A unit testing file for the HuffmanCoder functions. Because these
          functions are private, the unit_tests are commented out. They
          were made public for these tests, however.

     Makefile:
          File used to run the "make" command which compiles and builds
          the program.

     README: 
          This file.

     empty.txt:
          Input file used to test program behavior when opening an empty file.
     
     empty_nline.txt:
          Input file used to test program behavior when reading a file with a
          single new line character.

     single_char.txt:
          Input file used to test program behavior when reading a file that
          only contains a single character.

     all_conll_english.txt:
          Input file used to test program behavior for large input

     banana.txt:
          Input file used to test basic program behavior

     banana_apple.txt:
          Input file used to test basic program behavior

     ecoli.coli:
          Input file used to test program for large non .txt input

     hi.txt:
          Input file used to test basic program behavior

     sentences.txt:
          Input file used to test basic program behavior

     works_of_shakespeare.txt:
          Input file used to test program behavior for large input

E. Compile/run:

     - Compile using
            make
     - run executable with
            ./zap [zap | unzap] inputFile outputFile

F. Data Structure:

     The primary ADTs of this implementation are a List, a Priority Queue, 
     and a Binary Tree. To implement these ADTs, an array, std::vector, and
     huffman tree data structure was used respectively. 

     I used a standard array to store character frequencies and
     the binary encodings for those characters. I decided on using an array
     because we know that there are 256 total ASCII encodings. Because every
     character corresponds to an integer value from 0 - 255, this means that
     every index in the array is a one to one correspondance with the ASCII
     value of a character. There is no reason to add or remove elements from
     the array, so the important operations lie in accessing elements and
     manipulating their values. For a standard array, this occurs in constant
     time. An array of this form would also be useful for a problem to count
     how many characters do not appear in a text file, which uses an algorithm
     with very similar logic to counting frequencies. Additionally, this type
     of array would be useful for counting the traffic of the stores
     in a mall. Since the number of stores remains constant, an algorithm
     could count the people coming in/out of each store and save that
     information in an array.

     I used a std::vector data structure to create my priority queue, which in
     turn was used to assist in the process of building my huffman tree.
     The huffman coding algorithm finds the two character nodes with the
     smallest frequencies and joins them together with a parent node whose
     frequency is the sum of its children's frequencies. Then, the next two
     character nodes with the smallest frequencies (now including the parent)
     are joined together by a new parent. This continues until there are
     no more nodes to join together, leaving behind a huffman binary tree.
     The prioirity queue is useful for this problem because it is implemented
     as a min heap, where the top element is always the minimum value in
     the queue. This trvializes the issue of finding the smallest frequency
     character nodes and joining them with a parent node. A priority queue
     data structure can also be useful in an emergency room setting where
     patients need to kept track of by level of priority. Someone near death
     would be much higher on the queue than someone with a broken finger. 
     Additionally, a priority queue can also be used for a store that has
     different tiers of membership. "Gold" membership status receives higher
     priority on the queue than "Standard" membership status.

     I used a binary tree data structure to encode and decode text using the
     huffman coding algorithm. With a built tree, the path traversals to each
     leaf create the unique character encodings for each character contained
     in the tree. These traversals are also used to create a tree serialization
     which allows for a decoding algorithm to know what the huffman tree is
     supposed to look like after decoding. When decoding, after building a 
     huffman tree from a serialized string, the tree is then used to
     reconstruct the original text by traversing the tree according to the
     binary text (accessing the left child when reading "0" or a right child
     when reading "1" until a leaf node is reached). Binary trees have a lot
     of very useful implementations for other problems. They can be implemented
     as BSTs which are very useful for storing and finding sorted information.
     They can be used for dictionaries to quickly find the node containing
     that word and its corresponding definition. 

     The huffman coding algorithm is evidently the most important algorithm of
     this implementation. Its complexity under the hood is difficult to examine
     by simply looking at my implementation, so it's useful to discuss the
     process. First, a priority queue is populated with nodes that correspond
     to each character in the text. Next, the two smallest nodes are
     iteratively joined together with a parent node until only one (root) node
     remains. The time complexity of this algorithm is O(nlogn) where O(n)
     represents the number of nodes created and O(logn) represents the
     insertions into the priority queue. 

     Encoding characters is also quite important, where the huffman code for
     each character is generated recursively using the huffman tree. This tree
     is traveresed using a depth-first search, assigning 0 for left branches
     and 1 for right branches. These codes are then stored in a fixed-size
     array. The time complexity of generating binary code is O(n) where n is
     the number of leaves in the tree, and the complexity of converting an
     input into binary code is also O(n), where n is the size of the input.

G. Testing:

     1. unit_test
     
     I used the unit_test framework to test each of the individual functions
     used during my encoding and decoding processes. I unit_tested to test for
     functionality and edge cases, as I wanted to make sure that my functions 
     produced expected and necessary outputs for the rest of my implementation 
     to work as expected. I wrote getter functions for the private frequency
     and binary code arrays to unit_test the outputs for standard input and 
     single characters. For encoder, I tested building a tree using standard 
     input, using a single type of character, using the provided banana.txt 
     file, and using a single whitespace. I then tested the binary conversion 
     of a standard input, a single character type input, and a file input. I 
     also tested the serialization of a normal input and a single character 
     type input. For decoder, I tested the deserialization of a standard input,
     of a single leaf input, and an empty leaf input. I also checked that
     serializing after deserializing produced the original output. Finally,
     I tested decoding a binary string on a normal input and a single character
     type input, as well as printing this decoded text to ostream. 

     2. diff test

     I used several testing files I created to compare my program's edge and
     general case behavior with the reference implementation. I wrote some
     details of what each testing file specfically tests for above,
     but in general I checked cases for an empty file, a file with a single
     character, a file with a whitespace, and then some general behavior with
     the provided files. My actual method of testing this program was by 
     sending the program's "zap" outputs to stdout and diff testing these 
     outputs with the reference. I also sent "bad" inputs to stdout when the
     user enters a wrong command, the incorrect number of arguments, or when
     an input file that does not exist is named. Additionally, I sent the
     program's output to stdout when attempting to zap "bad_zap_file" and
     diff testing that output with the reference. To test "unzap" and decoding
     functionality, I diff tested my output files with the reference's output
     files. I did this two ways: using unzap on my own zapped file and using
     unzap on the reference's zapped file and then diff testing both types of
     output with the reference's unzapped files. 

H. Time Spent: 

     15
