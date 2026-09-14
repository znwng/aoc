package main

import "core:fmt"
import "core:os"
import "core:strconv"
import "core:strings"

same_pattern :: proc(a, b: []int) -> bool {
	if len(a) != len(b) {
		return false
	}

	for i := 0; i < len(a); i += 1 {
		if a[i] != b[i] {
			return false
		}
	}

	return true
}

pattern_exists :: proc(patterns: [dynamic][dynamic]int, numbers: []int) -> bool {
	for pattern in patterns {
		if same_pattern(pattern[:], numbers) {
			return true
		}
	}

	return false
}

main :: proc() {
	data, err := os.read_entire_file("./input.txt", context.allocator)
	if err != nil {
		fmt.println(err)
		return
	}
	defer delete(data)

	numbers := [dynamic]int{}
	patterns := [dynamic][dynamic]int{}

	for token in strings.fields(string(data)) {
		value, err := strconv.parse_int(token)
		if err == false {
			continue
		}

		append(&numbers, value)
	}

	for {
		if pattern_exists(patterns, numbers[:]) {
			break
		}

		snapshot := make([dynamic]int, len(numbers))
		copy(snapshot[:], numbers[:])
		append(&patterns, snapshot)

		largest_index := 0

		for i := 1; i < len(numbers); i += 1 {
			if numbers[i] > numbers[largest_index] {
				largest_index = i
			}
		}

		blocks := numbers[largest_index]
		numbers[largest_index] = 0

		for blocks > 0 {
			largest_index += 1
			largest_index %= len(numbers)

			numbers[largest_index] += 1
			blocks -= 1
		}
	}

	fmt.printfln("Cycles: %d", len(patterns))
	fmt.printfln("Pattern: %w", numbers)
}
