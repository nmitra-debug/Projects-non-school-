 typedef struct file
 {
   struct file *next;
   char *name;
 } File;

typedef struct dir
{
  struct dir *sub;
  struct dir *Parent;
  struct dir *next;
  char *name;
  File *file;
} Dir;

typedef struct unix
{
  Dir *root;
  Dir *curr;
} Unix;
  
