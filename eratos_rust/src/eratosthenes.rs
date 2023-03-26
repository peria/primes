mod eratosthenes0;
mod eratosthenes1;

pub trait Eratosthenes {
    // Finds prime numbers in range [0, x).
    fn generate(&mut self, x: usize);

    // Finds prime numbers in range [x, y).
    fn generate_range(&mut self, x: usize, y: usize);

    // Returns the number of counted prime numbers.
    fn count(&self) -> i64;

    // Return the implemented version.
    fn version(&self) -> i32;
}

pub fn get_eratosthenes(version: i32) -> Box<dyn Eratosthenes> {
    match version {
        0 => Box::new(eratosthenes0::Eratosthenes0::new()),
        1 => Box::new(eratosthenes1::Eratosthenes1::new()),
        _ => Box::new(eratosthenes1::Eratosthenes1::new()),
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::time::Instant;

    #[test]
    fn generate_test() {
        for v in 0..2 {
            let mut eratosthenes = get_eratosthenes(v);
            let test_data: Vec<(usize, i64)> = vec![
                (100, 25),
                (1000, 168),
                (10000, 1229),
                (100000, 9592),
                (1000000, 78498),
                (10000000, 664579),
                (100000000, 5761455),
                (1000000000, 50847534),
                (10000000000, 455052511),
            ];
            for (x, expect) in test_data {
                let start = Instant::now();
                eratosthenes.generate(x);
                let end = start.elapsed();
                let pi = eratosthenes.count();
                assert_eq!(expect, pi);
                eprintln!("{} {:.03} sec", x, end.as_secs_f64());
                if end.as_secs() >= 3 {
                    break;
                }
            }
        }
    }
}
