def main():
    x, y = 0, 0
    facing = 0  # north=0, east=1, south=2, west=3

    result = []

    with open("input.txt", "r") as fin:
        for line in fin:
            values = line.strip().split(",")
            for value in values:
                result.append(value.strip())

    for instruction in result:
        turn = instruction[0]
        steps = int(instruction[1:])

        if turn == "R":
            facing = (facing + 1) % 4
        elif turn == "L":
            facing = (facing + 3) % 4
        else:
            raise ValueError(f"Invalid turn: {turn}")

        if facing == 0:
            y += steps
        elif facing == 1:
            x += steps
        elif facing == 2:
            y -= steps
        elif facing == 3:
            x -= steps

    distance = abs(x) + abs(y)
    print(distance)


if __name__ == "__main__":
    main()

