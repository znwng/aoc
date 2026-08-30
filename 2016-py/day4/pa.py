from collections import Counter
import re


def main():
    total = 0

    with open("input.txt") as f:
        for line in f:
            line = line.strip()

            # Extract name, sector ID, and checksum
            m = re.match(r"([a-z-]+)-(\d+)\[([a-z]+)\]", line)

            name = m.group(1)
            sector = int(m.group(2))
            checksum = m.group(3)

            # Count letters only
            freq = Counter(c for c in name if c.isalpha())

            # Sort by frequency, then alphabetically
            ordered = sorted(freq.items(), key=lambda x: (-x[1], x[0]))

            # Build the computed checksum
            computed = "".join(char for char, _ in ordered[:5])

            if computed == checksum:
                total += sector

    print(total)


if __name__ == "__main__":
    main()

