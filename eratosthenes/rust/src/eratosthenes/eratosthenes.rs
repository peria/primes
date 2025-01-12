pub trait Eratosthenes {
    // Finds prime numbers in range [0, x).
    fn generate(&mut self, x: usize);

    // Finds prime numbers in range [x, y).
    fn generate_range(&mut self, x: usize, y: usize);

    // Returns the number of counted prime numbers.
    fn count(&self) -> usize;

    // Return the implemented version.
    fn version(&self) -> i32;
}
