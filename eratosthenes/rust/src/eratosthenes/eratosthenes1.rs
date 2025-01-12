use crate::bits::Bits;

use super::Eratosthenes;

pub struct Eratosthenes1 {
    flags: Bits,
}

impl Eratosthenes1 {
    pub fn new() -> Eratosthenes1 {
        Eratosthenes1 {
            flags: Bits::new(0, false),
        }
    }
}

impl Eratosthenes for Eratosthenes1 {
    fn version(&self) -> i32 {
        1
    }

    fn generate(&mut self, x: usize) {
        let mut flags = Bits::new((x + 1) / 2, true);
        flags.unset(0); // 1 is not a prime
        let sqr_x = (x as f64).sqrt().ceil() as usize;
        let sqr_xi = sqr_x / 2 + 1;
        for pi in 1..=sqr_xi {
            if flags.get(pi) {
                let p = pi * 2 + 1;
                for j in ((2 * pi * (pi + 1))..(x + 1) / 2).step_by(p) {
                    flags.unset(j);
                }
            }
        }
        self.flags = flags;
    }

    fn generate_range(&mut self, _x: usize, _y: usize) {
        eprintln!("Does not support ranged generation.");
    }

    fn count(&self) -> usize {
        // 2 is counted separately.
        1 + self.flags.bit_count()
    }
}
