###
### Makefile for Zap Project
###
### Author:  Daniel Jarka


CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

## This rule lets the program execute with ./zap
zap: main.o HuffmanCoder.o HuffmanTreeNode.o ZapUtil.o
	$(CXX) $(LDFLAGS) -o $@ $^

# This rule builds HuffmanCoder.o
HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h HuffmanTreeNode.h ZapUtil.h
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp

# This rule builds main.o
main.o: main.cpp HuffmanCoder.h ZapUtil.h
	$(CXX) $(CXXFLAGS) -c main.cpp


# The below rule will be used by unit_test.
unit_test: unit_test_driver.o HuffmanTreeNode.o HuffmanCoder.o ZapUtil.o 
	$(CXX) $(CXXFLAGS) $^
##
## Here is a special rule that removes all .o files besides the provided ones 
## (ZapUtil.o, HuffmanTreeNode.o, and BinaryIO.o), all temporary files 
## (ending with ~), and a.out produced by running unit_test. First, we find
## all .o files that are not provided files, then we run rm -f on each found
## file using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'HuffmanTreeNode.o' ! -name 'BinaryIO.o' \
		! -name 'ZapUtil.o' \) -exec rm -f {} \;
	@rm -f *~ a.out

