def is_valid(a, b, c):
    return a + b > c and a + c > b and b + c > a


def main():
    triangles = []

    with open("input.txt", "r") as fin:
        for line in fin:
            triangles.append(list(map(int, line.split())))

    count = 0
    for i in range(0, len(triangles), 3):
        for triangle in zip(*triangles[i : i + 3]):
            if is_valid(*triangle):
                count += 1

    print(count)


if __name__ == "__main__":
    main()

