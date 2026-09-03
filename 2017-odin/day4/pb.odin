package main

import "core:fmt"
import "core:os"
import "core:strings"

is_anagram :: proc(word1: string, word2: string) -> bool {
	if len(word1) != len(word2) {
		return false
	}

	counts: [256]int
	for c in word1 {
		counts[c] += 1
	}

	for c in word2 {
		counts[c] -= 1
		if counts[c] < 0 {
			return false
		}
	}

	return true
}

is_valid_passphrase_pb :: proc(line: string) -> bool {
	words := strings.fields(line)
	seen := make(map[string]struct{})
	defer delete_map(seen)

	for i := 0; i < len(words) - 1; i += 1 {
		for j := i + 1; j < len(words); j += 1 {
			if is_anagram(words[i], words[j]) {
				return false
			}
		}
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
		if is_valid_passphrase_pb(line) {
			count += 1
		}
	}

	fmt.println(count)
}
