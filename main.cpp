#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include "Scanner.hpp"
#include "utils.hpp"
#include "bst.hpp"
#include "TreeNode.hpp"


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string dirName = std::string("input_output");
    const std::string inputFileName = std::string(argv[1]);
    const std::string inputFileBaseName = baseNameWithoutTxt(inputFileName);

    // build the path to the .tokens output file.
    const std::string wordTokensFileName = dirName + "/" + inputFileBaseName + ".tokens";


    // The next several if-statement make sure that the input file, the directory exist
    // and that the output file is writeable.
    if( error_type status; (status = regularFileExistsAndIsAvailable(inputFileName)) != NO_ERROR )
        exitOnError(status, inputFileName);


    if (error_type status; (status = directoryExists(dirName)) != NO_ERROR )
        exitOnError(status, dirName);

    if (error_type status; (status = canOpenForWriting(wordTokensFileName)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);


    std::vector<std::string> words;
    namespace fs = std::filesystem;
    fs::path tokensFilePath(wordTokensFileName); // create a file system path using the output file.

    auto fileToWords = Scanner(fs::path(inputFileName));
    if( error_type status; (status = fileToWords.tokenize(words)) != NO_ERROR)
        exitOnError(status, inputFileName);

    if (error_type status; (status = writeVectorToFile(wordTokensFileName, words)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    BinSearchTree bst;
    auto [tokenTuples, totalTokens] = bst.creatingVector(wordTokensFileName);
    auto priorityQueue = bst.insertPriorityQueue(tokenTuples);
    for (const auto& [word, freq] : tokenTuples) {
        for (int i = 0; i < freq; i++) {
            bst.insert(word);
        }
    }
    auto [minFreq, maxFreq] = bst.getMinMaxFreq();
    std::cout << "BST height: " << bst.height() << std::endl;
    std::cout << "BST unique words: " << bst.size() << std::endl;
    std::cout << "Total tokens: " << totalTokens << std::endl;
    std::cout << "Min frequency: " << minFreq << std::endl;
    std::cout << "Max frequency: " << maxFreq << std::endl;

    return 0;
}
