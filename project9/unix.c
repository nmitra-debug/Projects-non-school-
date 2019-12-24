/*
 * Name: Nistha Mitra
 * University directory ID: nmitra28
 * University ID number: 116274555
 * TerpConnect loginID: nmitra28
 * Discussion section number: 0107
 *  
 * I pledge on my honor that I have not given or received any unauthorized
 * assistance on this assignment.
 */

/*This program is recreating a unix system. It is not entirely
  the same in terms of properties but quite similar.

  You can make a Directory which can have as many subdirectories 
  or files as one wants and till the time heap is not full.

  Subdirectories have the same propertry as it's parent directory
  and can cantain it's own sub directories and files.

  The difference between this project and project8 is that you can 
  delete the entire system or a file or a subdirectories

  Refer to unix-datastructure.h where we see that the subdirectories
  or files of a directory is linked togethor and makes it easy
  to traverse through them.

  The functions
  (mkfs(), touch(), mkdir(), ls(), cd(), pwd(), rmfs(), rm())

  are describes below giving more details about the 
  operations that can be carried out.
*/
#include "unix.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

/*initializing the Unix system. Allocating size for the first
  Directory and it's name. The current directory and the root
  are pointing to the same one initially*/
void printhelper(Dir *directory);
void helperremove(Dir *current);
int exists (Dir *current, const char arg[]);

void mkfs (Unix *filesystem)
{
  /*root file of the system is the first directory.
    Refer to the unix-datastructure.h file.*/
  if (filesystem != NULL) {
    filesystem->root= malloc(sizeof(Dir));
    filesystem->root->name= malloc(sizeof(char)*2);
    if(filesystem->root->name)
      strcpy(filesystem->root->name,"/");
    filesystem->root->sub=NULL;
    filesystem->root->Parent=filesystem->root;
    filesystem->root->next=NULL;
    filesystem->root->file=NULL;
    filesystem->curr=filesystem->root;
  }
  
}

/*touch() function adds file if it already doesn't 
  exist. It creates a new file in the current directory.*/
int touch (Unix *filesystem, const char arg[])
{
  File  *curr = NULL, *prev= NULL, *new_item= NULL;
  int result= 0;
  if (filesystem != NULL && arg != NULL) {
    if ((strchr(arg,'/') == NULL && strlen(arg) != 0) || strcmp("/", arg) == 0)
      {

	/*checking special cases*/
	if (strcmp(arg,".") == 0 || strcmp(arg,"..") == 0 ||
	    strcmp(arg,"/") == 0 || strcmp(arg,"") == 0) {
	  result = 1;
	}
	/*checking error cases*/
	else if ((strlen(arg) > 1 && strchr(arg, '/') != NULL)) {
	  result = 0;
	} 
		
	else
	  {
	    if(!exists(filesystem->curr, arg))
	      {
		/*going through current directory's files.*/
		curr = filesystem -> curr -> file;

		/*if this is the first one being added make new as 
		  first*/
		if (curr == NULL) {
		  curr = malloc(sizeof(File));
		  curr -> name = malloc(sizeof(arg) * (strlen(arg) + 1));
		  strcpy(curr -> name, arg);
		  curr -> next = NULL;
		  filesystem -> curr -> file = curr;
		} 
		
		else {
		  while (curr != NULL && strcmp(curr->name,arg) < 0) {
		    prev= curr;
		    curr= curr->next;
		  }

		  /* create new node and if memory allocation succeeded fill in its
		     fields */
		  if (curr == NULL) {
		    new_item= malloc(sizeof(*new_item)); 
		    if (new_item != NULL) {
		      new_item->name = malloc(sizeof(arg) * (strlen(arg) + 1));
		      strcpy (new_item->name,arg);
		      new_item->next= curr;
		    }
		    prev -> next = new_item;
		  } else if(strcmp(curr->name,arg) != 0)
		    {
		      new_item= malloc(sizeof(*new_item)); 
		      if (new_item != NULL) {
			new_item->name = malloc(sizeof(arg) * (strlen(arg) + 1));
			strcpy (new_item->name,arg);
			new_item->next= curr;
		      }

		      if (prev == NULL)
			filesystem->curr->file= new_item;  /* special case- 
						      inserting new first element */
		      else 
			prev->next= new_item;  /* general case- inserting elsewhere */
		    }
		}
		result= 1;
	      }
	  }
      }
  }
  return result;
}





/*mkdir() function adds file if it already doesn't 
  exist. It creates a new sub-directory in the current directory.*/
