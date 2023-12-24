with open('input.txt', 'r') as f:
    lines = f.readlines()


def part_one():
    total = 0

    for line in lines:
        for c in line:
            if c.isnumeric():
                total += int(c) * 10
                break

        for c in line[::-1]:
            if c.isnumeric():
                total += int(c)
                break

    print(f'Part 1: {total}')


def part_two():
    total = 0

    nums_as_strings = ['one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']

    for line in lines:
        for i in range(len(line)):
            if line[i].isnumeric():
                total += int(line[i]) * 10
                break
            else:
                done = False

                for num in nums_as_strings:
                    if line[i:].startswith(num):
                        total += (nums_as_strings.index(num) + 1) * 10
                        done = True
                        break

                if done: break

        for i in range(len(line)):
            if line[-i - 1].isnumeric():
                total += int(line[-i - 1])
                break
            else:
                done = False

                for num in nums_as_strings:
                    if line[:len(line) - i].endswith(num):
                        total += nums_as_strings.index(num) + 1
                        done = True
                        break

                if done: break

    print(f'Part 2: {total}')


part_one()
part_two()
