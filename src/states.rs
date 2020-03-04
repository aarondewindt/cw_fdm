use dynamic::Dynamic;
use std::collections::HashMap;
use std::any::Any;
use std::result::Result;


pub struct State {
    value_reference: Box<Dynamic>
}

impl State {
    pub fn new<T: Any>(value: T) -> State {
        State{
            value_reference: Dynamic::new(value)
        }
    }

    pub fn set_value<T: Any>(&mut self, value: T) -> Result<(), ()> {
        match self.value_reference.downcast_mut::<T>() {
            Some(v) => *v = value,
            None => return Result::Err(())
        };
        Result::Ok(())
    }

    pub fn get_ref<T: Any>(&self) -> Option<&T> {
        match self.value_reference.downcast_ref::<T>() {
            Some(value) => Some(value),
            None => None
        }
    }

    pub fn get_mut<T: Any>(&mut self) -> Option<&mut T> {
        match self.value_reference.downcast_mut::<T>() {
            Some(value) => Some(value),
            None => None
        }
    }
}


pub struct _States {
    states: HashMap<String, State>
}

impl _States {

}