int mkdir(Unix *filesystem, const char arg[])
{
  Dir  *curr = NULL, *prev= NULL, *new_item= NULL;
  int result= 0;

  if (filesystem != NULL && arg != NULL) {
    if (strchr(arg,'/') == NULL || strlen(arg) > 1)
      {

	if (strcmp(arg,".") == 0 || strcmp(arg,"..") == 0 || strcmp(arg,"/") == 0 ||
	    strcmp(arg,"") == 0 ||(strlen(arg) > 1 && strchr(arg, '/') != NULL)) {

	}
	else
	  {
	    if (!exists(filesystem->curr, arg))
	      {
		/* find first node in list that's greater than or equal to the one we
		   want to insert */
		curr = filesystem -> curr -> sub;
		if (curr == NULL) {
		  curr = malloc(sizeof(Dir));
		  curr -> name = malloc(sizeof(arg) * (strlen(arg) + 1));
		  strcpy(curr -> name, arg);
		  curr -> next = NULL;
		  filesystem -> curr -> sub = curr;
		  filesystem -> curr -> sub -> Parent = filesystem -> curr;
		  filesystem -> curr -> sub->file=NULL;
		  filesystem -> curr -> sub->sub=NULL;
	     
		} else {
		  while (curr != NULL && strcmp(curr->name,arg) < 0) {
		    prev= curr;
		    curr= curr->next;
		  }

		  /* create new node and if memory allocation succeeded fill in its
		     fields */
		  new_item= malloc(sizeof(*new_item)); 
		  if (new_item != NULL) {
		    new_item->name = malloc(sizeof(*(new_item->name))*(strlen(arg)+1));
		    strcpy (new_item->name,arg);
		    new_item->next= curr;
		    new_item->Parent= filesystem -> curr;
		    new_item->file=NULL;
		    new_item->sub=NULL;
		  }
		
		  if (curr == NULL) {
	
		    curr = new_item;
		    prev -> next = curr;
	       
		  }

		  else if(strcmp(curr->name,arg) != 0)
		    {
		      if (prev == NULL)
			filesystem->curr->sub= new_item;  /* special case- 
							inserting new first element */
		      else 
			prev->next= new_item;  /* general case- inserting elsewhere */

		    }
		}
		result=1;
	    
	      }
	  }
      }
  }
  
  return result;
}

/*ls() function lists the subdirectory and files
  of current sirectory or files and subdirectories
  of the argument or arg name if it is a file*/
int ls(Unix *filesystem, const char arg[])
{
  Dir *currsub = NULL;
  File *currfile = NULL;
  
  int ret =0;

  if (filesystem != NULL && arg != NULL)
    {
      /*special cases*/
      if (strcmp(arg,"..") == 0)
	{
	  
	  printhelper(filesystem->curr->Parent);
	  ret=1;
        
	}

      else if (strcmp(arg,"") == 0 || strcmp(arg,".") == 0)
	{
	  printhelper(filesystem->curr);
	  ret=1;
	}
	
      else if(strcmp(arg,"/") == 0)
	{
	  printhelper(filesystem->root);
	  ret=1;
	}

      else
	{
	 
	  currsub= filesystem->curr->sub;
	  currfile= filesystem->curr->file;
	  if (currsub != NULL && currfile != NULL) {

	    /*checking it see if arg is a file*/
	    while (currfile != NULL)
	      {
		if (strcmp(currfile->name,arg) == 0)
		  {
		    printf("%s\n",currfile->name);
		    ret =1;
		  }
		currfile=currfile->next;
	
	      }

	    /*checking it see if arg is a subdir*/
	    while (currsub != NULL)
	      {
	     
		if (strcmp(currsub->name,arg) == 0)
		  {
		    printhelper(currsub);
		    ret=1;
		  }
		currsub=currsub->next;
	      }
	  }
	}

    }
  return ret;
}

/*changes the current directory according to the 
  argument sent*/
int cd(Unix *filesystem, const char arg[])
{
  Dir *subcurr = NULL;
  int ret =0;
  if (filesystem != NULL && arg != NULL)
    {
      subcurr = filesystem->curr->sub;
      if (strcmp(arg,"..") == 0)
	{
	  filesystem->curr=filesystem->curr->Parent;
	  ret =1;
	}

      /*has no effects because current directory remains the same*/
      else if (strcmp(arg,".") == 0 || strcmp(arg,"") == 0)
	{
	  ret =1;
	}

      /*The root directory becomes the current directory*/
      else if (strcmp(arg,"/") == 0)
	{
	  filesystem->curr=filesystem->root;
	  ret =1;
	}

      /*looking for the directory name arg in current
	directory*/
      else
	{
	  while (subcurr != NULL && !ret)
	    {
	      if(strcmp(subcurr->name,arg) == 0)
		{
		  filesystem->curr=subcurr;
		  ret =1;
		} else 
		{
		  subcurr=subcurr->next;
		}
		
	    }
	}
    }
  return ret;
  
}

/*My datastructure has pointer up to parent
  so I save the current name in a temperory variable
  and add the previously stored path such that the 
  Parent is stored first in the string. Thereafter I store
  the modified path to the current path and free the
  temperory variable. Does this till you reach root. */
