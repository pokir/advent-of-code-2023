package main

import (
	"fmt"
	"os"
	"slices"
	"strconv"
	"strings"
)

type line struct {
    hand string
    bid int
}

func getCardStrength(card rune, withJoker bool) int {
    var order []rune

    if withJoker {
        order = []rune{'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'}
    } else {
        order = []rune{'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'}
    }

    for i := 0; i < len(order); i++ {
        if order[i] == card {
            return i
        }
    }

    return -1
}

func getHandKindStrength(hand string, withJoker bool) int {
    // 0 for high card
    // 1 for one pair
    // 2 for two pair
    // 3 for three of a kind
    // 4 for full house
    // 5 for four of a kind
    // 6 for five of a kind

    if withJoker {
        nonJokerCards := []rune{'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'}

        for pos, card := range hand {
            if card == 'J' {
                // find the best card to replace the joker by
                maxStrength := 0

                for _, newCard := range nonJokerCards {
                    newHand := hand[:pos] + string(newCard) + hand[pos + 1:]
                    newStrength := getHandKindStrength(newHand, true)

                    if (newStrength > maxStrength) {
                        maxStrength = newStrength
                    }
                }

                return maxStrength
            }
        }
    }

    kindCounts := []int{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    for _, card := range hand {
        kindCounts[getCardStrength(card, withJoker)]++
    }

    slices.Sort(kindCounts)

    kindOrder := [][]int{
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, // high card
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2}, // one pair
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2}, // two pair
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3}, // three of a kind
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3}, // full house
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4}, // four of a kind
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5}, // five of a kind
    }

    for i := 0; i < len(kindOrder); i++ {
        if slices.Equal(kindCounts, kindOrder[i]) {
            return i
        }
    }

    return -1
}

func compareLinesWithoutJoker(line1 line, line2 line) int {
    cards1 := []rune(line1.hand)
    cards2 := []rune(line2.hand)

    strength1 := getHandKindStrength(line1.hand, false)
    strength2 := getHandKindStrength(line2.hand, false)

    if strength1 == strength2 {
        // compare each card in the hands from left to right
        for i := 0; i < len(line1.hand); i++ {
            cardStrength1 := getCardStrength(cards1[i], false)
            cardStrength2 := getCardStrength(cards2[i], false)

            if cardStrength1 != cardStrength2 {
                return cardStrength1 - cardStrength2
            }
        }
    }

    return strength1 - strength2
}

func compareLinesWithJoker(line1 line, line2 line) int {
    cards1 := []rune(line1.hand)
    cards2 := []rune(line2.hand)

    strength1 := getHandKindStrength(line1.hand, true)
    strength2 := getHandKindStrength(line2.hand, true)

    if strength1 == strength2 {
        // compare each card in the hands from left to right
        for i := 0; i < len(line1.hand); i++ {
            cardStrength1 := getCardStrength(cards1[i], true)
            cardStrength2 := getCardStrength(cards2[i], true)

            if cardStrength1 != cardStrength2 {
                return cardStrength1 - cardStrength2
            }
        }
    }

    return strength1 - strength2
}

func partOne(lines []line) {
    linesCopy := make([]line, len(lines))
    copy(linesCopy, lines)

    slices.SortFunc(linesCopy, compareLinesWithoutJoker)

    totalWinnings := 0

    for i := 0; i < len(linesCopy); i++ {
        totalWinnings += linesCopy[i].bid * (i + 1)
    }

    fmt.Println("Part one:", totalWinnings)
}

func partTwo(lines []line) {
    linesCopy := make([]line, len(lines))
    copy(linesCopy, lines)

    slices.SortFunc(linesCopy, compareLinesWithJoker)

    totalWinnings := 0

    for i := 0; i < len(linesCopy); i++ {
        totalWinnings += linesCopy[i].bid * (i + 1)
    }

    fmt.Println("Part two:", totalWinnings)
}

func main() {
    input := strings.TrimSuffix(os.Getenv("AOC_INPUT"), "\n")
    linesStrings := strings.Split(input, "\n")

    var lines = make([]line, len(linesStrings))

    for i := 0; i < len(linesStrings); i++ {
        splitLine := strings.SplitN(linesStrings[i], " ", 2)
        bid, _ := strconv.Atoi(splitLine[1])
        lines[i] = line{splitLine[0], bid}
    }

    partOne(lines)
    partTwo(lines)
}
