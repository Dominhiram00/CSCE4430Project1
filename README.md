CSCE 4430 Project 1
By Hiram Dominguez, Dan Bui, and Jack Follett


To use the lexer, please make sure that flex is istalled.

Next, compile the lexer by using the following commands:
	flex lexer.l
	gcc -o calc lexer.c parser.c -lfl

To test the lexer, please use the provided input.txt file.
To test it, run the following command:
	./calc < input.txt > output.txt

When oppening it, it should read:
- (Minus)
    * (Multiply)
        57(int)
        2(int)
    + (Add)
        3(int)
        4(int)