void pwd(Unix *filesystem)
{
  Dir *currpoint = filesystem->curr;
  char *path =NULL;
  char *temperory =NULL;
  /* if current directory is not root that is / */
  if (currpoint != filesystem->root)
    {

      path= malloc((strlen("")+1)*sizeof(char));
      strcpy(path,"");
      while (currpoint != filesystem->root)
	{
	  temperory= malloc((strlen(currpoint->name)+strlen(path)+2)*sizeof(char));
	  if(temperory)
	    {
	      strcpy(temperory,"/");
	      strcat(temperory,currpoint->name);
	      strcat(temperory,path);
	      path= realloc(path,(strlen(currpoint->name)+strlen(path)+2)
			    *sizeof(char));
	      strcpy(path,temperory);
	      free(temperory);
	    }
	  currpoint=currpoint->Parent;
	}
      printf("%s\n",path);
      free(path);
    }
  /* if current directory is root just print /*/
  else
    {
      printf("%c\n",'/');
    }
}

/*removes the entire system*/
void rmfs(Unix *filesystem)
{
  if(filesystem != NULL)
    {
      helperremove(filesystem->root);
    }
}

/* send in a directory and then delete 
   all files and recursively remove the sub directories*/
void helperremove(Dir *current)
{
  Dir *sub= current->sub;
  File *file= current->file;
  File *tempf=NULL;
  Dir *tempd=NULL;
  if(current!=NULL)
    {
     
      /*removing files*/
      while (file != NULL)
	{
	  tempf=file;
	  file=file->next;
	  free(tempf->name);
	  free(tempf);
	}

      /*removing sub-directories*/
      while (sub != NULL)
	{
	  tempd=sub;
	  sub=sub->next;
	  helperremove(tempd);
	}
      free(current->name);
      free(current);
    }
}

/*removing a particular file or directory. 
If arg is the name of a file, then find it and remove it
If arg is the name of a directory, pass it to helperremove()
*/
int rm(Unix *filesystem, const char arg[])
{
  Dir *subcurr=NULL, *tempd, *prevsub;
  File *currfile=NULL;
  File *tempf, *prev;
  int ret=0;
  if (strcmp(arg,".") == 0 || strcmp(arg,"..") == 0 || strcmp(arg,"/") == 0 || strcmp(arg,"") == 0 ||
      (strlen(arg) > 1 && strchr(arg, '/') != NULL) || !exists(filesystem->curr,arg));
  else
    {
      if (filesystem != NULL && arg != NULL)
	{
	  
	  /*if arg is subdirectory*/
	  subcurr = filesystem->curr->sub;
	  prevsub = subcurr;
	  while (subcurr != NULL && !ret)
	    {
	      if (strcmp(subcurr->name,arg) == 0)
		{
		  if(subcurr== filesystem->curr->sub)
		    filesystem->curr->sub=subcurr->next;
		  tempd=subcurr;
		  subcurr=subcurr->next;
		  helperremove(tempd);
		  prevsub->next=subcurr;	    
		  ret =1;
		} else 
		{
		  prevsub=subcurr;
		  subcurr=subcurr->next;
		}	
	    }

	  /*if arg is same of a file*/
	  currfile=filesystem->curr->file;
	  prev=currfile;
	  while (currfile != NULL && !ret)
	    {
	      if (strcmp(currfile->name,arg) == 0)
		{
		  if (currfile == filesystem->curr->file)
		    filesystem->curr->file=currfile->next;
		  tempf=currfile;
		  currfile=currfile->next;
		  prev->next=currfile;
		  free(tempf->name);
		  free(tempf);
		  ret =1;
		}
	      else 
		{
		  prev=currfile;
		  currfile=currfile->next;
		}	
	    }
	  
	}
    }
  return ret;
}

void printhelper(Dir *directory)
{
  Dir *currsubsub= directory->sub;
  File *currsubfile= directory->file;
  while (currsubsub != NULL && currsubfile != NULL) 
    {
      /*comparing the lements of the files and subdirectory
	of the current directory lexicographically.

	Note that it prints till one of the list reached NULL*/
      if (strcmp(currsubsub->name,currsubfile->name) < 0)
	{
			    
	  printf("%s/\n",currsubsub->name);
	  currsubsub=currsubsub->next;
	}
      else
	{
	  printf("%s\n",currsubfile->name);
	  currsubfile=currsubfile->next;
	}
	    
    }

  /*After printing till the end of one of the list
    it print the rest of the elements in the non empty list */
  if (currsubsub != NULL)
    {
      while (currsubsub != NULL)
	{
	  printf("%s/\n",currsubsub->name);
	  currsubsub=currsubsub->next;
	}
    }

  else if (currsubfile != NULL)
    {
      while (currsubfile != NULL)
	{
	  printf("%s\n",currsubfile->name);
	  currsubfile=currsubfile->next;
	}
    }
}

/*checks whether arg passed is the name of a file or
  subdirectory in the current directory*/
int exists (Dir *current, const char arg[])
{
  File *currentfile=current->file;
  Dir  *currentsub=current->sub;
  int ret=0;

  /* exists as a file*/
  while (currentfile != NULL) {

    if( strcmp(currentfile->name,arg) == 0)
      ret=1;
    currentfile=currentfile->next;
  }

  /* exists as a subdirectory*/
  while (currentsub != NULL) {

    if( strcmp(currentsub->name,arg) == 0)
      ret=1;
    currentsub=currentsub->next;
  }
  return ret;
}


