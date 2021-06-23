
#ifndef FILE_HELPER
#define FILE_HELPER

#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#define SD_PROFILE_LOCATION "./Firmware/Profiles"
char SD_PROFILE_DIR[100];

#define USB_PROFILE_DIR "./USB_Drive/Profiles"
#define MAX_FILE_ENTRIES 50
#define MAX_NUM_FILES 50

#define POPEN_READ                   "re"  // "r" opens for reading, "e" sets close on exec flag ("FD_CLOEXEC")
#define POPEN_WRITE                   "w"  // "r" opens for reading, "e" sets close on exec flag ("FD_CLOEXEC")


/*
|--------------------------------------------------------------------------
| Shell_List_Files
|--------------------------------------------------------------------------
|
| List the files in the directory given by path. Only "regular" files are
| returned. Folders are not returned
|
| @param:   path    the path to the directory whose files are listed
| @return:          a pointer to a list of strings, each string is a file in the directory
*/
char** Shell_List_Files(char* path)
{
  unsigned char filetype;
  struct dirent *directory_entry;   // Pointer for directory entry
  DIR *directory = opendir(path);   // opendir() returns a pointer of DIR type.

  if (directory == NULL)  // opendir returns NULL if couldn't open directory
  {
      printf("Could not open directory: %s\n", path);
      return 0;
  }

  char** file_list = (char**)malloc(sizeof(char*) * MAX_NUM_FILES );
  int file_index = 0;

  file_list[ file_index ] = (char*)malloc(sizeof(char*) * ( strlen(path) +1 ) ); // allocate memory for filepath string
  strcpy(file_list[file_index], path);
  ++file_index;

  while ((directory_entry = readdir(directory)) != NULL)
  {
      filetype = directory_entry->d_type;
      if(filetype == DT_REG)
      {
            file_list[ file_index ] = (char*)malloc(sizeof(char*) * ( strlen(directory_entry->d_name) +2 ) ); // allocate memory for file string
            strcpy( file_list[file_index], directory_entry->d_name);
            ++file_index;
      }
  }
  file_list[ file_index ] = NULL;

  closedir(directory);
  return file_list;
}

/*
|--------------------------------------------------------------------------
| Shell_List_Folders
|--------------------------------------------------------------------------
|
| List all regular folders in the directory given in the argument path.
| Hidden folders are not included. (folders beginning with a '.')
|
| @param:     path         filepath to directory whose folders are listed
| @return:                 a pointer to a list of strings, each string is a folder in the directory
*/
char* Shell_List_Folders(char* path)
{
  unsigned char filetype;
  struct dirent *directory_entry;   // Pointer for directory entry
  DIR *directory = opendir(path);   // opendir() returns a pointer of DIR type.

  if (directory == NULL)  // opendir returns NULL if couldn't open directory
  {
      printf("Could not open directory: %s\n", path);
      return 0;
  }

  printf("\nLIST FOLDERS:\n");
  printf("------------------------------------------------------------------------------\n");
  printf("ls %s\n", path);
  while ((directory_entry = readdir(directory)) != NULL)
  {
      filetype = directory_entry->d_type;
      if(filetype == DT_DIR)
      {
          if(directory_entry->d_name[0] != '.' && directory_entry->d_name[1] != '.')
            printf(COLOR_LIGHT_BLUE "\t%s\n" COLOR_RESET, directory_entry->d_name);
      }
  }
  printf("------------------------------------------------------------------------------\n");

  closedir(directory);
  return 0;
}

/*
|--------------------------------------------------------------------------
| Shell_List_Hidden_Folders
|--------------------------------------------------------------------------
|
| List all hidden folders in the directory given in the argument path.
| Hidden folders are folders beginning with a '.'
|
| @param:     path         filepath to directory whose hidden folders are listed
| @return:                 a pointer to a list of strings, each string is a folder in the directory
*/
char* Shell_List_Hidden_Folders(char* path)
{
  unsigned char filetype;
  struct dirent *directory_entry;   // Pointer for directory entry
  DIR *directory = opendir(path);   // opendir() returns a pointer of DIR type.

  if (directory == NULL)  // opendir returns NULL if couldn't open directory
  {
      printf("Could not open directory: %s\n", path);
      return 0;
  }

  printf("\nLIST HIDDEN FOLDERS:\n");
  printf("------------------------------------------------------------------------------\n");
  printf("ls %s\n", path);
  while ((directory_entry = readdir(directory)) != NULL)
  {
      filetype = directory_entry->d_type;
      if(filetype == DT_DIR)
      {
          if(directory_entry->d_name[0] == '.' && strlen(directory_entry->d_name)>1 && directory_entry->d_name[1] != '.')
              printf(COLOR_LIGHT_BLUE "\t%s\n" COLOR_RESET, directory_entry->d_name);
      }
  }
  printf("------------------------------------------------------------------------------\n");

  closedir(directory);
  return 0;
}






#endif
