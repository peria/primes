use crate::bits;

pub struct Eratosthenes0 {
    flags: bits::Bits,
}

impl super::Eratosthenes for Eratosthenes0 {
    // Finds prime numbers in range [0, x).
    fn generate(&mut self, x: usize) {
        self.init(x);

        let sq = (x as f64).sqrt() as usize + 1;
        for p in 0..sq {
            if !self.flags.get(p) {
                continue;
            }
            for m in (p * p..=x).step_by(p) {
                self.flags.unset(m);
            }
        }
    }

    // Finds prime numbers in range [x, y).
    fn generate_range(&mut self, _x: usize, _y: usize) {}

    // Returns the number of counted prime numbers.
    fn count(&self) -> i64 {
        self.flags.bit_count() as i64
    }

    // Return the implemented version.
    fn version(&self) -> i32 {
        0
    }
}

impl Eratosthenes0 {
    pub fn new() -> Eratosthenes0 {
        Eratosthenes0 {
            flags: bits::Bits::new(1, false),
        }
    }

    fn init(&mut self, x: usize) {
        let n = x + 1;
        let mut bits = bits::Bits::new(n, true);
        // Turn off flags for 0 and 1.
        bits.unset(0);
        bits.unset(1);
        self.flags = bits;
    }
}
