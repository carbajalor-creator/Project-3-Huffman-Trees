# Project-3-Huffman-Trees
Gabrela Carbajal Ortiz
007715715
https://github.com/carbajalor-creator/Project-3-Huffman-Trees.git

Collaboration & Sources: 
I used past labs to base my functoins and by TreeNode class off of and altered them to fit the needs of this project. I also used websites like geeksforgeeks to learn how to create a vector of tuples and the ways I can access elements in a tuple vector like get front and back. I had a lot of bugs that I couldn't figure out how to solve so I used AI to try to help I also used it to figure out what libraries I needed to include in my files.

Implementation Details: 
For part 2 of this project I implemented all of the methods in the BinSearchTree class along with adding 3 of my own functions. Most of the functions I saw were very similar to those we did in lab 6 except those took in an integer so I needed to change them to take in a tuple with a string and an integer. I added the function creatingVector that reads from the output file of Scanner.cpp and adds them to a temporary vector called tokenTuples where the tokens are stored in a tuple with their frequency count. It also keeps track of how many total tokens there are which is called later in main. The second function I created was insertPriorityQueue which takes in the tokenTuples vector but organizes them in descending order and in lexicographical order. The last function I created was getMinMaxFreq which uses the priorityQueue vector to get the maximum and minimum frequency. I also created a new class TreeNode to be able to work with the binary tree. 

Testing & Status: 
My functions seem to be working correctly I tested them with the TheBells.txt. My scanner is still not working correctly so it is affecting my output for part 2. I also encountered a segmentation fault when running my project which I have not been able to figure out how to fix yet.

