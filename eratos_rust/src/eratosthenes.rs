mod eratosthenes0;
mod eratosthenes1;
mod eratosthenes2;
mod eratosthenes3;

const B: [usize; 8] = [1, 7, 11, 13, 17, 19, 23, 29];

// [n0-m0 for (n0,m0) in zip(n, m)]
const C1: [usize; 8] = [6, 4, 2, 4, 2, 4, 6, 2];

// [[m0*n1/30-m0*m1/30 for (n1,m1) in zip(n, m)] for m0 in m]
const C0: [[usize; 8]; 8] = [
    [0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 0, 1, 1, 1, 1],
    [2, 2, 0, 2, 0, 2, 2, 1],
    [3, 1, 1, 2, 1, 1, 3, 1],
    [3, 3, 1, 2, 1, 3, 3, 1],
    [4, 2, 2, 2, 2, 2, 4, 1],
    [5, 3, 1, 4, 1, 3, 5, 1],
    [6, 4, 2, 4, 2, 4, 6, 1],
];

// [[bitoff(m0*m1%30) for m1 in m] for m0 in m]
#[allow(dead_code)]
const D: [[u8; 8]; 8] = [
    [0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f],
    [0xfd, 0xdf, 0xef, 0xfe, 0x7f, 0xf7, 0xfb, 0xbf],
    [0xfb, 0xef, 0xfe, 0xbf, 0xfd, 0x7f, 0xf7, 0xdf],
    [0xf7, 0xfe, 0xbf, 0xdf, 0xfb, 0xfd, 0x7f, 0xef],
    [0xef, 0x7f, 0xfd, 0xfb, 0xdf, 0xbf, 0xfe, 0xf7],
    [0xdf, 0xf7, 0x7f, 0xfd, 0xbf, 0xfe, 0xef, 0xfb],
    [0xbf, 0xfb, 0xf7, 0x7f, 0xfe, 0xef, 0xdf, 0xfd],
    [0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe],
];

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
        2 => Box::new(eratosthenes2::Eratosthenes2::new()),
        3 => Box::new(eratosthenes3::Eratosthenes3::new()),
        _ => Box::new(eratosthenes2::Eratosthenes2::new()),
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::time::Instant;

    #[test]
    fn generate_test() {
        for v in 0..=3 {
            let mut eratosthenes = get_eratosthenes(v);
            let test_data: Vec<(u32, i64)> = vec![
                (2, 25),
                (3, 168),
                (4, 1229),
                (5, 9592),
                (6, 78498),
                (7, 664579),
                (8, 5761455),
                (9, 50847534),
                (10, 455052511),
            ];
            eprintln!("version: {}", v);
            for (e, expect) in test_data {
                let x = 10usize.pow(e);
                let start = Instant::now();
                eratosthenes.generate(x);
                let end = start.elapsed();
                let pi = eratosthenes.count();
                assert_eq!(expect, pi);
                eprintln!("pi(10^{:2}) = {:9} {:6.03} sec", e, pi, end.as_secs_f64());
                if end.as_secs() >= 1 {
                    break;
                }
            }
        }
    }
}
