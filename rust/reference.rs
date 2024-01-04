// this is meant to be a ctrl+f style reference, don't use as a primary learning source
//  ctrl+f appropriate keywords to find relevant locs e.g. ctrl+f DOCSTRINGS
/* install rust from below:
 *  https://rustup.rs/#
 *  curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
 * from tldr: 
 * - Install the nightly toolchain for your system:
 *   rustup install nightly
 *
 * - Switch the default toolchain to nightly so that the `cargo` and `rustc` commands will use it:
 *   rustup default nightly
 *
 * - Use the nightly toolchain when inside the current project but leave global settings unchanged:
 *   rustup override set nightly
 *
 * - Update all toolchains:
 *   rustup update
 *
 * - List installed toolchains:
 *   rustup show
 *
 * - Run `cargo build` with a certain toolchain:
 *   rustup run toolchain cargo build
 *
 * - Open the local Rust documentation in the default web browser:
 *   rustup doc
 * for completions do this:
 *  mkdir -p ~/.local/share/bash-completion/completions
 *  rustup completions bash >> ~/.local/share/bash-completion/completions/rustup
*/
// TLDR;
// macros have a ! postfix, for example write! or println!
// everything is immutable by default, mut keyword makes them mutable
// there is NO None type!
// structs are equivalent to dataclasses in python
//  The impl keyword is primarily used to define implementations on types. 
//  Functions and consts can both be defined in an implementation. A function defined in an impl block can be standalone, meaning it would be called like Foo::bar(). 
//  If the function takes self, &self, or &mut self as its first argument, it can also be called using method-call syntax, a familiar feature to any object oriented programmer, like foo.bar().
// Impl functions that do not take self are essentially static methods, and must be called as my_instance::foo(), while "instance methods" (which take a self, &self, or &mut self) can be called as my_instance.boo()
 
// HEADER FILES
// Rust does not have header files.
// Every struct, implementation, function, const, and macro resides in a file ending in .rs. 
// Code is made public or not by structuring .rs files into modules and exposing functions via the pub keyword.
// For functions, the definition and the implementation are the same thing - the function implementation's signature is its definition.
// For structs, the structure is declared and there are zero or more implementation blocks for functions and traits that are associated with the struct. 
// Usually the implementation and definition will reside right next to each other.
// Other modules can use the other module's public types and functions and the compiler will obtain the definition.
// Ordering is less important too. Rust can forward reference structs or functions, or even use the very same module that a piece of code is a part of.
// The only time that ordering matters is for macro definitions. A macro must be defined before a module that uses it.
// Rust files reference non-dependent modules with the use keyword and pull-in dependent modules with the mod keyword.

// SEMICOLONS & RETURN STATEMENTS
// They're not optional. Semicolons modify the behaviour of an expression statement 
// so it should be a conscious decision whether you use them or not for a line of code.
// Almost everything in Rust is an expression. An expression is something that returns a value. 
// If you put a semicolon you are suppressing the result of this expression, which in most cases is what you want.
// On the other hand, this means that if you end your function with an expression without a semicolon, 
// the result of this last expression will be returned. The same can be applied for a block in a match statement.
// AUTHOR'S NOTE: apparently return statements are bloat... thankfully rust still has them, see below from phind:
fn max(a: i32, b: i32) -> i32 {
   if a > b {
       return a;
   }
   return b;
}

fn is_divisible_by(lhs: u32, rhs: u32) -> bool {
   if rhs == 0 {
       return false;
   }
   lhs % rhs == 0
}

fn five() -> i32 {
   5
}

// COMPILATION
// $ rustc file.rs

// DEBUG PRINTING:
// All types which want to use std::fmt formatting traits require an implementation to be printable. 
// Automatic implementations are only provided for types such as in the std library. All others must be manually implemented somehow.
// fmt::Debug can be automatically #[derived however fmt::Display cannot.
// This structure cannot be printed either with `fmt::Display` or
// with `fmt::Debug`.
struct UnPrintable(i32);

