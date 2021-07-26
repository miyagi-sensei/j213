#!/bin/bash

# solution.cpp/sol.py   solution you want to stress test
# verify.cpp/verify.py  brute force verifier for the problem
# gen.py                generates a new random test case for the problem

# compile all programs first
g++ v3.cpp
g++ verify.cpp -o verify
# g++ gen.cpp -o gen

for ((i = 1; ;i++)) do
  # generate a new test case in the file named "in"
  # note that we pass i as a random seed to the generator
  python3 gen.py > in
  # redirect the solution output to the "out" file
  # python3 sol.py < in > out
  ./a.out < in > out
  # concatenate the input and output to the "inout" file
  cat in out > inout

  # verify that the solution generates the correct output.
  # if verifier terminates without error, echo the 
  # corresponding message and break the loop.
  # failing test will be in the "in" file.
  if ! ./verify < inout
  then
    echo 'Found failing test!'
    break
  fi

  # if outputs are the same, we echo "OK".
  # this is optional, but helps to see the progress of stress testing.
  echo 'OK'
done