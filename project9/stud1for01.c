#include <stdio.h>
#include "unix.h"
#include "driver.h"

/* CMSC 216, Fall 2019, Project #9
 * Student test for Public test 1 (public01.c)
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  driver(&filesystem);

  return 0;
}
