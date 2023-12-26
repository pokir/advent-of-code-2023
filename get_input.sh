SESSION=$1
START_DAY=$2
END_DAY=$3

mkdir inputs

for DAY in $(seq $START_DAY $END_DAY)
do
  curl "https://adventofcode.com/2023/day/$DAY/input" \
    -H "Cookie: session=$SESSION" \
    -o "inputs/day-$DAY.txt"
done
