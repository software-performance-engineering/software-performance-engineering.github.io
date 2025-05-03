/**
 * Copyright (c) 2020 MIT License by 6.172 Staff
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 **/

// Solve the n-queens problem.  The single command-line argument is
// the number of queens.  The code was written by Charles E. Leiserson
// in 2016, but it was heavily inspired by Tony Lezard's original code
// from 1991:

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>  // for atoi()

int32_t queens(uint32_t mask, uint32_t down, uint32_t left, uint32_t right) {
  int32_t possible, place;
  int32_t count = 0;
  // printf("%d %d %d %d\n", mask, down, left, right);
  if (down == mask)
    return 1;
  for (possible = ~(down | left | right) & mask; possible != 0;
       possible &= ~place) {
    place = possible & -possible;
    count += queens(mask, down | place, ((left | place) << 1) & mask,
                    (right | place) >> 1);
  }
  return count;
}

int main(int argc, char* argv[]) {
  // argc should be 2 for correct execution
  if (argc != 2) {
    // Assume that argv[0] is the program name
    printf("Usage: %s <integer number of queens>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int n = atoi(argv[1]);
  if ((n <= 0) || (n > 32)) {
    printf("Number of queens must be > 0 and <= 32.\n");
    exit(EXIT_FAILURE);
  }
  printf("The %d-queens problem has %d solutions.\n", n,
         queens((1 << n) - 1, 0, 0, 0));
  exit(EXIT_SUCCESS);
}
