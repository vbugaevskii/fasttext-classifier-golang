#pragma once

#ifndef GO_FASTTEXT_H
#define GO_FASTTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

typedef struct {
    char* label;
    float score;
} FastTextScore;

typedef void* FastTextGoPtr;

FastTextGoPtr FastTextGoInit(const char* path);
void FastTextGoFree(FastTextGoPtr model);

FastTextScore* FastTextGoPredict(
    FastTextGoPtr model,
    const char* word,
    int k,
    float threshold,
    size_t* p_pred_size
);

void FreeFastTextScores(FastTextScore* scores, size_t scores_size);

#ifdef __cplusplus
}
#endif

#endif
