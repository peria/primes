use crate::bits::Bytes;

use super::{Eratosthenes, BIT_MASKS, C0, C1, MOD30};

pub struct Eratosthenes2 {
    flags: Bytes,
}

impl Eratosthenes2 {
    pub fn new() -> Eratosthenes2 {
        Eratosthenes2 {
            flags: Bytes::new(0, 0),
        }
    }
}

impl Eratosthenes for Eratosthenes2 {
    fn version(&self) -> i32 {
        2
    }

    fn generate(&mut self, x: usize) {
        let r = x % 30;
        let size = x / 30 + if r == 0 { 0 } else { 1 };
        let mut flags = Bytes::new(size, 0xff);

        flags.set_byte(
            size - 1,
            match r {
                0 => 0xff,
                1 => 0x00,
                2..=7 => 0x01,
                8..=11 => 0x03,
                12..=13 => 0x07,
                14..=17 => 0x0f,
                18..=19 => 0x1f,
                20..=23 => 0x3f,
                _ => 0x7f,
            },
        );

        flags.unset_bit(0, 0); // 1 is not a prime
        let sqr_x = (x as f64).sqrt().ceil() as usize;
        let sqr_xi = sqr_x / 30 + 1;
        for i in 0..sqr_xi {
            let mut bits = flags.get_byte(i);
            while bits != 0 {
                let lsb = bits & (!bits + 1);
                let ibit = (lsb - 1).count_ones() as usize;
                let m = MOD30[ibit];
                let pm = 30 * i + 2 * m;

                let mut j = i * pm + (m * m) / 30;
                let mut k = ibit;
                while j < size {
                    flags.mask(j, BIT_MASKS[ibit][k]);
                    j += i * C1[k] + C0[ibit][k];
                    k = (k + 1) & 7;
                }
                bits &= bits - 1;
            }
        }
        self.flags = flags;
    }

    fn generate_range(&mut self, _x: usize, _y: usize) {
        eprintln!("Does not support ranged generation.");
    }

    fn count(&self) -> usize {
        // 2, 3, and 5 are counted separately.
        3 + self.flags.bit_count()
    }
}
