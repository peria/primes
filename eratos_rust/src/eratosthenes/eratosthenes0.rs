pub struct Eratosthenes0 {
    flags: Vec<u64>,
}

impl super::Eratosthenes for Eratosthenes0 {
    // Finds prime numbers in range [0, x).
    fn generate(&mut self, x: usize) {
        const FULL_BITS: u64 = !0u64;
        let n = x / 64 + 1;
        let mut flags = vec![FULL_BITS; n];
        // Turn off flags for 0 and 1.
        flags[0] ^= 3;
        // Turn off flags for out of the range.
        flags[n - 1] = (1u64 << ((x + 1) % 64)) - 1;
        self.flags = flags;

        let sq = (x as f64).sqrt() as usize + 1;
        for p in 0..sq {
            if !self.is_prime(p) {
                continue;
            }
            for m in (p * p..=x).step_by(p) {
                self.set_off(m);
            }
        }
    }

    // Finds prime numbers in range [x, y).
    fn generate_range(&mut self, _x: usize, _y: usize) {}

    // Returns the number of counted prime numbers.
    fn count(&self) -> i64 {
        self.flags.iter().map(|x| x.count_ones() as i64).sum()
    }

    // Return the implemented version.
    fn version(&self) -> i32 {
        0
    }
}

impl Eratosthenes0 {
    pub fn new() -> Eratosthenes0 {
        Eratosthenes0 { flags: Vec::new() }
    }

    fn is_prime(&self, n: usize) -> bool {
        (self.flags[n / 64] & (1u64 << (n % 64))) != 0
    }

    fn set_off(&mut self, n: usize) {
        self.flags[n / 64] &= !(1u64 << (n % 64));
    }
}
