#include <stdio.h>
#include "unix.h"
#include "driver.h"

/* CMSC 216, Fall 2019, Project #9
 * Public test 1 (public01.c)
 *
 * Tests that the revised form of the \texttt{pwd()} function prints the
 * full pathname of the current directory.  Note that this test uses the
 * driver.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  driver(&filesystem);

  return 0;
}
