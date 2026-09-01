package main

import "core:fmt"
import "core:os"
import "core:strconv"
import "core:strings"

Point :: struct {
	x, y: int,
}

neighbors :: [8]Point{{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}}

main :: proc() {
	data, err := os.read_entire_file("./input.txt", context.allocator)
	if err != nil {
		return
	}
	defer delete(data)

	input, ok := strconv.parse_int(strings.trim_space(string(data)))
	if !ok {
		return
	}

	fmt.printfln("Number: %d", input)

	values := make(map[Point]int)

	position := Point{0, 0}
	values[position] = 1

	directions := [4]Point {
		{1, 0}, // right
		{0, 1}, // up
		{-1, 0}, // left
		{0, -1}, // down
	}

	direction := 0
	steps := 1

	for {
		for repeat := 0; repeat < 2; repeat += 1 {
			for step := 0; step < steps; step += 1 {

				// Move to the next position.
				position.x += directions[direction].x
				position.y += directions[direction].y

				sum := 0

				// Check all 8 neighboring cells.
				for offset in neighbors {
					neighbor := Point{position.x + offset.x, position.y + offset.y}

					if value, exists := values[neighbor]; exists {
						sum += value
					}
				}

				values[position] = sum

				if sum > input {
					fmt.printfln("Answer: %d", sum)
					return
				}
			}

			direction = (direction + 1) % 4
		}

		steps += 1
	}
}
