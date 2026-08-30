def main():
    valid = 0

    with open("input.txt", "r") as fin:
        for line in fin:
            sides = []

            for n in line.split():
                sides.append(int(n))

            if len(sides) == 3:
                sides.sort()
                a, b, c = sides

                if a + b > c:
                    valid += 1

    print(valid)


if __name__ == "__main__":
    main()

