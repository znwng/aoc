package main

import "core:fmt"
import "core:os"
import "core:strconv"
import "core:strings"

same_pattern_b :: proc(a, b: []int) -> bool {
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

pattern_exists_b :: proc(patterns: [dynamic][dynamic]int, numbers: []int) -> (bool, int) {
	for pattern, i in patterns {
		if same_pattern_b(pattern[:], numbers) {
			return true, i
		}
	}

	return false, -1
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
	pattern_cycles := [dynamic]int{}

	for token in strings.fields(string(data)) {
		value, err := strconv.parse_int(token)
		if !err {
			continue
		}

		append(&numbers, value)
	}

	cycles := 0

	for {
		found, index := pattern_exists_b(patterns, numbers[:])

		if found {
			first_seen := pattern_cycles[index]
			fmt.printfln("%d", cycles - first_seen)
			break
		}

		snapshot := make([dynamic]int, len(numbers))
		copy(snapshot[:], numbers[:])

		append(&patterns, snapshot)
		append(&pattern_cycles, cycles)

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

		cycles += 1
	}
}
