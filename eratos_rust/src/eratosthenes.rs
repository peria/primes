mod eratosthenes0;

pub trait Eratosthenes {
    // Finds prime numbers in range [0, x).
    fn generate(&mut self, x: usize);

    // Finds prime numbers in range [x, y).
    fn generate_range(&mut self, x: usize, y: usize);

    // Returns the number of counted prime numbers.
    fn count(&self) -> i64;

    // Return the implemented version.
    fn version(&self) -> i32;
}

pub fn get_eratosthenes(version: i32) -> Box<dyn Eratosthenes> {
    match version {
        0 => Box::new(eratosthenes0::Eratosthenes0::new()),
        _ => Box::new(eratosthenes0::Eratosthenes0::new()),
    }
}
