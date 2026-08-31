package main

import "core:fmt"
import "core:math"
import "core:os"
import "core:sort"
import "core:strconv"
import "core:strings"

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

		sort.quick_sort(numbers[:])

		for i := 0; i < len(numbers) - 1; i += 1 {
			for j := i + 1; j < len(numbers); j += 1 {
				if numbers[j] % numbers[i] == 0 {
					checksum += numbers[j] / numbers[i]
					break
				}
			}
		}
	}

	fmt.printfln("%d", checksum)
}
