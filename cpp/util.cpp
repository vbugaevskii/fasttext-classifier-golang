#include <iostream>
#include "fasttext.h"

using namespace fasttext;

int main(int argc, char** argv)
{
    FastText fasttext;
    fasttext.loadModel(std::string(argv[1]));

    int k = 5;
    float threshold = 0.0;

    std::vector<std::pair<float, std::string>> predictions;

    while (fasttext.predictLine(std::cin, predictions, k, threshold))
    {
        for (const auto& prediction : predictions)
            std::cout << prediction.second << ' ' << prediction.first << ' ';
        std::cout << std::endl;
    }
}
