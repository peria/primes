pub mod bits;
mod eratosthenes;

pub use crate::eratosthenes::Eratosthenes;

pub fn get_eratosthenes(version: i32) -> Box<dyn eratosthenes::Eratosthenes> {
    eratosthenes::get_eratosthenes(version)
}
