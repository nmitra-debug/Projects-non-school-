#include <stdio.h>
#include <assert.h>
#include "unix.h"

/* Tests pwd() in interesting ways... */
int main() {
  Unix filesystem;
  mkfs(&filesystem);

  mkdir(&filesystem, "chipmunk");
  touch(&filesystem, "pear");
  mkdir(&filesystem, "platypus");
  touch(&filesystem, "papaya");
  touch(&filesystem, "orange");
  ls(&filesystem, "");

   /* now trash the whole thing */
  /* rmfs(&filesystem);*/

  rm(&filesystem, "chipmunk");
  rm(&filesystem, "pear");
  ls(&filesystem, "");

  rmfs(&filesystem);

  return 1; 
}
