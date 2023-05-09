use crate::bits;

pub struct Eratosthenes1 {
    flags: bits::Bits,
}

impl super::Eratosthenes for Eratosthenes1 {
    // Finds prime numbers in range [0, x).
    fn generate(&mut self, x: usize) {
        self.init(x);

        let isq = ((x as f64).sqrt().round() as usize) / 2;
        for i in 0..=isq {
            if !self.flags.get(i) {
                continue;
            }
            let p = 2 * i + 1;
            for m in ((2 * i * (i + 1))..=(x - 1) / 2).step_by(p) {
                self.flags.unset(m);
            }
        }
    }

    fn generate_range(&mut self, _x: usize, _y: usize) {}

    fn count(&self) -> i64 {
        self.flags.bit_count() as i64 + 1
    }

    fn version(&self) -> i32 {
        1
    }
}

impl Eratosthenes1 {
    pub fn new() -> Eratosthenes1 {
        Eratosthenes1 {
            flags: bits::Bits::new(1, false),
        }
    }

    fn init(&mut self, x: usize) {
        let n = (x - 1) / 2;
        // flags[i] shows if 2 * i + 1 is prime or not.
        self.flags = bits::Bits::new(n + 1, true);
        // Turn off flags for 1.
        self.flags.unset(0);
    }
}