// The `derive` attribute automatically creates the implementation
// required to make this `struct` printable with `fmt::Debug`.
#[derive(Debug)]
struct DebugPrintable(i32);

// Derive the `fmt::Debug` implementation for `Structure`. `Structure`
// is a structure which contains a single `i32`.
#[derive(Debug)]
struct Structure(i32);

#[derive(Debug)]
struct Person<'a> {
    name: &'a str,
    age: u8
}

#[derive(Debug)]
struct Color {
    red: u8,
    green: u8,
    blue: u8,
}

impl Display for Color {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        let hex = self.red as u32 * 65536 + self.green as u32 * 256 + self.blue as u32;
        write!(f, "RGB ({red}, {green}, {blue}) 0x{hex:0>6X}", 
                red=self.red, 
                green=self.green, 
                blue=self.blue)
    }
}

// HELLO WORLD & FORMATTED/FORMATTING PRINT
// Printing is handled by a series of macros defined in std::fmt some of which include:
// format!: write formatted text to String
// print!: same as format! but the text is printed to the console (io::stdout).
// println!: same as print! but a newline is appended.
// eprint!: same as print! but the text is printed to the standard error (io::stderr).
// eprintln!: same as eprint! but a newline is appended.
fn main() {
    // println! is a MACRO
    println!("Hello World!");
    // In general, the `{}` will be automatically replaced with any
    // arguments. These will be stringified.
    println!("{} days", 31);
    // POSITIONAL formatting
    println!("{0}, this is {1}. {1}, this is {0}", "Alice", "Bob");
    // NAMED ARGUMENTS formatting
    println!("{subject} {verb} {object}", object="the lazy dog", subject="the quick brown fox", verb="jumps over");
    // FORMAT SPECIFIERS
    // Different formatting can be invoked by specifying the format character after a `:`.
    println!("Base 10:               {}",   69420); // 69420
    println!("Base 2 (binary):       {:b}", 69420); // 10000111100101100
    println!("Base 8 (octal):        {:o}", 69420); // 207454
    println!("Base 16 (hexadecimal): {:x}", 69420); // 10f2c
    println!("Base 16 (hexadecimal): {:X}", 69420); // 10F2C
    println!("{number:>5}", number=1);
    // You can pad numbers with extra zeroes,
    println!("{number:0>5}", number=1); // 00001
    // You can use named arguments in the format specifier by appending a `$`.
    println!("{number:0>width$}", number=1, width=5);
    
    // AUTHORS NOTE: jesus christ
    // For Rust 1.58 and above, you can directly capture the argument from a
    // surrounding variable. Just like the above, this will output
    // "    1", 4 white spaces and a "1".
    let number: f64 = 1.0;
    let width: usize = 5;
    println!("{number:>width$}");
    
    // DISABLE WARNINGS
    // is an ATTRIBUTE which only apply to the module after it.
    //#[allow(dead_code)] // disable `dead_code` which warn against unused module
    //struct Structure(i32);
    
    // `Structure` is printable!
    println!("Now {:?} will print!", Structure(3));
    
    let name = "Peter";
    let age = 27;
    let peter = Person { name, age };
    // PRETTY PRINT
    println!("{:#?}", peter);
    
    for color in [
        Color { red: 128, green: 255, blue: 90 },
        Color { red: 0, green: 3, blue: 254 },
        Color { red: 0, green: 0, blue: 0 },
    ] {
        // https://doc.rust-lang.org/rust-by-example/hello/print/fmt.html
        println!("{}", color);
    }
}

// PRIMITIVES / DATA TYPES

// SCALARES / DATA TYPES
// Signed integers: i8, i16, i32, i64, i128 and isize (pointer size)
// Unsigned integers: u8, u16, u32, u64, u128 and usize (pointer size)
// Floating point: f32, f64
// char Unicode scalar values like 'a', 'α' and '∞' (4 bytes each)
// bool either true or false
// The unit type (), whose only possible value is an empty tuple: ()

