pub mod bits;
pub mod eratosthenes;

pub fn get_eratosthenes(version: i32) -> Box<dyn eratosthenes::Eratosthenes> {
    eratosthenes::get_eratosthenes(version)
}
