package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	file, err := os.Open("./input1.txt")
	if err != nil {
		panic(err)
	}
	defer func() {
		if err := file.Close(); err != nil {
			fmt.Println(err)
		}
	}()

	var lines [][]rune
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, []rune(scanner.Text()))
	}
	if err := scanner.Err(); err != nil {
		panic(err)
	}

	rows := len(lines)
	total := 0

	for i := range rows {
		cols := len(lines[i])
		for j := range cols {
			curr := lines[i][j]
			if curr != '@' {
				continue // skipping empty shit
			}

			adjacent := 0
			for di := -1; di <= 1; di++ {
				for dj := -1; dj <= 1; dj++ {
					if di == 0 && dj == 0 {
						continue
					}
					ni, nj := i+di, j+dj
					if ni >= 0 && ni < rows && nj >= 0 && nj < len(lines[ni]) {
						if lines[ni][nj] == '@' {
							adjacent++
						}
					}
				}
			}

			if adjacent < 4 {
				total++
			}
		}
	}

	fmt.Println(total)
}

