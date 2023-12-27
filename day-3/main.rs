use std::{
    collections::{HashMap, HashSet},
    env,
};

fn main() {
    let input = env::var("AOC_INPUT").unwrap();

    let width = get_width(&input);
    let height = get_height(&input);

    let mut sum = 0;
    let mut gear_numbers = HashMap::<(usize, usize), Vec<u32>>::new();

    for y in 0..height {
        let mut current_number = "".to_owned();
        let mut current_number_is_adjacent_to_symbol = false;
        let mut gears_around_current_number = HashSet::new();

        for x in 0..width {
            let character = get_char_at(&input, x as isize, y as isize).unwrap();

            if character.is_ascii_digit() {
                current_number.push_str(&character.to_string());

                // check if there are symbols around it
                for j in 0..3 {
                    for i in 0..3 {
                        let offset_x = (x + j) as isize - 1;
                        let offset_y = (y + i) as isize - 1;
                        let character = get_char_at(&input, offset_x, offset_y).unwrap_or('.');

                        if character != '.' && !character.is_ascii_digit() {
                            current_number_is_adjacent_to_symbol = true;

                            if character == '*' {
                                gears_around_current_number
                                    .insert((offset_x as usize, offset_y as usize));
                            }
                        }
                    }
                }
            } else if !current_number.is_empty() {
                let number = current_number.parse::<u32>().unwrap();

                if current_number_is_adjacent_to_symbol {
                    sum += number;
                }

                for gear in &gears_around_current_number {
                    if !gear_numbers.contains_key(gear) {
                        gear_numbers.insert(*gear, vec![]);
                    }

                    gear_numbers.get_mut(gear).unwrap().push(number);
                }

                // reset
                current_number = "".to_owned();
                current_number_is_adjacent_to_symbol = false;
                gears_around_current_number.clear();
            }
        }

        // also add the number at the end of the line
        if !current_number.is_empty() {
            let number = current_number.parse::<u32>().unwrap();

            if current_number_is_adjacent_to_symbol {
                sum += number;
            }

            for gear in &gears_around_current_number {
                if !gear_numbers.contains_key(gear) {
                    gear_numbers.insert(*gear, vec![]);
                }

                gear_numbers.get_mut(gear).unwrap().push(number);
            }
        }
    }

    println!("Part one: {}", sum);

    let mut sum_of_gear_ratios = 0;

    for gear in gear_numbers {
        if gear.1.len() == 2 {
            sum_of_gear_ratios += gear.1[0] * gear.1[1];
        }
    }

    println!("Part two: {}", sum_of_gear_ratios);
}

fn get_width(input: &str) -> usize {
    input.lines().next().unwrap().len()
}

fn get_height(input: &str) -> usize {
    input.lines().collect::<Vec<&str>>().len()
}

fn get_char_at(input: &str, x: isize, y: isize) -> Option<char> {
    if x < 0 || y < 0 || x as usize >= get_width(input) || y as usize >= get_height(input) {
        None
    } else {
        Some(input.replace('\n', "").as_bytes()[y as usize * get_width(input) + x as usize] as char)
    }
}
