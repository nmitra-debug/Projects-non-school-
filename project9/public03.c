#include <stdio.h>
#include "unix.h"
#include "memory-checking.h"

/* CMSC 216, Fall 2019, Project #9
 * Public test 3 (public03.c)
 *
 * Tests calling rmfs() on a filesystem that only contains files (in the
 * root directory), ensuring that memory is released and the heap is valid.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  #if !defined(ENABLE_VALGRIND)
  setup_memory_checking();
  #endif

  mkfs(&filesystem);

  touch(&filesystem, "chipmunk");
  touch(&filesystem, "platypus");
  touch(&filesystem, "numbat");
  touch(&filesystem, "quokka");
  touch(&filesystem, "koala");

  ls(&filesystem, ".");

  /* now trash the whole thing */
  rmfs(&filesystem);

  #if !defined(ENABLE_VALGRIND)
  check_heap();
  #endif

  /* if this is the only thing printed the heap must be valid, and there
   * must not have been any memory leaks
   */
  printf("\nEverything in the heap looks valid!\n");

  return 0;
}
