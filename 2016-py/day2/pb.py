def is_valid(x, y, pad):
    return 0 <= x < len(pad) and 0 <= y < len(pad[0]) and pad[x][y] is not None


def main():
    current = [2, 0]  # starts on 5

    pad = [
        [None, None, "1", None, None],
        [None, "2", "3", "4", None],
        ["5", "6", "7", "8", "9"],
        [None, "A", "B", "C", None],
        [None, None, "D", None, None],
    ]

    with open("input.txt", "r") as fin:
        for line in fin:
            line = line.strip()

            for char in line:
                new_x, new_y = current

                if char == "U":
                    new_x -= 1
                elif char == "D":
                    new_x += 1
                elif char == "L":
                    new_y -= 1
                elif char == "R":
                    new_y += 1

                if is_valid(new_x, new_y, pad):
                    current = [new_x, new_y]

            print(pad[current[0]][current[1]], end="")

    print()


if __name__ == "__main__":
    main()

