const games = process.env.AOC_INPUT
  .trim()
  .split('\n')
  .map(line => line.split(':')[1])
  .map(line => line.split(';'))
  .map(line => line.map(hand => hand.split(',')))
  .map(line => line.map(hand => hand.map(string => {
    const [ _, number, color ] = string.split(' ');
    return [Number.parseInt(number), color];
  })));


function partOne() {
  let sum = 0;

  games.forEach((game, index) => {
    let good = true;

    game.forEach(hand => {
      hand.forEach(([ number, color ]) => {
        if ((color === 'red' && number > 12)
          || (color === 'green' && number > 13)
          || (color === 'blue' && number > 14))
          good = false;
      });
    });

    if (good) sum += index + 1;
  });

  console.log('Part one:', sum);
}


function partTwo() {
  let sumOfPowers = 0;

  games.forEach(game => {
    const maxes = {red: 0, blue: 0, green: 0};

    game.forEach(hand => {
      hand.forEach(([ number, color ]) => {
        if (number > maxes[color])
          maxes[color] = number;
      });
    });

    sumOfPowers += maxes.red * maxes.blue * maxes.green;
  });

  console.log('Part two:', sumOfPowers);
}


partOne();
partTwo();
