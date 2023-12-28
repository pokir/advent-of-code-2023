import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class Main {
  public static void main(String[] args) {
    String input = System.getenv("AOC_INPUT");

    String[] lines = input.split("\n");

    int totalPoints = 0;

    for (String line : lines) {
      String[] numbers = line.split(":")[1].split("\\|");

      List<String> winningNumbers =
          new LinkedList<>(Arrays.asList(numbers[0].trim().replaceAll(" +", " ").split(" ")));
      String[] yourNumbers = numbers[1].trim().replaceAll(" +", " ").split(" ");

      int points = 0;

      for (String number : yourNumbers) {
        if (winningNumbers.contains(number)) {
          if (points == 0) points = 1;
          else points *= 2;

          winningNumbers.remove(number);
        }
      }

      totalPoints += points;
    }

    System.out.println("Part one: " + totalPoints);
  }
}
