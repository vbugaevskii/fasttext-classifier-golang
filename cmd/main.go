package main

import (
    "os"
    "bufio"
    "fmt"
    "github.com/vbugaevskii/fasttext-classifier-go/pkg/fasttext"
)

func main() {
    model := fasttext.NewModel(os.Args[1])
    defer model.Free()

	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		predicts := model.Predict(scanner.Text() + "\n", 5, 0.0)

		for _, predict := range predicts {
			fmt.Printf("%s %.6f ", predict.Label, predict.Score)
		}
		fmt.Println()
	}
}
