# Brainfuck-C

A brainfuck interpreter written in C.

## What is brainfuck?

"Brainfuck is an esoteric programming language created in 1993 by Urban Mülle"

If you haven't already, give the wiki a quick read:

https://en.wikipedia.org/wiki/Brainfuck

Brainfuck is a turing complete programming language with only 8 instructions.

In addition to the instructions, you can think of Brainfuck as having three concepts:

1. A byte array of length N. (the wiki defines it as infinite, but different implementations give it a different length)

2. A memory pointer. `*m` which points to a location in the byte array.

3. An instruction pointer. `*p` which points to the current instruction being read.

So when we say `m`, we're talking about the **address** of the memory pointer,
and when we say `*m`, we're talking about the **byte at the address** of the pointer.

Likewise `p` is the address of the instruction pointer, not to be confused with the instruction itself.

The instruction set is as follows:

`>` - Move `m` forward 1.

`<` - Move `m` backward 1.

`+` - Increment the byte `*m`.

`-` - Decrement the byte `*m`.

`.` - Output (print, generally) the byte `*m`.

`,` - Input a byte and set `*m` to it.

`[` - If `*m` is zero, jump `p` to the instruction after the matching `]`.

`]` - If `*m` is nonzero, jump `p` to the instruction after the matching `[`.

Any characters other than the above eight are ignored.

## Build

`clone https://github.com/DavidHargat/Brainfuck-C`

`gcc main.c -o bf`

## Usage

`./bf <filename>`

Try running the helloworld program (taken from the wiki) with `./bf helloworld.bf`.

## Dependencies

gcc - https://gcc.gnu.org/