// COMPOUND TYPES / DATA TYPES
// Arrays like [1, 2, 3]
//  An array is a collection of objects of the same type T, stored in contiguous memory. 
//  Arrays are created using brackets [], and their length, which is known at compile time, is part of their type signature [T; length].
// Slices are similar to arrays, but their length is not known at compile time. 
//  Instead, a slice is a two-word object; the first word is a pointer to the data, the second word is the length of the slice. 
//  The word size is the same as usize, determined by the processor architecture, e.g. 64 bits on an x86-64. 
//  Slices can be used to borrow a section of an array and have the type signature &[T].
// Tuples like (1, true)
//  A tuple is a collection of values of different types.

// Integers can, alternatively, be expressed using hexadecimal, octal or binary notation using these prefixes respectively: 0x, 0o or 0b.
// Underscores can be inserted in numeric literals to improve readability, e.g. 1_000 is the same as 1000, and 0.000_001 is the same as 0.000001.
// Rust also supports scientific E-notation, e.g. 1e6, 7.6e-4. The associated type is f64.

// Variables can always be type annotated. Numbers may additionally be annotated via a suffix or by default. 
// INTEGERS DEFAULT TO i32 and FLOATS TO f64. Note that Rust can also infer types from context.
// Despite the value of a unit type being a tuple, it is not considered a compound type because it does not contain multiple values.

use std::mem;

// Tuples can be used as function arguments and as return values.
fn reverse(pair: (i32, bool)) -> (bool, i32) {
    // `let` can be used to bind the members of a tuple to variables.
    // AUTHOR'S NOTE: this is TUPLE UNPACKING essentially
    let (int_param, bool_param) = pair;

    (bool_param, int_param)
}

fn main() {
    // All elements can be initialized to the same value.
    let ys: [i32; 500] = [0; 500];
    // Indexing starts at 0.
    println!("First element of the array: {}", xs[0]);
    println!("Second element of the array: {}", xs[1]);
    
    // `len` returns the count of elements in the array.
    println!("Number of elements in array: {}", xs.len());

    // Arrays are stack allocated.
    println!("Array occupies {} bytes", mem::size_of_val(&xs));
    
    // Slices can point to a section of an array.
    // They are of the form [starting_index..ending_index].
    // `starting_index` is the first position in the slice.
    // `ending_index` is one more than the last position in the slice.
    println!("Borrow a section of the array as a slice.");
    analyze_slice(&ys[1 .. 4]);

    // Example of empty slice `&[]`:
    let empty_array: [u32; 0] = [];
    assert_eq!(&empty_array, &[]);
    assert_eq!(&empty_array, &[][..]); // Same but more verbose
    
    // Arrays can be safely accessed using `.get`, which returns an
    // `Option`. This can be matched as shown below, or used with
    // `.expect()` if you would like the program to exit with a nice
    // message instead of happily continue.
    for i in 0..xs.len() + 1 { // Oops, one element too far!
        match xs.get(i) {
            Some(xval) => println!("{}: {}", i, xval),
            None => println!("Slow down! {} is too far!", i),
        }
    }

    // Out of bound indexing on array causes compile time error.
    //println!("{}", xs[5]);
    // Out of bound indexing on slice causes runtime error.
    //println!("{}", xs[..][5]);

    // Variables can be type annotated.
    let logical: bool = true;

    let a_float: f64 = 1.0;  // Regular annotation
    let an_integer   = 5i32; // Suffix annotation
    
    // A type can also be inferred from context.
    let mut inferred_type = 12; // Type i64 is inferred from another line.
    // We need to tell the compiler the type of the literals we use. For now, we'll use the u32 suffix to indicate that the literal is 
    // an unsigned 32-bit integer, and the i32 suffix to indicate that it's a signed 32-bit integer.
    inferred_type = 4294967296i64;
    
    // Variables can be overwritten with shadowing.
    let inferred_type = true;
    
    // A tuple with a bunch of different types.
    let long_tuple = (1u8, 2u16, 3u32, 4u64,
                      -1i8, -2i16, -3i32, -4i64,
                      0.1f32, 0.2f64,
                      'a', true);

    // Values can be extracted from the tuple using tuple indexing.
    println!("Long tuple first value: {}", long_tuple.0);
    println!("Long tuple second value: {}", long_tuple.1);

    // Tuples can be tuple members.
    let tuple_of_tuples = ((1u8, 2u16, 2u32), (4u64, -1i8), -2i16);

    // Tuples are printable.
    println!("tuple of tuples: {:?}", tuple_of_tuples);

    // AUTHOR'S NOTE: this is hilarious
    // But long Tuples (more than 12 elements) cannot be printed.
    //let too_long_tuple = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);
    //println!("Too long tuple: {:?}", too_long_tuple);
    
    // Fixed-size array (type signature is superfluous).
    let xs: [i32; 5] = [1, 2, 3, 4, 5];
}

