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
  
  cd(&filesystem, "chipmunk");

  touch(&filesystem, "kiwi");
  mkdir(&filesystem, "papaya");
  mkdir(&filesystem, "pear");
  touch(&filesystem, "orange");

  cd(&filesystem, "..");
  cd(&filesystem, "platypus");

  touch(&filesystem, "apple");
  mkdir(&filesystem, "grape");
  mkdir(&filesystem, "banana");
  touch(&filesystem, "cherry");

  cd(&filesystem, "grape");

  mkdir(&filesystem, "blue");
  touch(&filesystem, "green");
  mkdir(&filesystem, "purple");
  touch(&filesystem, "yellow");
  touch(&filesystem, "white");
  mkdir(&filesystem, "red");

  assert(rm(&filesystem, "red") == 1);

  cd(&filesystem, "..");
  assert(rm(&filesystem, "grape") == 1);

  cd(&filesystem, "..");
  assert(rm(&filesystem, "chipmunk") == 1);;

  ls(&filesystem, "");
  /*
    orange
    papaya
    pear
    platypus/
  */

  ls(&filesystem, "platypus");
  /*
    apple
    banana/
    cherry
  */

  cd(&filesystem, "platypus");
  ls(&filesystem, "banana");
  /* */

  rmfs(&filesystem);

  return 1;
}
