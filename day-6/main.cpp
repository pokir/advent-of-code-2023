#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

int getNumWaysToBeatRace(int time, int distanceToBeat) {
  return 0;
}

void partOne(std::string input) {
  // parse the numbers
  std::vector<int> times;
  std::vector<int> distances;

  std::string word;
  bool startedParsingDistance = false;

  for (char &c : input) {
    if (c == 'D') startedParsingDistance = true;

    if (c >= '0' && c <= '9') {
      word += c;
    } else {
      if (word.size() != 0) {
        int num = std::stoi(word, nullptr, 10);

        if (!startedParsingDistance) times.push_back(num);
        else distances.push_back(num);

        word = "";
      }
    }
  }

  int product = 1;

  for (int i = 0; i < times.size(); ++i) {
    // count the number of ways to win
    int waysToWin = 0;

    int raceTime = times.at(i);
    int distanceToBeat = distances.at(i);

    for (int chargingTime = 0; chargingTime < raceTime; ++chargingTime) {
      int speed = chargingTime;
      int distance = (raceTime - chargingTime) * speed;

      if (distance >= distanceToBeat) {
        ++waysToWin;
      }
    }

    product *= waysToWin;
  }

  std::cout << "Part one: " << product << std::endl;
}

void partTwo(std::string input) {
  // parse the single number
  long raceTime;
  long distanceToBeat;

  std::string word;

  for (char &c : input) {
    if (c >= '0' && c <= '9') {
      word += c;
    }

    if (c == 'D') {
      raceTime = std::stol(word, nullptr, 10);
      word = "";
    }
  }

  distanceToBeat = std::stol(word, nullptr, 10);

  // count the number of ways to win
  int waysToWin = 0;

  for (int chargingTime = 0; chargingTime < raceTime; ++chargingTime) {
    long speed = chargingTime;
    long distance = (raceTime - chargingTime) * speed;

    if (distance >= distanceToBeat) {
      ++waysToWin;
    }
  }

  std::cout << "Part two: " << waysToWin << std::endl;

}

int main() {
  std::string input = std::getenv("AOC_INPUT");

  partOne(input);
  partTwo(input);

  return 0;
}
