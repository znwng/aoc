def visit(x, y, visited):
    key = (x, y)

    if key in visited:
        return True

    visited.add(key)
    return False


def main():
    x, y = 0, 0
    facing = 0  # north=0, east=1, south=2, west=3

    result = []
    visited = {(0, 0)}

    with open("input.txt", "r") as fin:
        for line in fin:
            values = line.strip().split(",")
            for value in values:
                result.append(value.strip())

    first_repeat = None

    for instruction in result:
        turn = instruction[0]
        steps = int(instruction[1:])

        if turn == "R":
            facing = (facing + 1) % 4
        elif turn == "L":
            facing = (facing + 3) % 4
        else:
            raise ValueError(f"Invalid turn: {turn}")

        for _ in range(steps):
            if facing == 0:
                y += 1
            elif facing == 1:
                x += 1
            elif facing == 2:
                y -= 1
            elif facing == 3:
                x -= 1

            if first_repeat is None and visit(x, y, visited):
                first_repeat = (x, y)

    if first_repeat is not None:
        print(f"{first_repeat[0]},{first_repeat[1]}")
        print(abs(first_repeat[0]) + abs(first_repeat[1]))
    else:
        print("No repeated coordinate found")


if __name__ == "__main__":
    main()

