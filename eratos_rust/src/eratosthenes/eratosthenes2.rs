use crate::bits;

pub struct Eratosthenes2 {
    flags: bits::Bytes,
}

impl super::Eratosthenes for Eratosthenes2 {
    fn generate(&mut self, x: usize) {
        use crate::eratosthenes::B;
        use crate::eratosthenes::C0;
        use crate::eratosthenes::C1;
        use crate::eratosthenes::D;

        self.init(x);

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
                while mj < self.flags.len() {
                    self.flags.mask(mj, D[j][k]);
                    mj += i * C1[k] + C0[j][k];
                    k = (k + 1) % 8;
                }
            }
        }
    }

    fn generate_range(&mut self, _x: usize, _y: usize) {}

    fn count(&self) -> i64 {
        self.flags.bit_count() as i64 + 3
    }

    fn version(&self) -> i32 {
        2
    }
}

impl Eratosthenes2 {
    pub fn new() -> Eratosthenes2 {
        Eratosthenes2 {
            flags: bits::Bytes::new(1, false),
        }
    }

    fn init(&mut self, x: usize) {
        use crate::eratosthenes::B;

        let n = x / 30 + 1;

        self.flags = bits::Bytes::new(n, true);
        self.flags.unset(0, 0);

        for j in 0..8 {
            let p = 30 * (n - 1) + B[j];
            if p > x {
                self.flags.unset(n - 1, j);
            }
        }
    }
}
