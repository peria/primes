pub struct Eratosthenes1 {
    flags: Vec<u64>,
}

impl super::Eratosthenes for Eratosthenes1 {
    // Finds prime numbers in range [0, x).
    fn generate(&mut self, x: usize) {
        const FULL_BITS: u64 = !0u64;
        let n = x / 2 / 64 + 1;
        // flags[i] shows if 2 * i + 1 is prime or not.
        self.flags = vec![FULL_BITS; n];
        let bits = n * 64;
        // Turn off flags for 1.
        self.flags[0] &= !1u64;
        // Turn off flags for out of the range.
        for i in ((n - 1) * 64)..(n * 64) {
            let p = 2 * i + 1;
            if p > x {
                self.set_off(i);
            }
        }

        let isq = ((x as f64).sqrt() as usize) / 2 + 1;
        for i in 0..isq {
            if !self.is_prime(i) {
                continue;
            }
            let p = 2 * i + 1;
            for m in ((2 * i * (i + 1))..bits).step_by(p) {
                self.set_off(m);
            }
        }
    }

    // Finds prime numbers in range [x, y).
    fn generate_range(&mut self, _x: usize, _y: usize) {}

    // Returns the number of counted prime numbers.
    fn count(&self) -> i64 {
        self.flags
            .iter()
            .map(|x| x.count_ones() as i64)
            .sum::<i64>()
            + 1
    }

    // Return the implemented version.
    fn version(&self) -> i32 {
        0
    }
}

impl Eratosthenes1 {
    pub fn new() -> Eratosthenes1 {
        Eratosthenes1 { flags: Vec::new() }
    }

    fn is_prime(&self, n: usize) -> bool {
        (self.flags[n / 64] & (1u64 << (n % 64))) != 0
    }

    fn set_off(&mut self, n: usize) {
        self.flags[n / 64] &= !(1u64 << (n % 64));
    }
}
