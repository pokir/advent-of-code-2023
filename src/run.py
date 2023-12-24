import json
import os
import sys


def get_day():
    if len(sys.argv) < 2:
        print("Please provide the date (1 to 24)")
    elif not sys.argv[1].isnumeric():
        print("The date entered is not a positive integer")
    elif not 1 <= int(sys.argv[1]) <= 24:
        print("The date entered is not in the valid range (1 to 24)")
    else:
        return int(sys.argv[1])


day = get_day()

if day is None:
    exit()

day_folder = f'day-{day}'

with open(f'{day_folder}/run.json', 'r') as f:
    command = json.load(f)['run']

os.system(f'cd {day_folder} && {command}')
