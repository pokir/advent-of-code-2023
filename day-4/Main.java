import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class Main {
  public static void main(String[] args) {
    String input = System.getenv("AOC_INPUT");

    String[] lines = input.split("\n");

    int totalPoints = 0;

    int[] cardInstances = new int[lines.length];
    Arrays.fill(cardInstances, 1);

    for (int i = 0; i < lines.length; ++i) {
      String line = lines[i];

      String[] numbers = line.split(":")[1].split("\\|");

      List<String> winningNumbers = new LinkedList<>(Arrays.asList(numbers[0].trim().split(" +")));
      String[] yourNumbers = numbers[1].trim().split(" +");

      int points = 0;
      int numMatches = 0;

      for (String number : yourNumbers) {
        if (winningNumbers.contains(number)) {
          if (points == 0) points = 1;
          else points *= 2;

          ++numMatches;

          winningNumbers.remove(number);
        }
      }

      totalPoints += points;

      for (int j = i + 1; j < Math.min(i + numMatches + 1, lines.length); ++j) {
        cardInstances[j] += cardInstances[i];
      }
    }

    System.out.println("Part one: " + totalPoints);
    System.out.println("Part two: " + Arrays.stream(cardInstances).sum());
  }
}
