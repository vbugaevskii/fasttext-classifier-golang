#include "fasttext/fasttext_go.h"

#include <iostream>

int main(int argc, char** argv)
{
	auto fasttext = FastTextGoInit(argv[1]);

    int k = 5;
    float threshold = 0.0;

	std::string line;

	while (std::getline(std::cin, line))
	{
        size_t predictions_size = 0;

		line += '\n';

        auto predictions = FastTextGoPredict(
	    	fasttext,
            const_cast<char*>(line.c_str()),
		    k,
    		threshold,
            &predictions_size
    	);

        for (std::size_t i = 0; i < predictions_size; i++)
            std::cout << predictions[i].label << ' ' << predictions[i].score << ' ';
        std::cout << std::endl;

        FreeFastTextScores(predictions, predictions_size);
    }

    FastTextGoFree(fasttext);
}
