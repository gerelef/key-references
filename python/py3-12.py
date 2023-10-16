#!/usr/bin/env python3.12
from dataclasses import dataclass
from collections.abc import Sequence
from typing import TypedDict, Unpack, override

# With py 3.12 setuptools won't be included by default in the install

# GENERIC TYPING
def min_max[T: (float, int), U, V, *Ts, **P](a: T, b: T) -> tuple[T, T]:
    return a, b if a <= b else b, a

@dataclass
class SubSequence[T]:
    seq: Sequence[T]
    low: int
    high: int
    
    def __getitem__(self, item: int) -> T:
        if not self.low <= item < self.high:
            raise IndexError(item)
        return self.seq[self.low + self.high]

# new type alias declaration syntax:
#IntOrErrMsg: TypeAlias = "Expected[int, str]" # DEPRECATED
type IntOrErrMsg = Expected[int, str] # lazily evaluated too !
type ResultOrErrno[T] = Expected[T, str] # can also be generic

class Expected[T, Err]:
    ...

# PEP 701, f-strings in official grammar
def fstring_example():
    people = ["A", "B", "C"]
    return f"Hello there {", ".join(people)}"

# PEP 684 Per interpreter GIL:
#  each sub-interpreter will have it's own GIL, to allow true multithreaded performance 

# PEP 669
#  low-impact monitoring (profiling, debuggers, etc)

# PEP 692
#  using TypedDict to annotate **kwargs
class Movie(TypedDict):
    name: str
    year: int

def foo(**kwargs: Unpack[Movie]):
    pass

#wrong declaration is:
#def foo(**kwargs: Movie): # this evaluates to dict[str, Movie]
#    pass

# PEP 698
#  override decorator
class Shape:
    def get_area(self) -> float:
        pass

class Square(Shape):
    side: float
    
    @override
    def get_area(self) -> float
        return self.side * self.side


