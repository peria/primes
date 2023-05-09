use crate::bits;

pub struct Eratosthenes3 {
    flags: bits::Bytes,
    primes: Vec<(usize, usize)>,
}

impl super::Eratosthenes for Eratosthenes3 {
    fn generate(&mut self, x: usize) {
        self.init(x);
        self.sieve();
    }

    fn generate_range(&mut self, _x: usize, _y: usize) {}

    fn count(&self) -> i64 {
        self.flags.bit_count() as i64 + 3
    }

    fn version(&self) -> i32 {
        2
    }
}

impl Eratosthenes3 {
    pub fn new() -> Eratosthenes3 {
        Eratosthenes3 {
            flags: bits::Bytes::new(1, false),
            primes: Vec::new(),
        }
    }

    fn init(&mut self, x: usize) {
        use crate::eratosthenes::B;
        use crate::eratosthenes::C0;
        use crate::eratosthenes::C1;
        use crate::eratosthenes::D;

        let n = x / 30 + 1;

        self.flags = bits::Bytes::new(n, true);
        self.flags.unset(0, 0);

        for j in 0..8 {
            let p = 30 * (n - 1) + B[j];
            if p > x {
                self.flags.unset(n - 1, j);
            }
        }

        let isq = ((x as f64).sqrt() as usize) / 30 + 1;
        for i in 0..=isq {
            for j in 0..8 {
                if !self.flags.get(i, j) {
                    continue;
                }
                let m = B[j];
                let pm = 30 * i + 2 * m;
                let mut mj = i * pm + (m * m) / 30;
                let mut k = j;
                while mj <= isq {
                    self.flags.mask(mj, D[j][k]);
                    mj += i * C1[k] + C0[j][k];
                    k = (k + 1) % 8;
                }
                let prime = (i << 3) + j;
                let index = (mj << 3) + k;
                self.primes.push((prime, index));
            }
        }
    }

    fn sieve(&mut self) {
        use crate::eratosthenes::C0;
        use crate::eratosthenes::C1;
        use crate::eratosthenes::D;

        const SEGMENT_SIZE: usize = 1000000;
        for offset in (0..self.flags.len()).step_by(SEGMENT_SIZE) {
            let up = self.flags.len().min(offset + SEGMENT_SIZE);
            for (prime, index) in self.primes.iter_mut() {
                let pi = *prime >> 3;
                let pj = *prime & 7;
                let mut mj = *index >> 3;
                let mut k = *index & 7;
                while mj < up {
                    self.flags.mask(mj, D[pj][k]);
                    mj += pi * C1[k] + C0[pj][k];
                    k = (k + 1) % 8;
                }
                *index = (mj << 3) + k;
            }
        }
    }
}
