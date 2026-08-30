def clamp(value, minimum, maximum):
    return max(minimum, min(value, maximum))


def main():
    current = [1, 1]  # starts on 5

    pad = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9],
    ]

    with open("input.txt", "r") as fin:
        for line in fin:
            line = line.strip()

            for char in line:
                if char == "U":
                    current[0] = clamp(current[0] - 1, 0, len(pad) - 1)
                elif char == "D":
                    current[0] = clamp(current[0] + 1, 0, len(pad) - 1)
                elif char == "L":
                    current[1] = clamp(current[1] - 1, 0, len(pad[0]) - 1)
                elif char == "R":
                    current[1] = clamp(current[1] + 1, 0, len(pad[0]) - 1)

            print(pad[current[0]][current[1]])


if __name__ == "__main__":
    main()

