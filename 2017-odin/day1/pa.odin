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

	sum := 0

	for i := 0; i < len(it) - 1; i += 1 {
		if int(it[i] - '0') == int(it[i + 1] - '0') {
			sum += int(it[i] - '0')
		}
	}

	if int(it[len(it) - 1] - '0') == int(it[0] - '0') {
		sum += int(it[0] - '0')
	}

	fmt.printf("%d\n", sum)
}
