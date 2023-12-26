import { readFileSync } from 'fs';


function partOne() {
  let sum = 0;

  readFileSync('input.txt')
    .toString()
    .split('\n')
    .map(line => line.split(':')[1])
    .slice(0, -1)
    .map(line => line.split(';'))
    .map(line => line.map(hands => hands.split(',')))
    .forEach((line, index) => {
      let good = true;

      for (const hands of line) {
        for (const hand of hands) {
          const [ _,  number, color ] = hand.split(' ');
          if ((color === 'red' && number > 12)
            || (color === 'green' && number > 13)
            || (color === 'blue' && number > 14))
            good = false;
        }
      }

      if (good) sum += index + 1;
    });

  console.log(sum);
}


partOne();


