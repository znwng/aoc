package main

import "core:fmt"
import "core:os"
import "core:strconv"
import "core:strings"

max_element :: proc(values: ^[dynamic]int) -> int {
	largest := values[0]
	for i in values {
		if i > largest {
			largest = i
		}
	}

	return largest
}

min_element :: proc(values: ^[dynamic]int) -> int {
	smallest := values[0]
	for i in values {
		if i < smallest {
			smallest = i
		}
	}

	return smallest
}

main :: proc() {
	data, err := os.read_entire_file("./input.txt", context.allocator)
	if err != nil {
		return
	}
	defer delete(data)

	checksum := 0

	it := strings.trim_space(string(data))
	for line in strings.split_lines_iterator(&it) {
		fmt.println(line)

		numbers := [dynamic]int{}

		for token in strings.fields(line) {
			value, err := strconv.parse_int(token)
			if err == false {
				continue
			}
			append(&numbers, value)

		}
		largest := max_element(&numbers)
		smallest := min_element(&numbers)

		fmt.printfln("Largest: %d, Smallest: %d", largest, smallest)
		checksum += largest - smallest
	}

	fmt.printfln("%d", checksum)
}
