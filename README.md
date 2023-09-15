# sliding-tile

[![license: MIT](https://img.shields.io/github/license/ujan-r/sliding-tile)](https://github.com/ujan-r/sliding-tile/blob/main/LICENSE)

A C implementation of the [sliding tile puzzle](https://en.wikipedia.org/wiki/15_puzzle)
in the terminal

## Installation


### With `GNU make` (recommended)
To build the executable, clone this repository and run:

```sh
make
```

To install it to the default path (/usr/local/bin/), run:

```sh
make install
```

### Without make

Use a `C99` compiler to build an executable with the source files in the
`src/` directory. Be sure to add `.` to your include search path and
link with the `curses` library.

For example, with `clang`:

```sh
cc -I. src/*.c -o sliding-tile -lcurses
```
