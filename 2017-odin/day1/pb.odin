package main

import "core:fmt"
import "core:os"
import "core:strings"

main :: proc() {
	number, err := os.read_entire_file("./input.txt", context.allocator)
	if err != nil {
		return
	}
	defer delete(number)

	it := strings.trim_space(string(number))
	step := len(it) / 2
	sum := 0

	for i := 0; i < len(it); i += 1 {
		check_index := i + step
		if (check_index >= len(it)) {
			check_index %= len(it)
		}

		if (int(it[i] - '0') == int(it[check_index] - '0')) {
			sum += int(it[i] - '0')
		}
	}

    fmt.printfln("%d", sum)
}
