#include "fasttext_go.h"

#include <cstring>
#include <sstream>

#include "fasttext.h"

using namespace fasttext;

FastTextGoPtr FastTextGoInit(const char* path)
{
    FastText* ft_ptr = new FastText();
    ft_ptr->loadModel(std::string(path));
    return static_cast<FastTextGoPtr>(ft_ptr);
}

void FastTextGoFree(void* ft)
{
    FastText* ft_ptr = reinterpret_cast<FastText*>(ft);
    delete ft_ptr;
}

FastTextScore* FastTextGoPredict(FastTextGoPtr ft, const char* word, int k, float threshold, std::size_t* p_pred_size)
{
    FastText* ft_ptr = reinterpret_cast<FastText*>(ft);
 
    std::istringstream in(word);

    std::vector<std::pair<real, std::string>> predictions;
    ft_ptr->predictLine(in, predictions, k, threshold);

    const auto pred_size = predictions.size();

    FastTextScore* scores = new FastTextScore[pred_size];

    for (size_t i = 0; i < pred_size; i++)
    {
        auto& prediction = predictions[i];

        const auto label_size = prediction.second.size();
        scores[i].label = new char[label_size + 1];
        memcpy(scores[i].label, prediction.second.c_str(), label_size + 1);
        scores[i].label[label_size] = 0;

        scores[i].score = prediction.first;
    }

    *p_pred_size = pred_size;

    return scores;
}

void FreeFastTextScores(FastTextScore* scores, size_t pairs_size)
{
    for (size_t i = 0; i < pairs_size; i++)
        delete scores[i].label;
    delete scores;
}