// CUSTOM TYPES / DATA TYPES
// struct: define a structure
// enum: define an enumeration

// Constants can also be created via the const and static keywords.

// STRUCTS
// Three types of structs:

struct CLikeStruct {
    name: String,
    age: u8,
}

struct Unit;

struct NamedTupleStruct(i32, f32);

// ENUMS

enum WebEvent {
    // An `enum` variant may either be `unit-like`,
    PageLoad,
    PageUnload,
    // like tuple structs,
    KeyPress(char),
    Paste(String),
    // or c-like structures.
    Click { x: i64, y: i64 },
}

// enum with implicit discriminator (starts at 0)
// C-LIKE ENUM
enum Number {
    Zero,
    One,
    Two,
}

// enum with explicit discriminator
enum Color {
    Red = 0xff0000,
    Green = 0x00ff00,
    Blue = 0x0000ff,
}

// A function which takes a `WebEvent` enum as an argument and
// returns nothing.
fn inspect(event: WebEvent) {
    match event {
        WebEvent::PageLoad => println!("page loaded"),
        WebEvent::PageUnload => println!("page unloaded"),
        // Destructure `c` from inside the `enum` variant.
        WebEvent::KeyPress(c) => println!("pressed '{}'.", c),
        WebEvent::Paste(s) => println!("pasted \"{}\".", s),
        // Destructure `Click` into `x` and `y`.
        WebEvent::Click { x, y } => {
            println!("clicked at x={}, y={}.", x, y);
        },
    }
}

fn main() {
    let pressed = WebEvent::KeyPress('x');
    // `to_owned()` creates an owned `String` from a string slice.
    let pasted  = WebEvent::Paste("my text".to_owned());
    let click   = WebEvent::Click { x: 20, y: 80 };
    let load    = WebEvent::PageLoad;
    let unload  = WebEvent::PageUnload;

    inspect(pressed);
    inspect(pasted);
    inspect(click);
    inspect(load);
    inspect(unload);
}

// TYPE ALIASES
enum VeryVerboseEnumOfThingsToDoWithNumbers {
    Add,
    Subtract,
}

// Creates a type alias
type Operations = VeryVerboseEnumOfThingsToDoWithNumbers;

// most common type alias usecase, Self:: is a builtin alias for self I suppose
impl VeryVerboseEnumOfThingsToDoWithNumbers {
    fn run(&self, x: i32, y: i32) -> i32 {
        match self {
            Self::Add => x + y,
            Self::Subtract => x - y,
        }
    }
}

// INCLUDES / IMPORTS
// Explicitly `use` each name so they are available without
// manual scoping.
use crate::Status::{Poor, Rich}; // import specific things from a namespace 
// Automatically `use` each name inside `Work`.
use crate::Work::*; // WILDCARD IMPORT

