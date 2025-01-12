use crate::bits::Bits;

use super::Eratosthenes;

pub struct Eratosthenes0 {
    flags: Bits,
}

impl Eratosthenes0 {
    pub fn new() -> Eratosthenes0 {
        Eratosthenes0 {
            flags: Bits::new(0, false),
        }
    }
}

impl Eratosthenes for Eratosthenes0 {
    fn version(&self) -> i32 {
        0
    }

    fn generate(&mut self, x: usize) {
        let mut flags = Bits::new(x + 1, true);
        flags.unset(0);
        flags.unset(1);
        let sqr_x = (x as f64).sqrt().ceil() as usize;
        for p in 2..=sqr_x {
            if flags.get(p) {
                for j in ((p * p)..=x).step_by(p) {
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
        self.flags.bit_count()
    }
}
