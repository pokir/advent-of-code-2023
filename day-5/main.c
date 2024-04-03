#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseInto(char *input, char **output, const unsigned int num, char *delimiters) {
  char **word;

  for (word = output; (*word = strsep(&input, delimiters)) != NULL;) {
    ++word;
    if (word >= &output[num]) break;
  }
}

void parseLines(char *input, char **lines, const unsigned int numLines) {
  parseInto(input, lines, numLines, "\n");
}

void parseWords(char *input, char **words, const unsigned int numWords) {
  parseInto(input, words, numWords, " \n");
}

unsigned long getMinimumLocationNumber(char **lines, int numSeeds, unsigned long *seeds) {
  unsigned long values[numSeeds];
  unsigned long newValues[numSeeds];

  for (int i = 0; i < numSeeds; ++i) {
    values[i] = seeds[i];
    newValues[i] = values[i];
  }

  for (int i = 1; lines[i] != NULL; ++i) {
    char *line = lines[i];
    char firstChar = line[0];

    // if a new mapping starts, set the old values to the new values
    if (firstChar >= 'a' && firstChar <= 'z') {
      for (int j = 0; j < numSeeds; ++j) values[j] = newValues[j];
    }

    // otherwise, do the mapping
    if (firstChar >= '0' && firstChar <= '9') {
      char *numStrings[3];
      parseWords(line, numStrings, 3);

      unsigned long nums[3];
      for (int j = 0; j < 3; ++j)
        nums[j] = strtoul(numStrings[j], NULL, 10);

      unsigned long destinationRangeStart = nums[0];
      unsigned long sourceRangeStart = nums[1];
      unsigned long rangeLength = nums[2];

      for (int j = 0; j < numSeeds; ++j) {
        // convert the range
        if (values[j] >= sourceRangeStart && values[j] < sourceRangeStart + rangeLength)
          newValues[j] = values[j] - sourceRangeStart + destinationRangeStart;
      }
    }
  }

  // set the final values
  for (int i = 0; i < numSeeds; ++i) values[i] = newValues[i];

  // find the minimum
  unsigned long min = values[0];
  for (int i = 1; i < numSeeds; ++i) {
    if (values[i] < min) min = values[i];
  }

  return min;
}

void partOne(char **lines) {
  int numSeeds = 20;

  // get the seeds line
  char *seedStrings[numSeeds + 1];
  parseWords(lines[0], seedStrings, 21);

  unsigned long seeds[numSeeds];
  for (int i = 0; i < numSeeds; ++i)
    seeds[i] = strtoul(seedStrings[i + 1], NULL, 10);

  unsigned long minLocationNumber = getMinimumLocationNumber(lines, numSeeds, seeds);

  printf("Part one: %lu\n", minLocationNumber);
}

void partTwo(char **lines) {
  int numSeedRanges = 10;

  // get the seeds lines
  char *words[numSeedRanges * 2 + 1];
  parseWords(lines[0], words, numSeedRanges * 2 + 1);

  unsigned long seedRanges[numSeedRanges * 2];
  for (int i = 0; i < numSeedRanges * 2; ++i)
    seedRanges[i] = strtoul(words[i + 1], NULL, 10);

  // only get the start of the ranges
  unsigned long seeds[numSeedRanges];
  for (int i = 0; i < numSeedRanges; ++i)
    seeds[i] = seedRanges[i * 2];

  unsigned long minLocationNumber = getMinimumLocationNumber(lines, numSeedRanges, seeds);

  printf("Part two: %lu\n", minLocationNumber);
}

int main() {
  char *input = getenv("AOC_INPUT");
  char input2[99999];
  strcpy(input2, input);

  // get the lines
  char *lines[9999];
  parseLines(input, lines, 9999);

  partOne(lines);

  // get the lines again
  parseLines(input2, lines, 9999);

  // TODO: bad logic for part two (not working)
  partTwo(lines);

  return 0;
}
