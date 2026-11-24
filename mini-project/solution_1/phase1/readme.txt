
Given a text file as input, generate an index

Phase 1:
Todo:
0. pass the filename as argument on the command line
   int main(int argc, char* argv[]) ...
   argv[1] will be the filename
1. read the text file line by line 
2. break the line into words - remove all separators 
3. make the words case insensitive - convert to lowercase
4. store these words in a trie - let the trie have 26 pointers in each node
5. store the frequency of each word.
6. display words with frequency
7. there shall be no input and no other output.

additional :
8. remove commonly occurring words

example:
input1.txt:

Betty Botter bought some butter
but the butter was bitter
Betty Botter bought some better butter
to make the bitter butter better

output: (should exactly match)
word : better count : 2
word : betty count : 2
word : bitter count : 2
word : botter count : 2
word : bought count : 2
word : but count : 1
word : butter count : 4
word : make count : 1
word : some count : 2
word : the count : 2
word : to count : 1
word : was count : 1