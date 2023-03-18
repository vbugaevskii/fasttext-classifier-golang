# fasttext-classifier-golang

## Overview

This is Go binding for [fastText](https://github.com/facebookresearch/fastText) library classifier.

## Requirements
- `git`;
- `make`;
- `cmake`;
- other [requirements](https://github.com/facebookresearch/fastText/#requirements) for fastText.

## Compiling
Clone the repository and build project:
```bash
git clone https://github.com/vbugaevskii/fasttext-classifier-golang/
cd fasttext-classifier-golang
make all
```
   
## Usage
Run the binary for classification:
```bash
cat <path_to_queries> | ./bin/fasttext_go <path_to_model>
```

You can use the library in your code, see the [`cmd/main.go`](cmd/main.go) example:
```go
model := fasttext.NewModel(path_to_model)
defer model.Free()   // don't forget to free model

predicts := model.Predict(text + "\n", 5, 0.0)
```

## Trouble shooting
You can get the error running previous command:
```
./bin/fasttext_go: error while loading shared libraries: libfasttext.so.0: cannot open shared object file: No such file or directory
```
This happens because this version still have dependency to libfasttext shared & static libraries.
You should put the libraries to `/usr/local/lib` or specify extra path to the library using env variable:
```
# you should specify absolute path here, not a relative one like below
LD_LIBRARY_PATH=./deps/fastText/build
```
