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
  
  cd(&filesystem, "chipmunk");
  /*chipmunk directory content*/
  touch(&filesystem, "kiwi");
  mkdir(&filesystem, "papaya");
  mkdir(&filesystem, "pear");
  touch(&filesystem, "orange");

  cd(&filesystem, ".."); /*goes back to root*/
  cd(&filesystem, "platypus");
  /*platypus content*/
  touch(&filesystem, "apple");
  mkdir(&filesystem, "grape");
  mkdir(&filesystem, "banana");
  touch(&filesystem, "cherry");

  /*grape inside platypus inside root*/
  cd(&filesystem, "grape");

  /*content of grape*/
  mkdir(&filesystem, "blue");
  touch(&filesystem, "green");
  mkdir(&filesystem, "purple");
  touch(&filesystem, "yellow");
  touch(&filesystem, "white");
  mkdir(&filesystem, "red");

  /*inside red inside grape inside Platypus inside root*/
  cd(&filesystem, "red");
  pwd(&filesystem);
  /*should be /platypus/grape/red*/
  printf("\n");
  printf("\n");

  /*goes to grape*/
  cd(&filesystem, "..");
  pwd(&filesystem);
  /* prints /platypus/grape*/
  printf("\n");
  ls(&filesystem, "");
  /* print content of grape*/
  /*blue/
    green
    purple/
    red/
    white
    yellow
*/
  printf("\n");
  printf("\n");

  /*goes to platypus*/
  cd(&filesystem, "..");
  pwd(&filesystem);
  /*  /platypus */
  printf("\n");
  ls(&filesystem, "");
  /*apple
    banana/
    cherry
    grape/ */
  printf("\n");
  printf("\n");

  /*goes to root8*/
  cd(&filesystem, "..");
  pwd(&filesystem);
  /* will just print / */
  printf("\n");

  /*print content in root*/
  ls(&filesystem, "");
  /*  chipmunk/
      orange
      papaya
      pear
      platypus/
    */
  printf("\n");
  printf("\n");

  ls(&filesystem, "chipmunk");

  /* kiwi
     orange
     papaya/
     pear/
     */
  return 0;
}
