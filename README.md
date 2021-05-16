# Qwirkle

A strange game. The only winning move is not to play.

## Authors

- Martin Krisnanto Putra (GrygrFlzr)
  <s3608646@student.rmit.edu.au>
- Riley James Gozzard (qponfqhen)
  <s3811315@student.rmit.edu.au>
- Ryan Iem (s3700995)
  <s3700995@student.rmit.edu.au>
- Thomas Joseph Dib (s3838765)
  <s3838765@student.rmit.edu.au>

## Tests
Tests (`.input` files) are designed to be executed from the tests/ folder.
Make sure to use `cd tests/` before using these tests as the savegame files
are relative to this directory. For example:
`cd tests`, `../qwirkle < 1-newgame-static.input`
will execute the first test.

Any tests labelled with static should use a static seed (meaning the generated tiles will be scrambled in the same order). This can be changed within the `bag.cpp` file in the `scrambleTiles()` method. By default, tiles will be randomly scrambled, however if the scrambling should be static, the line consisting of a `std::default_random_engine` should be uncommented, and the seed that has been used within the static tests is the integer 1. Any value besides this will not work.