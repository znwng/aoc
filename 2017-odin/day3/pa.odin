package main

import "core:fmt"
import "core:math"
import "core:os"
import "core:strconv"
import "core:strings"

find_ring_side :: proc(n: int) -> int {
	k := 1

	for k * k < n {
		k += 2
	}

	return k
}

main :: proc() {
	data, err := os.read_entire_file("./input.txt", context.allocator)
	if err != nil {
		return
	}
	defer delete(data)

	number, ok := strconv.parse_int(strings.trim_space(string(data)))
	if !ok {
		return
	}

	fmt.printfln("Number: %d", number)

	k := find_ring_side(number)
	fmt.printfln("k: %d", k)

	ring_distance := (k - 1) / 2
	fmt.printfln("Ring Distance: %d", ring_distance)

	midpoints := [4]int{}
	half_side := (k - 1) / 2

	for i := 0; i < 4; i += 1 {
		midpoints[i] = (k * k) - half_side - i * (k - 1)
	}

	fmt.println("Midpoints: ", midpoints)

	smallest := 999999999999999

	for i := 0; i < 4; i += 1 {
		distance := math.abs(midpoints[i] - number)

		if distance < smallest {
			smallest = distance
		}
	}

	fmt.printfln("Answer: %d", ring_distance + smallest)
}