// STATIC / CONSTANTS / GLOBALS / VARIABLE BINDINGS
// Globals are declared outside all other scopes.
const THRESHOLD: i32 = 10;
static LANGUAGE: &str = "Rust";

fn main() {
    // The compiler warns about unused variable bindings; these warnings can
    // be silenced by prefixing the variable name with an underscore
    let _unused_variable = 3u32;
    let noisy_unused_variable = 2u32;
    // Declare a variable binding
    let another_binding;

    // Error! Use of uninitialized binding
    println!("another binding: {}", another_binding);
}

// CASTING

fn main() {
    let integer = decimal as u8;
    let character = integer as char;
    println!("1000 as a u16 is: {}", 1000 as u16);
    // 300.0 as u8 is 255
    println!(" 300.0 as u8 is : {}", 300.0_f32 as u8);
    // -100.0 as u8 is 0
    println!("-100.0 as u8 is : {}", -100.0_f32 as u8);
    // nan as u8 is 0
    println!("   nan as u8 is : {}", f32::NAN as u8);
    
    // converting floats to integers performs a "saturating cast" and as such has a runtime cost,
    // to prevent, use the following, but note that the results might overflow and return unsound values
    unsafe {
        // 300.0 as u8 is 44
        println!(" 300.0 as u8 is : {}", 300.0_f32.to_int_unchecked::<u8>());
        // -100.0 as u8 is 156
        println!("-100.0 as u8 is : {}", (-100.0_f32).to_int_unchecked::<u8>());
        // nan as u8 is 0
        println!("   nan as u8 is : {}", f32::NAN.to_int_unchecked::<u8>());
    }
}

// CASTING WITH TRAITS / FROM / INTO
#[derive(Debug)]
struct Number {
    value: i32,
}

// convert from i32 into Number
impl std::convert::From<i32> for Number {
    fn from(item: i32) -> Self {
        Number { value: item }
    }
}

// convert from Number into i32
impl std::convert::Into<Number> for i32 {
    fn into(self) -> Number {
        Number { value: self }
    }
}

struct EvenNumber(i32);

// TRY to convert an EvenNumber FROM i32
impl std::convert::TryFrom<i32> for EvenNumber {
    type Error = ();

    fn try_from(value: i32) -> Result<Self, Self::Error> {
        if value % 2 == 0 {
            Ok(EvenNumber(value))
        } else {
            Err(())
        }
    }
}

// AUTHOR'S CODE equivalent tryinto
//  of course, an EvenNumber is a subset of i32, and as such will always return
//  if you comment this out however, the compiler will warn that there is no equivalent TryInto for the TryFrom
//  to suppress the error, use the attribute below
#[derive(PartialEq)]
impl std::convert::TryInto<Number> for i32 {
    type Error = ();
    
    fn try_into(self) -> Result<Number, Self::Error> {
        Ok(self.0)
    }
}

// converting to string should be done using fmt::Display
fn main() {
    let num = Number::from(30);
    println!("My number is {:?}", num);
    
    // parsing / converting FROM a string
    let parsed: i32 = "5".parse().unwrap();
    let turbo_parsed = "10".parse::<i32>().unwrap(); // turbofish syntax (looks bad)

    let sum = parsed + turbo_parsed;
    println!("Sum: {:?}", sum);
}



// DOCSTRINGS https://doc.rust-lang.org/rust-by-example/meta/doc.html
// Whenever you are working in a crate, cargo doc --open will generate documentation for your project and 
// all its dependencies in their correct version, and open it in your browser. 
// Add the flag --document-private-items to also show items not marked pub.
// When running rustdoc, these are the comments that get compiled into documentation. They are denoted by a ///, and support Markdown.
#![crate_name = "doc"]

/// A human being is represented here
pub struct Person {
    /// A person must have a name, no matter how much Juliet may hate it
    name: String,
}
