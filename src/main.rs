#![allow(unused_imports)]
#![allow(dead_code)]

use dynamic::Dynamic;
use std::collections::HashMap;
use std::rc::Rc;

use cw_fdm::State;


fn main() {
    let mut state = State::new(123.456);
    let value = state.get_ref::<f64>().unwrap();

    println!("value {}", value);
    state.set_value(923847.6).unwrap();
    println!("value {}", state.get_ref::<f64>().unwrap());

    let mut_ref = state.get_mut::<f64>().unwrap();
    *mut_ref = 1234567890.0;

    println!("value {}", state.get_ref::<f64>().unwrap());



}
