package main

import "core:fmt"
import "core:os"
import "core:strings"

is_valid_passphrase :: proc(passphrase: string) -> bool {
	words := strings.fields(passphrase)
	seen := make(map[string]struct{})
	defer delete_map(seen)

	for word in words {
		if _, exists := seen[word]; exists {
			return false
		}

		seen[word] = {}
	}

	return true
}

main :: proc() {
	data, err := os.read_entire_file("./input.txt", context.allocator)
	if err != nil {
		return
	}
	defer delete(data)

	it := strings.trim_space(string(data))
	count := 0

	for line in strings.split_lines_iterator(&it) {
		if is_valid_passphrase(line) {
			count += 1
		}
	}

	fmt.printfln("%d", count)
}
