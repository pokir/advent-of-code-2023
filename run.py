import json
import os
import sys


def get_day():
    if len(sys.argv) < 2:
        print('Please provide the date (1 to 24)')
    elif not sys.argv[1].isnumeric():
        print('The date entered is not a positive integer')
    elif not 1 <= int(sys.argv[1]) <= 24:
        print('The date entered is not in the valid range (1 to 24)')
    else:
        return int(sys.argv[1])


day = get_day()

if day is None:
    exit()

with open(f'day-{day}/run.json', 'r') as f:
    command = json.load(f)['run']

if not os.path.isfile(f'inputs/day-{day}.txt'):
    print('The input file does not exist')
    exit()

os.system(f'cd day-{day} && AOC_INPUT=$(cat ../inputs/day-{day}.txt) {command}')
