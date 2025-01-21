use crate::bits::Bytes;

use super::{Eratosthenes, BIT_MASKS, C0, C1, MOD30, SEGMENT_SIZE};

pub struct Eratosthenes3 {
    flags: Bytes,
    sflags: Bytes,
    indecies: Vec<u32>,
}

impl Eratosthenes3 {
    pub fn new() -> Eratosthenes3 {
        Eratosthenes3 {
            flags: Bytes::new(0, 0),
            sflags: Bytes::new(0, 0),
            indecies: Vec::new(),
        }
    }

    fn generate_small(&mut self, sx: usize) {
        let sxi = sx / 30 + 1;
        let qx = (sx as f64).sqrt().ceil() as usize;
        let qxi = qx / 30 + 1;

        self.sflags = Bytes::new(sxi, 0xff);
        let sflags = &mut self.sflags;
        sflags.unset_bit(0, 0);
        for i in 0..qxi {
            let mut bits = sflags.get_byte(i);
            while bits != 0 {
                let lsb = bits & (!bits + 1);
                let ibit = (lsb - 1).count_ones() as usize;
                let m = MOD30[ibit];
                let pm = 30 * i + 2 * m;

                let mut j = i * pm + (m * m) / 30;
                let mut k = ibit;
                while j < sxi {
                    sflags.mask(j, BIT_MASKS[ibit][k]);
                    j += i * C1[k] + C0[ibit][k];
                    k = (k + 1) & 7;
                }
                bits &= bits - 1;
            }
        }

        let indecies = &mut self.indecies;
        indecies.clear();
        for i in 0..sxi {
            let mut bits = sflags.get_byte(i);
            while bits != 0 {
                let lsb = bits & (!bits + 1);
                let ibit = (lsb - 1).count_ones() as usize;
                let m = MOD30[ibit];
                let j = i * (30 * i + 2 * m) + (m * m) / 30;
                indecies.push(((j << 3) | ibit) as u32);
                bits &= bits - 1;
            }
        }
    }

    fn init_flags(&mut self, x: usize, size: usize) {
        let mut flags = Bytes::new(size, 0xff);

        flags.set_byte(
            size - 1,
            match x % 30 {
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

        self.flags = flags;
    }

    fn generate_core(&mut self, offset: usize, size: usize) {
        let flags = &mut self.flags;
        let mut pindex = 0;
        for i in 0..self.sflags.len() {
            let mut primes = self.sflags.get_byte(i);
            while primes != 0 {
                let lsb = primes & (!primes + 1);
                let ibit = (lsb - 1).count_ones() as usize;
                let index = self.indecies[pindex] as usize;
                let mut j = index >> 3;
                let mut k = index & 7;
                while j < size {
                    flags.mask(j + offset, BIT_MASKS[ibit][k]);
                    j += i * C1[k] + C0[ibit][k];
                    k = (k + 1) & 7;
                }
                j -= size;
                self.indecies[pindex] = ((j << 3) | k) as u32;
                pindex += 1;
                primes &= primes - 1;
            }
        }
    }
}

impl Eratosthenes for Eratosthenes3 {
    fn version(&self) -> i32 {
        3
    }

    fn generate(&mut self, x: usize) {
        let sqr_x = (x as f64).sqrt().ceil() as usize;
        self.generate_small(sqr_x);

        let r = x % 30;
        let size = x / 30 + if r == 0 { 0 } else { 1 };
        self.init_flags(x, size);

        for offset in (0..size).step_by(SEGMENT_SIZE) {
            let segment_size = (size - offset).min(SEGMENT_SIZE);
            self.generate_core(offset, segment_size);
        }
    }

    fn generate_range(&mut self, _x: usize, _y: usize) {
        eprintln!("Does not support ranged generation.");
    }

    fn count(&self) -> usize {
        // 2, 3, and 5 are counted separately.
        3 + self.flags.bit_count()
    }
}
