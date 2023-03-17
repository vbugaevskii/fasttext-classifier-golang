package fasttext

/*
#cgo CXXFLAGS: -std=c++11 -march=native -g -I${SRCDIR}/../../deps/fastText/src/ -I.
#cgo LDFLAGS: -L${SRCDIR}/../../deps/fastText/build/ -lfasttext
#include "fasttext_go.h"
#include <stdlib.h>
*/
import "C"
import (
    "unsafe"
)

type FastTextScore struct {
    Label   string
    Score   float32
}

type FastText struct {
    ft C.FastTextGoPtr
}

func NewModel(path string) *FastText {
    pathChar := C.CString(path)
    defer C.free(unsafe.Pointer(pathChar))

    return &FastText{
        ft: C.FastTextGoInit(pathChar),
    }
}

func (m *FastText) Free() {
    C.FastTextGoFree(m.ft)
}

func (m *FastText) Predict(word string, k int, threshold float32) []FastTextScore {
    wordChar := C.CString(word)
    defer C.free(unsafe.Pointer(wordChar))

    var cScoresLen C.ulong
    var cScores *C.FastTextScore = C.FastTextGoPredict(
        m.ft,
        wordChar,
        C.int(k),
        C.float(threshold),
        &cScoresLen,
    )
    defer C.FreeFastTextScores(cScores, cScoresLen)

    scoresLen := int(cScoresLen)

    // https://stackoverflow.com/questions/48756732/what-does-1-30c-yourtype-do-exactly-in-cgo/48756785#48756785
    scoresSlice := (*[1 << 28]C.FastTextScore)(unsafe.Pointer(cScores))[:scoresLen:scoresLen]
    return castScoresToGo(scoresSlice)
}

func castScoresToGo(scoresSlice []C.FastTextScore) []FastTextScore {
    scores := []FastTextScore{}

    for _, cstruct := range scoresSlice {
        r := FastTextScore{
            Label: C.GoString(cstruct.label),
            Score: float32(cstruct.score),
        }
        scores = append(scores, r)
    }

    return scores
}
