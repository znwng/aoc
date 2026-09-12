package main

import "core:fmt"
import "core:os"
import "core:strconv"
import "core:strings"

main :: proc() {
	data, err := os.read_entire_file("./input.txt", context.allocator)
	if err != nil {
		return
	}
	defer delete(data)

	numbers := [dynamic]int{}

	it := strings.trim_space(string(data))
	for line in strings.split_lines_iterator(&it) {
		number, err := strconv.parse_int(line)
		if err == false {
			return
		}
		append(&numbers, number)
	}

	current := 0
	steps := 0
	for current < len(numbers) {
		jumps := numbers[current]
		if jumps >= 3 {
			numbers[current] -= 1
		} else {
			numbers[current] += 1
		}
		current += jumps

		steps += 1
	}

	fmt.println(steps)
}
