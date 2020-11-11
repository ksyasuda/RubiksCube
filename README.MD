# Rubik's cube solver (C++)

A command-line application capable of creating, scrambling, and solving a
Rubik's Cube.

On my laptop, an old Asus Zenbook UX303UA, it can go through 1,000,000
twenty-five move scrambles and solves in about 10 seconds.

## Installation/Compilation

You must have `make` and `gcc` installed to build the program.

Run the following commands to get a copy of the source code, move into the newly
cloned RubiksCube directory, and compile the program.

```sh
git clone https://github.com/ksyasuda/RubiksCube.git
cd RubiksCube
make
```

## Usage

To run the program run `./rcube` in the terminal and you will be greeted by a 
text-based user interface .

You can also run the program in 'debug' mode by adding the `--debug` flag to
the run command.  This mode bypasses the usual user interface and allows for any
number of successive solves with 3 options for delay.
