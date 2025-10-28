# Project-3-Huffman-Trees
Gabrela Carbajal Ortiz
007715715
https://github.com/carbajalor-creator/Project-3-Huffman-Trees.git

COLLABORATION & SOURCES
For this project I used a lot of outside sources and websites such as geeksforgeeks to understand how to create tuple vectors, the priority queue, figuring out which instances it's better to use range based for loops instead of traditional for loops. I had a lot of errors throughout this project that I couldn't figure out how to fix so I used AI to clear some of them up or if I had trouble not understanding where my logic was wrong I used it to explain where I was going wrong.

IMPLEMENTATION DETAILS:
In the buildFromCounts function I merged the first two elements in the priority queue because it is a min heap. Once the parent node was made it was added to the tree with it's approriate word and frequency. For assigning codes functions I learned that it was more efficient to use emplace_back instead of push_back to output the word and code pairing and then I had a preorder traversal where I assigned zeros to left branches and ones to right branches. I reused the same code for writeHeaderPreorder for the preorder traversal. For the encode function I had to use multiple loops one to look for the word in the tokens vector, another to go through the codebook, and the last one to output the code from the word given. I had a variable charCount that kept count of the characters to make sure only 80 were output per line.

TESTING & STATUS
My project does not work correctly as far as I've tested it does build and run but it does not produce the output that is expected because I made mistakes early on that I didn't have time to fix in time to get the final product to work properly. Though some parts of my project do work correctly like the priority queue and the trees, the scanner doesn't work as it should.
