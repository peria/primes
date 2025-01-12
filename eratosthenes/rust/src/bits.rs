pub struct Bits {
    bits: Vec<u64>,
}

impl Bits {
    pub fn new(num_bits: usize, is_filled: bool) -> Bits {
        const FULL_BITS: u64 = !0u64;
        let num_bytes = (num_bits + 63) / 64;
        let val = if is_filled { FULL_BITS } else { 0 };
        let mut x = Bits {
            bits: vec![val; num_bytes],
        };
        (num_bits..(num_bytes * 64)).for_each(|i| x.unset(i));
        x
    }

    pub fn set(&mut self, bit_id: usize) {
        self.bits[bit_id / 64] |= 1u64 << (bit_id % 64);
    }

    pub fn unset(&mut self, bit_id: usize) {
        self.bits[bit_id / 64] &= !(1u64 << (bit_id % 64));
    }

    pub fn get(&self, bit_id: usize) -> bool {
        (self.bits[bit_id / 64] & (1u64 << (bit_id % 64))) != 0
    }

    pub fn bit_count(&self) -> usize {
        self.bits.iter().map(|x| x.count_ones() as usize).sum()
    }
}

pub struct Bytes {
    bytes: Vec<u8>,
}

impl Bytes {
    pub fn new(num_bytes: usize, value: u8) -> Bytes {
        Bytes {
            bytes: vec![value; num_bytes],
        }
    }

    pub fn set_byte(&mut self, byte_id: usize, value: u8) {
        self.bytes[byte_id] = value;
    }

    pub fn set_bit(&mut self, byte_id: usize, bit_id: usize) {
        self.bytes[byte_id] |= 1u8 << bit_id;
    }

    pub fn unset_bit(&mut self, byte_id: usize, bit_id: usize) {
        self.bytes[byte_id] &= !(1u8 << bit_id);
    }

    pub fn mask(&mut self, byte_id: usize, mask: u8) {
        self.bytes[byte_id] &= mask;
    }

    pub fn get_byte(&self, byte_id: usize) -> u8 {
        self.bytes[byte_id]
    }

    pub fn get(&self, byte_id: usize, bit_id: usize) -> bool {
        (self.bytes[byte_id] & (1u8 << bit_id)) != 0
    }

    pub fn bit_count(&self) -> usize {
        self.bytes.iter().map(|x| x.count_ones() as usize).sum()
    }

    pub fn len(&self) -> usize {
        self.bytes.len()
    }
}
