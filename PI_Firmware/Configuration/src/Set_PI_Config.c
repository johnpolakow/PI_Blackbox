

//  sudo raspi-config nonint do_change_locale en_US.UTF-8
//  sudo raspi-config nonint do_configure_keyboard us


/*
Verify Timezone:
/etc/timezone  contains: "America/Los_Angeles"
if not then:
echo "America/Los_Angeles" > /etc/timezone
dpkg-reconfigure -f noninteractive tzdata

Verify locale
cp /etc/locale.gen /etc/locale.gen.dist
sed -i -e "/^[^#]/s/^/#/" -e "/en_US.UTF-8/s/^#//" /etc/locale.gen

cp /var/cache/debconf/config.dat /var/cache/debconf/config.dat.dist
sed -i -e "/^Value: en_GB.UTF-8/s/en_GB/en_US/" \
       -e "/^ locales = en_GB.UTF-8/s/en_GB/en_US/" /var/cache/debconf/config.dat
locale-gen
update-locale LANG=en_US.UTF-8
///////////

// make copy of all files modified for easy revert to defaults




Something with SSH:
# update-rc.d ssh enable && invoke-rc.d ssh start
# rm -f -v /etc/ssh/ssh_host_*_key*
# /usr/bin/ssh-keygen -A -v
*/
// add firmware version number to config file
// read /dev/ folder and verify proper devices exist
//parse config file
// check and store:
/*
HOSTNAME
eth0_IP
network ADDRESS
subnet
hub ip#
update-rc.d ssh enable && invoke-rc.d ssh start
# dd if=/dev/hwrng of=/dev/urandom count=1 bs=4096
# rm -f -v /etc/ssh/ssh_host_*_key*
# /usr/bin/ssh-keygen -A -v
PCB revision level
usb folder location
log file suffix
hub log store
profile folder locations
environment variables
    hostname
    socket
    hub ip
    cal file location
    firmware version
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include "Aliases.h"
#include "colors.h"
#include "network.h"


#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>


//#define NEW_USERNAME                  "sapien"
//#define NEW_PASSWORD                  "blackberry"

#define DEFAULT_PASSWORD              "raspberry"
#define DEFAULT_USERNAME              "pi"

#define BACKUP_FILE_SUFFIX            ".pi_original"

#define SHELL_CMD_GET_HOSTNAME        "raspi-config nonint get_hostname"
#define SHELL_CMD_SET_HOSTNAME        "sudo raspi-config nonint do_hostname "

#define SHELL_CMD_GET_SSH             "sudo raspi-config nonint get_ssh"    // If SSH is set this command returns 0
#define SHELL_CMD_SET_SSH             "sudo raspi-config nonint do_ssh "    // Add argument of 0 to enable SSH

#define POPEN_READ                   "re"  // "r" opens for reading, "e" sets close on exec flag ("FD_CLOEXEC")
#define POPEN_WRITE                   "w"  // "r" opens for reading, "e" sets close on exec flag ("FD_CLOEXEC")

#define DEGREE_SYMBOL                 "°"
#define CHECKMARK_CHARACTER           "\033[01;32m\xE2\x9C\x94\x1b[0m"
#define CROSS_CHARACTER               "\033[01;31m\xE2\x9D\x8C\x1b[0m"

#define SHELL_CMD_LIST_BOOT_FILES     "sudo /bin/ls /boot 2>&1"
#define SHELL_CMD_CAT_CONFIG_FILE     "sudo /bin/cat /boot/config.txt 2>&1"
#define SHELL_CMD_CLEAR               "clear"
#define SHELL_CMD_SET_KEYBOARD        "sed -i -e '/XKBLAYOUT=/s/[a-z][a-z]/us/' /etc/default/keyboard"
#define SHELL_CMD_RESTART_KBD_SERIVCE "sudo service keyboard-setup restart"
#define FILE_PI_HARDWARE_CONFIG       "/boot/config.txt"
#define FILE_BOOTLOG                  "~/firmware/bootlog.txt"




struct Disk_Usage{
		char kernel_location[30];
    char filesystem[20];
    char total_space[10];
		char used_space[10];
    char free_space[10];
    char mount_location[100];
    char percent_filled[20];
    int percent_disk_filled;
};

struct Disk_Usage uSD_Card;                      // root filesystem stored on micro SD card
struct Disk_Usage Flash_Drive;

#define ENV_VAR_USER      "USER"
#define ENV_VAR_HOME      "HOME"
#define ENV_VAR_HOSTNAME  "(hostname)"

//----------------------------------------------
// PRIMARY FUNCTION DECLARATIONS

void Add_User(char* NEW_USERNAME);
void Backup_File(char* filepath);
void Create_Aliases_File();
char** Exec_Shell_Command(char* command);
void Expand_FileSystem();
void Enable_Autologin_For_User(char* USERNAME);
void Free_String_Array_Memory(char** string_array);
char* Get_Environment_Variable_Value(char* env_variable);
void  Get_Environment_Variables();
char* Get_Keyboard_Layout();
char* Get_Hostname();
void Get_Disk_Usage();
double Get_CPU_Temp();
char** Install_Software_Packages(char* software_list_filepath);
char** List_Users();
void Print_Users();
void Print_String_Array(char** string_array);
void Reboot_PI();
void Remove_User(char* USERNAME);
void Set_Hostname(char* hostname);
bool Verify_Boot_File_Config();
bool Set_Boot_File_Config();
bool Verify_SSH_Enabled();
void Set_SSH_Enabled();
void Set_US_Keyboard_Layout();
char* Shell_List_Files(char* filepath);
char* Shell_List_Folders(char* filepath);
char* Shell_List_Hidden_Folders(char* path);
void Set_Network_Configuration(char* eth0_IP);
void Set_User_Password(char* USERNAME, char* NEW_PASSWORD);
void Set_Wallpaper(char* wallpaper_filepath);


//-----------------------------------------------------
//  HELPER FUNCTIONS

void Backup_System_Files();
void  Echo_Env_Variable(char* variable, char* value);
void Enable_Sudo_No_Password_For_User(char* USERNAME);
void Enable_Desktop_Autologin(char* USERNAME);
void Enable_Console_Autologin(char* USERNAME);
void Erase_String_Contents(char* string);
void ExtractUserName(char* long_user_string);
void Get_Desktop_Autologin_File_Entry(char* get_line);
void Get_Desktop_Autologin_User(char* get_user);
void Get_Console_Autologin_User(char* get_user);
void Get_Console_Autologin_File_Entry(char* get_line);
char* Get_Substring(char* full_string, int start_index, int end_index);
char* Get_File_Suffix(char* filepath);
void Parse_Disk_Use(char* console_line, struct Disk_Usage* device);
char* Parse_KBD_Country_Code(char* read_line);
double parseDouble(char* integer_string);
int parseInt(char* integer_string);
char** Parse_Package_List(char*  software_list_filepath );
char** parseUsers(char** long_user_list, int uid_min, int uid_max);
void Print_Aliases();
bool Search_String_in_File(char *filename, char *match_string);
bool String_Equals_String(char* target_string, char* input_string);
bool String_Contains(char* base_string, char* match_string);
bool String_List_Contains(char** string_list, char* string_to_match);
void Trim_Trailing_WhiteSpace(char * str);
void Trim_Leading_WhiteSpace(char* str);
bool Verify_File_Exists(char* filepath);



//--------------------------------------------------------------
//  NEED TO DO
char* Get_TimeZone();
void Set_TimeZone(char* timezone);
bool Set_Locale();
bool Set_eth0_IP_Address(char* ip);
void Parse_Config_File();

///////////-----------------------------------------------------


char* USER;
char* HOME_FOLDER;
char* HOSTNAME;

int main( int argc, char *argv[] )
{

  FILE *file_pointer;
  char path[1035];
  bool boot_config = false;
  bool SSH_enabled = false;

  printf("\n");


	Install_Software_Packages("./package.install");
  //Exec_Shell_Command(SHELL_CMD_LIST_BOOT_FILES);
  //Exec_Shell_Command(SHELL_CMD_CAT_CONFIG_FILE);
  //Set_Hostname("PI-BB38");

  //Shell_List_Files(HOME_FOLDER);
  //Shell_List_Folders(HOME_FOLDER);
  //Shell_List_Hidden_Folders(HOME_FOLDER);
	// Get_Environment_Variables();
  Create_Aliases_File();
  printf(COLOR_BOLD_YELLOW "\nHARDWARE CONFIG " COLOR_RESET "\n\tChecking " COLOR_CYAN "/boot/config.txt " COLOR_RESET "for correct hardware overlays...\n" COLOR_RESET);
  boot_config = Verify_Boot_File_Config();
  if(boot_config)
  {
    printf("\n\t/boot/config.txt check:\t PASS ");
    printf(CHECKMARK_CHARACTER);
    printf("\n\n");
  }
  else
  {
    printf("/boot/config.txt check:\t FAIL");
    boot_config = Set_Boot_File_Config();
    printf(CROSS_CHARACTER);
  }

  SSH_enabled = Verify_SSH_Enabled();
  printf("\tSSH enabled: ");
  if(SSH_enabled)
  {
    printf("PASS \t");
    printf(CHECKMARK_CHARACTER);
    printf("\n\n");
  }
  else printf(CROSS_CHARACTER);

  printf("\tKeyboard Layout  \n");
  char* keyboard_layout = Get_Keyboard_Layout();
  printf("\t\tlayout:  " COLOR_LIGHT_MAGENTA "%s\t" COLOR_RESET, keyboard_layout);
  free(keyboard_layout);

  bool keyboard_layout_is_us = String_Equals_String(keyboard_layout, "us");
  if(keyboard_layout_is_us)
  {
      printf(CHECKMARK_CHARACTER);
      printf("\n\n");
  }

  char* hostname = Get_Hostname();
  printf(COLOR_BOLD_YELLOW "HOSTNAME: \t " COLOR_RESET COLOR_LIGHT_GREEN "%s\n" COLOR_RESET, hostname);

  Remove_User("sapien");
  Add_User("sapien");
  Add_User("pi");
  Enable_Sudo_No_Password_For_User("pi");
  Enable_Autologin_For_User("pi");

  // Set_Wallpaper("/home/pi/images/glowpi.jpg");
  // enter following command if pcmanfm doesnt restart
  // pcmanfm --desktop --profile LXDE-pi
  Backup_System_Files();

  Set_Network_Configuration("192.168.123.4");
  Get_Disk_Usage();

  double CPU_temperature = Get_CPU_Temp();
  printf(COLOR_LIGHT_RED);
  printf("CPU_TEMP:\t%.1f%sC\n", CPU_temperature, DEGREE_SYMBOL);
  printf(COLOR_RESET);
  Expand_FileSystem();
  //Reboot_PI();

  return 0;
}



char** Install_Software_Packages(char* software_list_filepath)
{
    if( !Verify_File_Exists( software_list_filepath) )
    {
        printf("Package Install List cannot be found.\t" COLOR_CYAN "%s\n" COLOR_RESET, software_list_filepath );
				return 0;
    }

		char package_update_command[] = "sudo apt-get -y update";
		char package_upgrade_command[] = "sudo apt-get -y upgrade";

		char** shell_response = Exec_Shell_Command( package_update_command );
		Print_String_Array( shell_response );
		Free_String_Array_Memory( shell_response );

		shell_response = Exec_Shell_Command( package_upgrade_command );
		Print_String_Array( shell_response );
		Free_String_Array_Memory( shell_response );


		char** packageList = Parse_Package_List( software_list_filepath );


		int package_index = 0;
		printf("\n\n");
	  while( packageList[ package_index ] )
	  {
	      printf("\t%d.   %s\n", package_index+1, packageList[ package_index ] );
	      ++package_index;
	  }

		Free_String_Array_Memory( packageList);
//do sudo apt update
// sudo apt upgrade
// verofy internet connection
// read package.install
// parse into strings
// do sudo apt install for each string
// return report of pass and failed installs


}

char** Parse_Package_List(char*  software_list_filepath )
{
	int MAX_LINES = 200;
	int MAX_LINE_LENGTH = 100;
	char read_line[250];

	FILE* software_list_file = fopen("/home/pi/firmware/package.install", "r");                 //  The popen() function opens a process by creating a pipe, forking and invoking the shell.
	if (software_list_file == NULL)
	{
			printf("Error opening package list file!!\n" );
			exit(1);
	}

	int line_count = 0;
	char**  package_list = malloc(sizeof(char*) * MAX_LINES);        // allocate memory for pointer to strings
	while (fgets(read_line, sizeof(read_line), software_list_file) != NULL)     /* Read the output a line at a time - output it. */
	{
			Trim_Trailing_WhiteSpace(read_line);
			//printf("LINE:\t%s\n", read_line);
			package_list[line_count] = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH); // allocate memory for the
			strcpy(package_list[line_count], read_line);
			++line_count;
	}
	package_list[line_count] = NULL;   // Add a marker for the last string in the array
	fclose( software_list_file );     // close file pointer to STDOUT
	return package_list;
}

void Set_Splash_Icon(char* splash_icon_filepath)
{

}


void Set_Launch_Bar_Icon(char* launch_icon_filepath)
{
//    /usr/share/icons/PiX/32x32/places/start_here.png


}


bool Create_SSH_Keys()
{
    // create directory .ssh

    // create key with identifier
    //ssh keygen -t rsa -C  "PIBB38"

    // send the contents of the public key to the server:
    //cat ~/.ssh/id_rsa.pub | ssh pi@10.198.23.52 'cat >> ~/.ssh/authorized_keys'
}




/*
|--------------------------------------------------------------------------
| Get_CPU_Temp
|--------------------------------------------------------------------------
|
| Query the linux kernel for the CPU temperature. Returns a double of the
| temperature in Celsius. Not super precise but gives pretty good results.
| Succesive reads may return the same temperature. Seems to change in around
| 0.5C increments, despite showing finer resolution. Tested with cold spray
| and temperature reporting is accurate- returns values in vicinity of -20
| when hit with cold spray.
|
| @return    tempC    temperature of pi CPU in degrees Celsius
*/
double Get_CPU_Temp()
{
    char temperature_command[] = "/opt/vc/bin/vcgencmd measure_temp";
    char** shell_response = Exec_Shell_Command( temperature_command );
    double tempC = parseDouble( shell_response[0] );
    Free_String_Array_Memory( shell_response );

    return tempC;
}

void Remove_User(char* USERNAME)
{
    char delete_user_command[100];
    strcpy(delete_user_command, "sudo userdel ");                    // linux command to delete a user
    strcat(delete_user_command, USERNAME);                        // Append USERNAME to the command

    char** result = Exec_Shell_Command( delete_user_command );          // Execute the delete command
    printf("\n------------\n");
    printf(COLOR_BOLD_YELLOW "REMOVE USER\n" COLOR_RESET);
    printf("\tRemoving user:\t" COLOR_LIGHT_MAGENTA "%s.\n" COLOR_RESET, USERNAME);
    Print_String_Array( result );                                       // Print shell response
    printf("------------\n");
    Free_String_Array_Memory( result );                                 // Free memory from return string
}


/*
|--------------------------------------------------------------------------
| Expand_FileSystem
|--------------------------------------------------------------------------
|
| Fresh Rasbian install only allots max 8 GB disk space to the SD card, despite
| the SD card physical size. This function firsts queries whether the file
| system can be expanded. If it can be expanded, then the command is executed
| to expand the filesystem. File system changes will not take effect until
| reboot.
|
*/
void Expand_FileSystem()
{
    int SD_card_already_expanded;
    char** shell_response;
    char can_expand[100];
    char get_info_command[] = "sudo raspi-config nonint get_can_expand";
    char expand_FS_command[] = "sudo raspi-config nonint do_expand_rootfs";

    printf(COLOR_BOLD_YELLOW "\n\nEXPANDING FILESYSTEM...\n" COLOR_RESET);
    shell_response = Exec_Shell_Command( get_info_command );
    SD_card_already_expanded = parseInt( shell_response[0] );
    Free_String_Array_Memory( shell_response );

    if( SD_card_already_expanded == 0 )
    {
        printf("\tSD Card Already Expanded\n");
    }
    else
    {
        printf("\tExpanding SD Card ....");
        shell_response = Exec_Shell_Command( expand_FS_command );
        Free_String_Array_Memory( shell_response );
        printf("\tChanges will apply after reboot\n");
    }
    printf("\n\n");
}

/*
|--------------------------------------------------------------------------
| Backup_File
|--------------------------------------------------------------------------
|
| Creates a copy of the file parameter in the argument. The argument should be
| a fully referenced filepath if not the current directory. For instance:
|     /home/pi/Documents/save.txt
| First a check is made the file in the argument actually exists. Then it checks if
| a backup copy has already been made. If a backup copy already exists, it is not
| overwritten. If a backup does not exist, then a copy is made, appending the
| copy with ".pi_original". From the above example the backup would be:
|     /home/pi/Documents/save.txt.pi_original
|
|@param   filepath  fully specified filepath to target file, which is to be backup up
*/
void Backup_File(char* filepath)
{
    if( !Verify_File_Exists(filepath) ) // if file to backup doesnt exist, leave
        return;

    char* backup_file_suffix = ".pi_orig";

    char backup_file_path[100];
    strcpy(backup_file_path, filepath);
    strcat(backup_file_path, BACKUP_FILE_SUFFIX);           // a backup file ends in ".pi_original"
    backup_file_path[ strlen(backup_file_path) ] = '\0';

    if( Verify_File_Exists(backup_file_path) )  // If backup file exists already, dont overwrite it
    {
        printf(COLOR_YELLOW "\tBACKUP:\t" COLOR_RESET "file exists already  " COLOR_CYAN "%s\n" COLOR_RESET , backup_file_path);
        return;
    }

    char shell_command[100];
    sprintf(shell_command, "sudo cp %s %s", filepath, backup_file_path);
    char** response = Exec_Shell_Command( shell_command);
    Free_String_Array_Memory( response );
    printf("Backed up file:\t%s\n", backup_file_path);
}

/*
|--------------------------------------------------------------------------
| Backup_System_Files
|--------------------------------------------------------------------------
|
| Iteratively creates backups of all files listed.
|
*/
void Backup_System_Files()
{
    printf("---------------\n");
    printf( COLOR_BOLD_YELLOW "BACKUP SYSTEM FILES\n" COLOR_RESET);
    Backup_File("/etc/sudoers.d/010_pi-nopasswd");
    Backup_File("/etc/lightdm/lightdm.conf");
    Backup_File("/etc/systemd/system/autologin@.service");
    Backup_File("/etc/default/keyboard");
    Backup_File("/boot/config.txt");
    Backup_File("/etc/fstab");
    Backup_File("/etc/bash.bashrc");
    Backup_File("/etc/xdg/lxpanel/LXDE-pi/panels/panel");
    Backup_File("/etc/wpa_supplicant/wpa_supplicant.conf");
    Backup_File("/etc/dhcpcd.conf");
    Backup_File("/etc/network/interfaces");
    printf("---------------\n");
}


void Set_Wallpaper(char* wallpaper_filepath)
{
    // verify ends with .jpg or .png
    char* file_suffix = Get_File_Suffix(wallpaper_filepath);
    bool file_is_picture = false;
    if( String_Equals_String(".png", file_suffix))
        file_is_picture = true;
    else if(String_Equals_String(".jpg", file_suffix))
        file_is_picture = true;
    else if(String_Equals_String(".jpeg", file_suffix))
        file_is_picture = true;
    free(file_suffix);

    // If the argument is not a photo, dont set it as wallpaper
    if( !file_is_picture )
        return;
    char shell_command[100];
    char update_command[] = "sudo killall -9 pcmanfm";
    // /home/pi/.config/pcmanfm/LXDE-pi/desktop-items-0.conf
    // edit the field wallpaper=
    // killall -9 pcmanfm
    char* escape_slash = "\\/";

    strcpy(shell_command, "sed -i 's/^wallpaper=.*/wallpaper=");

    char sed_filepath[50];


    int sed_index = 0;
    for(int i=0; i<strlen(wallpaper_filepath); ++i)
    {
        if( wallpaper_filepath[i] == '/')
        {
            sed_filepath[sed_index] = '\\';
            ++sed_index;
            sed_filepath[sed_index] = '/';
            ++sed_index;
        }
        else
        {
            sed_filepath[sed_index] = wallpaper_filepath[i];
            ++sed_index;
        }
    }
    sed_filepath[sed_index] = '\0';

    strcat(shell_command, sed_filepath);        // append filepath to shell command
    strcat(shell_command, "/' /home/pi/.config/pcmanfm/LXDE-pi/desktop-items-0.conf");
    printf("command:\t%s\n", shell_command);

    Backup_File("/home/pi/.config/pcmanfm/LXDE-pi/desktop-items-0.conf");
    char** response_string;
    // verify wallpaper file exists in proper location:
    if( access( wallpaper_filepath, F_OK ) != -1 )
    {
        printf("\tWallpaper File Exists:  \t\t" COLOR_LIGHT_CYAN "%s\n" COLOR_RESET, wallpaper_filepath);        // file exists
        response_string = Exec_Shell_Command( shell_command );
        Free_String_Array_Memory( response_string );
        response_string = Exec_Shell_Command( update_command );
        Free_String_Array_Memory( response_string );
    }
    else
    {
        printf("file not present\n");
              return;
    }
}


void Reboot_PI()
{
  char reboot_command[100];
  strcpy( reboot_command, "sudo reboot" );

  char**  return_string_array = Exec_Shell_Command( reboot_command );
  Free_String_Array_Memory(return_string_array);
}


/*
|--------------------------------------------------------------------------
| Get_Disk_Usage
|--------------------------------------------------------------------------
|
|	Gets disk space stats for the local micro SD card, and any attached Flash drives.
| Stats are collected using the "df" shell command . "df" returns more stats than
| just the USB flash and micro SD card, so the output from df is piped to grep,
| which filters the output. grep only returns lines that contain /dev/root (microSD),
| or /dev/sd (USB flash). The full shell command is:
|				df -Tha --total | grep -E "/dev/root|/dev/sd"
|
|Flags for df:
|			-T			print filesystem type
|			-h			print human readable output
|			--total	produce grand totals
|
|Flags for grep
|			-E			use regular expressions in search pattern
|
| Example output:
| /dev/sda1      vfat         970M   297M  664M   32% /home/pi//USB_DRIVE
|
*/
void Get_Disk_Usage()
{
  char SD_card_line[200];
  char Flash_Drive_line[200];
  char SD_card_use[100];
  char Flash_Drive_Use[100];
  char shell_command[300];
	bool FLASH_DRIVE = false;

  printf(COLOR_BOLD_YELLOW "\nDISK USE:\n" COLOR_RESET);

  strcpy( shell_command, "df -Tha --total" );
  strcat( shell_command, " | grep -E \"/dev/root|/dev/sd\""); // list disk usage, then search only for root use and flash use in /dev/sd*

  char**  return_string_array = Exec_Shell_Command( shell_command );
  strcpy(SD_card_line, return_string_array[0]);
	if( return_string_array[1] != NULL )
			FLASH_DRIVE = true;
	if( FLASH_DRIVE )
	{
			strcpy(Flash_Drive_line, return_string_array[1]);
  		Trim_Trailing_WhiteSpace(Flash_Drive_line);
		  Parse_Disk_Use(Flash_Drive_line, &Flash_Drive);
	}

  Free_String_Array_Memory(return_string_array);
  Trim_Trailing_WhiteSpace(SD_card_line);
  Parse_Disk_Use(SD_card_line, &uSD_Card);

  printf("\t\tKERNEL\t\tFILESYS\t  TOTAL\tUSED\tFREE\t% USE\tMOUNT LOCATION\n");
  printf("\t\t--------------------------------------------------------------------\n");
	if( FLASH_DRIVE)
	{
		printf(COLOR_CYAN); printf("FLASH DRIVE\t"); printf(COLOR_RESET);
	  printf("%s\t", Flash_Drive.kernel_location);
	  printf("%s\t  ", Flash_Drive.filesystem);
	  printf("%s\t",  Flash_Drive.total_space);
	  printf("%s\t", Flash_Drive.used_space);
	  printf("%s\t", Flash_Drive.free_space);
	  printf("%s\t", Flash_Drive.percent_filled);
	  printf(COLOR_CYAN);           printf("%s\t", Flash_Drive.mount_location);     printf(COLOR_RESET);
	  printf(COLOR_LIGHT_MAGENTA);  printf("%s", Flash_Drive.percent_filled);       printf(COLOR_RESET);
	  printf("  of  ");
	  printf(COLOR_LIGHT_MAGENTA);  printf("%s\n",  Flash_Drive.total_space); printf(COLOR_RESET);

	}


  printf(COLOR_CYAN); printf("uSD CARD\t"); printf(COLOR_RESET);
  printf("%s\t", uSD_Card.kernel_location);
  printf("%s\t  ", uSD_Card.filesystem);
  printf("%s\t",  uSD_Card.total_space);
  printf("%s\t", uSD_Card.used_space);
  printf("%s\t", uSD_Card.free_space);
  printf("%s\t", uSD_Card.percent_filled);
  printf(COLOR_CYAN);           printf("%s\t\t\t", uSD_Card.mount_location);     printf(COLOR_RESET);
  printf(COLOR_LIGHT_MAGENTA);  printf("%s", uSD_Card.percent_filled);       printf(COLOR_RESET);
  printf("  of  ");
  printf(COLOR_LIGHT_MAGENTA);  printf("%s\n\n",  uSD_Card.total_space); printf(COLOR_RESET);
}


/*
|--------------------------------------------------------------------------
| Parse_Disk_Use
|--------------------------------------------------------------------------
|
|	Parses the output from the "df" shell command into tokens, and stores the
| output into a data structure for reporting. The output from a command df
| command is passed as argument "console_line". This string is split into
| tokens delimited by whitespace, and the tokens are stored in struct of
| type Disk_Use.
|
| Example output from df:
| /dev/sda1      vfat         970M   297M  664M   32% /home/pi//USB_DRIVE
|
| fields the tokens are stored into:
| kernel_location filesystem   total_space  used_space  free_space   percent_used  mount_location
|
| @param				console_line			single line string output from df command
| @param 				device						Disk_Usage struct object, populated by this command
|
*/
void Parse_Disk_Use(char* console_line, struct Disk_Usage* device)
{
    char token_array[7][50];    // 7 tokens with 50 characters max length each
    int index_token_start = 0;
    int index_token_end = 0;
    int index_consumed = 0;
    char ch_at_index;
    int token_index = 0;

    Trim_Leading_WhiteSpace( console_line );
    char* substring;
    while(index_consumed < strlen(console_line))
    {
        while( isspace( console_line[ index_consumed ] ) && index_consumed < strlen(console_line) )   // skip whitespace between tokens
        { ++index_consumed;  }

        index_token_start = index_consumed;
        index_token_end = index_token_start;

        while( !isspace( console_line[ index_consumed ] ) && index_consumed < strlen(console_line) )   // consume any non whitespace characters (part of token)
        { ++index_consumed;  }
        index_token_end = index_consumed;
        substring = Get_Substring( console_line, index_token_start, index_token_end );
        strcpy( token_array[ token_index ], substring );
        free(substring);
        ++token_index;
    }

    strcpy(device->kernel_location,  token_array[ 0 ] );
    strcpy(device->filesystem,       token_array[ 1 ] );
    strcpy(device->total_space,      token_array[ 2 ] );
    strcpy(device->used_space,       token_array[ 3 ] );
    strcpy(device->free_space,       token_array[ 4 ] );
    strcpy(device->percent_filled,   token_array[ 5 ] );
    strcpy(device->mount_location,   token_array[ 6 ] );
}


/*
|--------------------------------------------------------------------------
| Set_Network_Configuration
|--------------------------------------------------------------------------
|
|	Sets up the network confuration on the pi. Sets a static eth0 address, and
| dhcp wifi address. Connects to wifi networks that have credentials stored
| in the wpa_supplicant file. The files edited by this command are:
|			/etc/dhcpcd.conf
|			/etc/wpa_supplicant/wpa_supplicant.conf
|			/etc/network/interfaces
|
| @param				eth0_IP			static ip address to set eth0 to
|
*/
void Set_Network_Configuration(char* eth0_IP)
{
    char dhcp_filepath[] =            "/etc/dhcpcd.conf";
    char wpa_supplicant_filepath[] =  "/etc/wpa_supplicant/wpa_supplicant.conf";
    char interfaces_filepath[] =      "/etc/network/interfaces";
    char write_line[200];
    Erase_String_Contents( write_line );

    int dhcp_File = open( dhcp_filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(dhcp_File == -1)
    {
        perror("could not open dhcpcd.conf file");
        return;
    }
    printf("\n-------------------------------------------------------------------------------------\n");
    printf(COLOR_BOLD_YELLOW "SETTING NETWORK CONFIGURATION\n" COLOR_RESET);
    printf("\tWriting static eth0 address " COLOR_LIGHT_GREEN "%s " COLOR_RESET "to \t" COLOR_CYAN "%s\n" COLOR_RESET, eth0_IP, dhcp_filepath);
    strcpy(write_line, DHCP_LINE1);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE1)+1);

    strcpy(write_line, DHCP_LINE2);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE2)+1 );

    strcpy(write_line, DHCP_LINE3);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE3)+1 );

    strcpy(write_line, DHCP_LINE4);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE4)+1 );

    strcpy(write_line, DHCP_LINE5);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE5)+1 );

    strcpy(write_line, DHCP_LINE6);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE6)+1 );

    strcpy(write_line, DHCP_LINE7);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE7)+1 );

    strcpy(write_line, DHCP_LINE8);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE8)+1 );

    strcpy(write_line, DHCP_LINE9);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE9)+1 );

    strcpy(write_line, DHCP_LINE10);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE10)+1 );

    strcpy(write_line, DHCP_LINE11);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE11)+1 );

    strcpy(write_line, DHCP_LINE12);
    strcat(write_line, eth0_IP);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(write_line)+1 );

    strcpy(write_line, DHCP_LINE13);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE13)+1 );

    strcpy(write_line, DHCP_LINE14);
    strcat(write_line, "\n");
    write(dhcp_File, &write_line, (ssize_t) strlen(DHCP_LINE14)+1 );

    close(dhcp_File);

    int wpa_supplicant_File = open( wpa_supplicant_filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(wpa_supplicant_File == -1)
    {
        perror("could not open wpa supplicant file");
        return;
    }

    printf("\tWriting default config to \t\t\t" COLOR_CYAN "%s\n" COLOR_RESET, interfaces_filepath);
    strcpy(write_line, WPA_LINE1);
    strcat(write_line, "\n");
    write(wpa_supplicant_File, &write_line, (ssize_t) strlen(WPA_LINE1)+1 );

    strcpy(write_line, WPA_LINE2);
    strcat(write_line, "\n");
    write(wpa_supplicant_File, &write_line, (ssize_t) strlen(WPA_LINE2)+1 );

    strcpy(write_line, WPA_LINE3);
    strcat(write_line, "\n");
    write(wpa_supplicant_File, &write_line, (ssize_t) strlen(WPA_LINE3)+1 );

    strcpy(write_line, WPA_LINE4);
    strcat(write_line, "\n");
    write(wpa_supplicant_File, &write_line, (ssize_t) strlen(WPA_LINE4)+1 );

    strcpy(write_line, WPA_LINE5);
    strcat(write_line, "\n");
    write(wpa_supplicant_File, &write_line, (ssize_t) strlen(WPA_LINE5)+1 );

    strcpy(write_line, WPA_LINE6);
    strcat(write_line, "\n");
    write(wpa_supplicant_File, &write_line, (ssize_t) strlen(WPA_LINE6)+1 );

    strcpy(write_line, WPA_LINE7);
    strcat(write_line, "\n");
    write(wpa_supplicant_File, &write_line, (ssize_t) strlen(WPA_LINE7)+1 );

    strcpy(write_line, WPA_LINE8);
    strcat(write_line, "\n");
    write(wpa_supplicant_File, &write_line, (ssize_t) strlen(WPA_LINE8)+1 );

    strcpy(write_line, WPA_LINE9);
    strcat(write_line, "\n");
    write(wpa_supplicant_File, &write_line, (ssize_t) strlen(WPA_LINE9)+1 );

    strcpy(write_line, WPA_LINE10);
    strcat(write_line, "\n");
    write(wpa_supplicant_File, &write_line, (ssize_t) strlen(WPA_LINE10)+1 );

    close(wpa_supplicant_File);

    int interfaces_File = open( interfaces_filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(interfaces_File == -1)
    {
        perror("could not open interfaces file");
        return;
    }

    printf("\tWriting wifi credentials to \t\t\t" COLOR_CYAN "%s\n" COLOR_RESET, wpa_supplicant_filepath);
    strcpy(write_line, INTERFACES_LINE1);
    strcat(write_line, "\n");
    write(interfaces_File, &write_line, (ssize_t) strlen(INTERFACES_LINE1)+1 );

    strcpy(write_line, INTERFACES_LINE2);
    strcat(write_line, "\n");
    write(interfaces_File, &write_line, (ssize_t) strlen(INTERFACES_LINE2)+1 );

    strcpy(write_line, INTERFACES_LINE3);
    strcat(write_line, "\n");
    write(interfaces_File, &write_line, (ssize_t) strlen(INTERFACES_LINE3)+1 );
    printf("-------------------------------------------------------------------------------------\n");
    printf("\tChanges will take effect after reboot\n\n");
}

void Create_Aliases_File()
{
    char move_file_command[] = "sudo mv ./.bash_aliases /home/pi/.bash_aliases";
    char permissions_command[200];
    char** response_string;

    printf(COLOR_BOLD_YELLOW "\nCREATING ALIASES FILE: \n" COLOR_RESET "\tCreate File:\t\t" COLOR_CYAN "%s\t" COLOR_RESET, BASH_ALIAS_FILE);

    response_string = Exec_Shell_Command( move_file_command );
    Print_String_Array( response_string );
    Free_String_Array_Memory( response_string );

    // verify Alias file exists in proper location, if it does set executable permissions
    if( access( BASH_ALIAS_FILE, F_OK ) != -1 )
    {
        printf(CHECKMARK_CHARACTER);
        printf("\n");
        printf("\tSet file permissions\t...\n");
        sprintf(permissions_command, "sudo chmod +rwx %s", BASH_ALIAS_FILE);
        response_string = Exec_Shell_Command(permissions_command);
        Free_String_Array_Memory(response_string);
        Print_Aliases();
    }
    else
    { printf("Alias file not present. \n");  }       // file doesn't exist

// ADD FUNCTION TO BASHRC FILE
    // the following code adds functionality to the pi console. Whenever you change directories with "cd" command,
    // the contents of the changed directory will be listed with the "ls" command. It is the same logically as:
    //      cd some_directory/
    //      ls
    bool cd_function_defined_already = Search_String_in_File( BASHRC_FILE, BASHRC_APPEND4);
    if( cd_function_defined_already == false )
    {
        printf("%s\n", BASHRC_APPEND4);
        FILE* bashrc_file = fopen(BASHRC_FILE, "a");     // OPEN file for appending with "a"
        fprintf(bashrc_file, "\n");
        fprintf(bashrc_file, BASHRC_LINE_SEP ); fprintf(bashrc_file, "\n");
        fprintf(bashrc_file, BASHRC_APPEND1  ); fprintf(bashrc_file, "\n");
        fprintf(bashrc_file, BASHRC_APPEND2  ); fprintf(bashrc_file, "\n");
        fprintf(bashrc_file, BASHRC_APPEND3  ); fprintf(bashrc_file, "\n");
        fprintf(bashrc_file, BASHRC_APPEND4  ); fprintf(bashrc_file, "\n");
        fprintf(bashrc_file, BASHRC_APPEND5  ); fprintf(bashrc_file, "\n");
        fprintf(bashrc_file, BASHRC_LINE_SEP ); fprintf(bashrc_file, "\n");
        fprintf(bashrc_file, BASHRC_APPEND6 ); fprintf(bashrc_file, "\n");
        fclose( bashrc_file );
    }

		char source_command[] = ". /home/pi/.bashrc";
		response_string = Exec_Shell_Command( source_command );
		Print_String_Array( response_string );
		Free_String_Array_Memory( response_string );

}

void Print_Aliases()
{
    char read_line[200];
    printf("\tAlias List:\n");
    FILE* alias_file = fopen(BASH_ALIAS_FILE, "r");     // OPEN file for reading
    if (alias_file == NULL)
    {
        printf("Error opening alias file!!\n" );
        exit(1);
    }

    while (fgets(read_line, sizeof(read_line), alias_file) != NULL)     /* Read the output a line at a time - output it. */
    {
        Trim_Trailing_WhiteSpace(read_line);
        printf("\t\t%s\n", read_line);
    }
    return;
}


void Change_Root_Password(char* root_password)
{
  char command_string[200];
  sprintf(command_string, "sudo passwd root");
  FILE* root_shell = popen(command_string, "w");
  fprintf(root_shell, "ir\n");
  fprintf(root_shell, "ir\n");
  pclose(root_shell);


}

// Check User List:   getent passwd | grep 'username'
// Check Password has been set


void Print_String_Array(char** string_array)
{
  int i = 0;
  while(string_array[i])
  {
      printf("\t%s\n", string_array[i]);
      ++i;
  }
}

char** List_Users()
{
    char UID_MIN_string[50];
    char UID_MAX_string[50];
    int UID_MIN;
    int UID_MAX;
    char* end_ptr;

    char**  return_string_array = Exec_Shell_Command("grep -E '^UID_MIN|^UID_MAX' /etc/login.defs");  // allocate memory for pointer to strings
    strcpy(UID_MIN_string, return_string_array[0]);
    strcpy(UID_MAX_string, return_string_array[1]);
    Free_String_Array_Memory(return_string_array);

    UID_MIN = parseInt(UID_MIN_string);
    UID_MAX = parseInt(UID_MAX_string);

    char** long_user_list = Exec_Shell_Command("getent passwd");
    char** user_list = parseUsers(long_user_list, UID_MIN, UID_MAX);
    Free_String_Array_Memory(long_user_list);

    return user_list;
}

void Print_Users()
{

    char UID_MIN_string[50];
    char UID_MAX_string[50];
    int UID_MIN;
    int UID_MAX;
    char* end_ptr;

    printf(COLOR_BOLD_YELLOW "\nLIST USERS:\n" COLOR_RESET);

    char**  return_string_array = Exec_Shell_Command("grep -E '^UID_MIN|^UID_MAX' /etc/login.defs");  // allocate memory for pointer to strings
    strcpy(UID_MIN_string, return_string_array[0]);
    strcpy(UID_MAX_string, return_string_array[1]);
    Free_String_Array_Memory(return_string_array);

    UID_MIN = parseInt(UID_MIN_string);
    UID_MAX = parseInt(UID_MAX_string);

    printf("\nRegular User ID Range:\n");
    printf("\tUID min: \t%d\n", UID_MIN);
    printf("\tUID max: \t%d\n", UID_MAX);
    char** long_user_list = Exec_Shell_Command("getent passwd");
    printf("\nAll Users:\n");
    Print_String_Array( long_user_list );
    char** user_list = parseUsers(long_user_list, UID_MIN, UID_MAX);
    Free_String_Array_Memory(long_user_list);
    printf("\nRegular Users:\n" COLOR_LIGHT_MAGENTA);
    Print_String_Array( user_list );
    printf( COLOR_RESET "\n");
    Free_String_Array_Memory( user_list);

    return;
}

void Add_User(char* NEW_USERNAME)
{
    char command_add_user[100];
    char command_add_groups[300];
    char** response_string;

    // First check if user exists already
    printf("\n--------------\n");
    printf(COLOR_BOLD_YELLOW "NEW USER\n" COLOR_RESET);
    char** existing_users = List_Users();

    if( String_List_Contains(existing_users, NEW_USERNAME) )
    {
        printf("\tUser " COLOR_LIGHT_MAGENTA "%s " COLOR_RESET "already exists, not creating.\n", NEW_USERNAME);
        return;
    }

    // Create the new user
    printf("\tCreating new user " COLOR_LIGHT_GREEN "%s " COLOR_RESET "\n", NEW_USERNAME);
    sprintf(command_add_user, "sudo useradd %s", NEW_USERNAME);                             // create shell command, store in string
    response_string = Exec_Shell_Command(command_add_user);                                 // execute the command: "sudo adduser new_user"
    Free_String_Array_Memory(response_string);                                              // free the memory allocated in "response_string"

    // ADD user to all groups on the pi. (so user has permissions to use all parts of the pi hardware)
    printf("\tAdding user " COLOR_LIGHT_GREEN "%s " COLOR_RESET "to the following groups:\n\t\tsudo,pi,adm,dialout,cdrom,sudo,audio,video,plugdev,games,users,input,netdev,spi,i2c,gpio\n", NEW_USERNAME);
    sprintf(command_add_groups, "sudo usermod %s -a -G sudo,pi,adm,dialout,cdrom,sudo,audio,video,plugdev,games,users,input,netdev,spi,i2c,gpio", NEW_USERNAME);
    response_string = Exec_Shell_Command(command_add_groups);                               // execute the command: "sudo usermod new_user -a -G sudo,pi,adm, ........"
    Free_String_Array_Memory(response_string);                                              // free the allocated memory in return string "response_string"
}

void Enable_Sudo_No_Password_For_User(char* USERNAME)
{
      char command_find_and_replace[200];
      char command_get_original_line[200];
      char command_get_modified_line[200];
      char** current_line;
      char** modified_line;
      char** response_string;
  //---------------------------------------------

      // add user to sudoers file to enable use of sudo with no password
      // change from current_user to new_user
      //FILE:     /etc/sudoers.d/010_pi-nopasswd
      // line in file to replace: pi ALL=(ALL) NOPASSWD: ALL
      //  's/[a-zA-Z0-9]*/sapien/'
      printf("\n------------\n");
      printf(COLOR_BOLD_YELLOW "ENABLE sudo NO PASSWORD\n" COLOR_RESET);
      printf("\tAdding user " COLOR_LIGHT_MAGENTA "%s " COLOR_RESET "to \"sudoers\" file\t" COLOR_CYAN "/etc/sudoers.d/010_pi-nopasswd\n" COLOR_RESET, USERNAME);

      // Get current user in the file (before modifying)
      sprintf(command_get_original_line, "sudo sed -r 's/(^.[^ ]+).*/\\1/' /etc/sudoers.d/010_pi-nopasswd");  // command to search for current user(s) set in file
      current_line = Exec_Shell_Command(command_get_original_line);                                           // execute sed search command
      printf("\t\tCURRENT user: \t%s", current_line[0]);                                                      // print out any users
      Free_String_Array_Memory(current_line);                                                                 // free allocated memory from returned string

      // Get current line in file to modify
      sprintf(command_get_original_line, "sudo sed -n '/ALL=(ALL)/p' /etc/sudoers.d/010_pi-nopasswd");
      current_line = Exec_Shell_Command(command_get_original_line);
      printf("\n\t\tFILE LINE:  \t%s\n", current_line[0]);
      Free_String_Array_Memory(current_line);

      sprintf(command_find_and_replace, "sudo sed -i -e 's/[a-zA-Z0-9]*/%s/' /etc/sudoers.d/010_pi-nopasswd", USERNAME);
      //response_string = Exec_Shell_Command(command_find_and_replace);
      //Free_String_Array_Memory(response_string);
      Erase_String_Contents(command_find_and_replace);                                                        // empty the string for next command

      sprintf(command_get_modified_line, "sudo sed -n '/ALL=(ALL)/p' /etc/sudoers.d/010_pi-nopasswd");
      modified_line = Exec_Shell_Command(command_get_modified_line);
      printf("\t\tMODIFY LINE:  \t%s\n", modified_line[0]);
      Free_String_Array_Memory(modified_line);
}

// Autologin can be setup for only a single user. There are two places to set autologin: the console and the desktop
// The user configured to autologin is specified in two files. This function searches through both files and inserts the argument username into
// the files
void Enable_Autologin_For_User(char* USERNAME)
{
      char user[50];
      char line[250];

      printf(COLOR_BOLD_YELLOW "\nENABLE DESKTOP AUTOLOGIN:\n" COLOR_RESET);
      printf("\tAdding auto-login for user " COLOR_LIGHT_GREEN "%s " COLOR_RESET "to desktop GUI in file:" COLOR_CYAN "\t/etc/lightdm/lightdm.conf" COLOR_RESET "\n", USERNAME);

      Get_Desktop_Autologin_User(user);
      printf("\t\tCURRENT USER:  \t%s\n", user);
      Get_Desktop_Autologin_File_Entry(line);
      printf("\t\tFILE LINE:  \t%s\n", line);

      if( String_Equals_String( user, USERNAME) )
          printf("\t\tDesktop Autologin already enabled for user " COLOR_LIGHT_MAGENTA "%s" COLOR_RESET ".\n", USERNAME);
      else
      {
          Enable_Desktop_Autologin(USERNAME);
          Get_Desktop_Autologin_File_Entry(line);
          printf("\t\tMODIFIED LINE:\t%s\n", line);
      }


      printf(COLOR_BOLD_YELLOW "\nENABLE CONSOLE AUTOLOGIN:\n" COLOR_RESET);
      printf("\tAdding console auto-login for user " COLOR_LIGHT_GREEN "%s " COLOR_RESET "in file:" COLOR_CYAN "\t/etc/systemd/system/autologin@.service" COLOR_RESET "\n", USERNAME);

      Get_Console_Autologin_User(user);
      printf("\t\tCURRENT USER:  \t%s\n", user);
      Get_Console_Autologin_File_Entry(line);
      printf("\t\tFILE LINE:  \t%s\n", line);

      if( String_Equals_String( user, USERNAME) )
          printf("\tConsole Autologin already enabled for user " COLOR_LIGHT_MAGENTA "%s. " COLOR_RESET "\n", USERNAME);
      else
      {
          Enable_Console_Autologin(USERNAME);
          Get_Console_Autologin_File_Entry(line);
          printf("\t\tMODIFIED LINE:\t%s\n", line);
      }
      printf("\n");
}

void Set_User_Password(char* USERNAME, char* NEW_PASSWORD)
{
  char command_string[200];
  // Change password for new_user. Sets to password passed in argument
  // uses chpasswd terminal command to change the password
  // echo command sends user:password through a pipe to chpasswd utility
  // echo ‘user:pass’ | sudo /usr/sbin/chpasswd
  printf("CHANGE PASSWORD:\n");
  printf("\tChanging password for user " COLOR_LIGHT_MAGENTA "%s " COLOR_RESET "\n", USERNAME);
  //printf("\t\tCOMMAND:\t" COLOR_LIGHT_CYAN "sudo echo %s:*pass* | sudo /usr/sbin/chpasswd\n" COLOR_RESET, USERNAME);
  sprintf(command_string, "sudo echo ‘%s:%s’ | sudo /usr/sbin/chpasswd", USERNAME, NEW_PASSWORD);
  char** response_string = Exec_Shell_Command(command_string);
  Free_String_Array_Memory(response_string);
  Erase_String_Contents(command_string);
}

/*
|--------------------------------------------------------------------------
| Set_Hostname
|--------------------------------------------------------------------------
|
| Sets the Hostname of the Pi using a raspi-config shell command. See macro
| for SET_HOSTNAME. Shell command executed using Exec_Shell_Command. The
| hostname string argument is appended to the command as an argument
|
| @param    hostname    the hostname you want to set the pi to
*/
void Set_Hostname(char* hostname)
{
    char exec_command[100];
    char** string_response;

    strcpy(exec_command, SHELL_CMD_SET_HOSTNAME);
    strcat(exec_command, hostname);
    string_response = Exec_Shell_Command(exec_command);
    Free_String_Array_Memory(string_response);

    return;
}

/*
|--------------------------------------------------------------------------
| Get_Hostname
|--------------------------------------------------------------------------
|
| Get the PI Hostname by the raspi-config command "sudo raspi-config nonint get_hostname" stored in macro 'SHELL_CMD_GET_HOSTNAME'
| The response to raspi-config command is a string of the Hostname. The command is executed in the shell console via popen() function.
| The return from Get_Hostname is the string returned from raspi-config
| @return               string of the PI Hostname
|
*/
char* Get_Hostname()
{
  char read_console[250];
  FILE *command_shell;
  //char* end_ptr; // required as argument to strtol function

  command_shell = popen(SHELL_CMD_GET_HOSTNAME, POPEN_READ);       //  The popen() function opens a process by creating a pipe, forking and invoking the shell.
                                                                  // 2>&1  redirects any error messages to sdout instead of stderr, so we can detect them
  if (command_shell == NULL)
  {
    printf("Error opening pipe!!\n" );
    exit(1);
  }

  if(fgets(read_console, sizeof(read_console), command_shell) != NULL)   // read stdout the console output from raspi-config, and store in "read_console"
  {
    Trim_Trailing_WhiteSpace(read_console);                               // remove trailing whitespace or newline from the hostname
  }
  pclose(command_shell);                                                // close file pointer

  return strdup(read_console);
}


/*
|--------------------------------------------------------------------------
| Set_US_Keyboard_Layout
|--------------------------------------------------------------------------
|
| Sets any attached USB keyboard to use the 'US' keys layout.The function executes by editing the "/etc/default/keyboard" file.
| The layout is set by country code on the line:
| XKBLAYOUT = [country code]
| default country code is 'gb' for great britain. This function uses the 'sed' command to do a find and replace of any two letters
| after "XKBLAYOUT=" with 'us'. The kernel keyboard setup service is then restarted. The shell sed command is:
|   "sed -i -e '/XKBLAYOUT=/s/[a-z][a-z]/us/' /etc/default/keyboard"
|
*/
void Set_US_Keyboard_Layout()
{
  char** response;
  response = Exec_Shell_Command(SHELL_CMD_SET_KEYBOARD);
  Free_String_Array_Memory(response);
  response = Exec_Shell_Command(SHELL_CMD_RESTART_KBD_SERIVCE);
  Free_String_Array_Memory(response);
}

/*
|--------------------------------------------------------------------------
| Get_Keyboard_Layout
|--------------------------------------------------------------------------
|
| Reads the file "/etc/default/keyboard", and parses the line:
|     XKBLAYOUT = [country code]
| Layout is set by country code. default country code is 'gb' for great britain. The
| Desired country code is 'us'
|
| @return   country_code   country code listed in /etc/default/keyboard
*/
char* Get_Keyboard_Layout()
{
  char read_line[250];
  FILE* keyboard_file;
  char filepath[] = "/etc/default/keyboard";
  char* contains = 0;
  char* country_code;

  if ( !(keyboard_file = fopen(filepath, "r") ) )
  {
      printf("Cannot open keyboard configuration file.\n");
      return 0;
  }

  while( (fgets(read_line, 250, keyboard_file) != NULL) )  // fgets reads in a single line at a time into "line"
	{
      if(String_Contains(read_line, "XKBLAYOUT"))
      {
          printf(COLOR_CYAN "\t\t%s " COLOR_RESET ": %s", filepath, read_line);
          country_code = Parse_KBD_Country_Code(read_line);
          return strdup(country_code);
      }
  }
  return 0;
}

/*
|--------------------------------------------------------------------------
| Verify_SSH_Enabled
|--------------------------------------------------------------------------
|
| Verify SSH access is enabled on the PI. Checking is done by the raspi-config command "raspi-config nonint get_ssh" stored in macro 'SHELL_CMD_GET_SSH'
| The response to raspiconfig command is 0 (enabled) or 1 (disabled). The command is executed in the shell console via popen function.
| The return from Verify_SSH_Enabled is true/1 (enabled) or false/0 (disabled). Note the flip flop of logic.
| Return Values:
|             raspi-config nonint get_ssh
|                     0 == SSH enabled
|                     1 == SSH disabled
|             Verify_SSH_Enabled
|                     1 == SSH enabled
|                     0 == SSH disabled
|
*/
bool Verify_SSH_Enabled()
{
  char read_console[250];
  FILE* shell;
  int ssh_not_enabled = 1;
  char* end_ptr; // required as argument to strtol function

  shell = popen(SHELL_CMD_GET_SSH, POPEN_READ);       //  The popen() function opens a process by creating a pipe, forking and invoking the shell.
                                                              // 2>&1  redirects any error messages to sdout instead of stderr, so we can detect them
  if (shell == NULL)
  {
    printf("Error opening shell pipe!!\n" );
    exit(1);
  }

  if(fgets(read_console, sizeof(read_console), shell) != NULL)   // read stdout the console output from echo command, and store in "buffer"
  {
    ssh_not_enabled = strtol(read_console, &end_ptr, 10);              // parse string from console into integer
  }
  pclose(shell);   // close file pointer

  if(!ssh_not_enabled)    // If SSH IS enabled, then not_enabled is false
    return true;
  else return false;
}

/*
|--------------------------------------------------------------------------
| Set_SSH_Enabled
|--------------------------------------------------------------------------
|
| Enable SSH access into the PI. Setting to enable is done by the raspi-config command "sudo raspi-config nonint do_ssh"
| Must supply an additional argument of 0 to enable SSH. The command is executed in the shell console via popen function.
| There is no return string from the raspi-config function.
|
*/
void Set_SSH_Enabled()
{
//  SHELL_CMD_SET_SSH
  FILE* command_shell;
  char Command_Set_SSH_Enabled[100];
  char** response;

  strcpy(Command_Set_SSH_Enabled, SHELL_CMD_SET_SSH);         // copy raspiconfig set command into string variable "Command_Set_SSH_Enabled"
  strcat(Command_Set_SSH_Enabled, "0");                       // append the argument '0' to enable SSH

  response = Exec_Shell_Command(Command_Set_SSH_Enabled);
  Free_String_Array_Memory(response);

  if (command_shell == NULL)
  {
    printf("Error opening pipe!!\n" );
    exit(1);
  }

  pclose(command_shell);   // close file pointer
  return;
}

/*
|--------------------------------------------------------------------------
| Check_Boot_File_Config
|--------------------------------------------------------------------------
|
| Read and parse the PI hardware config file /boot/config.txt
| The lines listed must be in the file. If all lines exist, returns true.
|
|
| dtparam=i2c_arm=on
| dtparam=i2c1_on
| dtparam=spi=on
| hdmi_force_hotplug=1
| hdmi_group=1
| hdmi_mode=16
| dtoverlay=spi1-1cs,cs0_pin=25 #physical pin 22
| dtoverlay=pi3-disable-bt
*/
bool Verify_Boot_File_Config()
{
    bool valid_hardware_config = true;

    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "dtparam=i2c_arm=on") )
        valid_hardware_config = false;
    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "dtparam=i2c1=on") )
        valid_hardware_config = false;
    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "dtparam=spi=on") )
        valid_hardware_config = false;
    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "hdmi_force_hotplug=1") )
        valid_hardware_config = false;
    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "hdmi_group=1") )
        valid_hardware_config = false;
    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "hdmi_mode=16") )
        valid_hardware_config = false;
    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "dtoverlay=spi1-1cs,cs0_pin=25 #physical pin 22") )
        valid_hardware_config = false;
    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "dtoverlay=pi3-disable-bt") )
        valid_hardware_config = false;

    return valid_hardware_config;
}


/*
|--------------------------------------------------------------------------
| Set_Boot_File_Config
|--------------------------------------------------------------------------
|
| Verifies the proper device overlays are set in /boot/config.txt. If a line
| is not present in the file, it is appended
|
| dtparam=i2c_arm=on
| dtparam=i2c1_on
| dtparam=spi=on
| hdmi_force_hotplug=1
| hdmi_group=1
| hdmi_mode=16
| dtoverlay=spi1-1cs,cs0_pin=25 #physical pin 22
| dtoverlay=pi3-disable-bt
*/
bool Set_Boot_File_Config()
{
    char** response;
    printf("Setting missing lines in /boot/config.txt ....\n");
    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "dtparam=i2c_arm=on") )
    {
        printf("\tdtparam=i2c_arm=on\t"); printf(CROSS_CHARACTER); printf("\n");
        response = Exec_Shell_Command("sudo echo 'dtparam=i2c_arm=on' >> /boot/config.txt");
        Free_String_Array_Memory(response);
        printf("Appending line in /boot/config.txt: %s\n", "dtparam=i2c_arm=on");
    }

    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "dtparam=i2c1=on") )
    {
        printf("\tdtparam=i2c1=on\t"); printf(CROSS_CHARACTER); printf("\n");
        response = Exec_Shell_Command("sudo echo 'dtparam=i2c1=on' >> /boot/config.txt");
        Free_String_Array_Memory(response);
        printf("Appending line in /boot/config.txt: %s\n", "dtparam=i2c1_on");
    }

    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "dtparam=spi=on") )
    {
        printf("\tdtparam=spi=on\t"); printf(CROSS_CHARACTER); printf("\n");
        response = Exec_Shell_Command("sudo echo 'dtparam=spi=on' >> /boot/config.txt");
        Free_String_Array_Memory(response);
        printf("Appending line in /boot/config.txt: %s\n", "dtparam=spi=on");
    }

    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "hdmi_force_hotplug=1") )
    {
        printf("\thdmi_force_hotplug=1\t"); printf(CROSS_CHARACTER); printf("\n");
        response = Exec_Shell_Command("sudo echo 'hdmi_force_hotplug=1' >> /boot/config.txt");
        Free_String_Array_Memory(response);
        printf("Appending line in /boot/config.txt: %s\n", "hdmi_force_hotplug=1");
    }

    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "hdmi_group=1") )
    {
        printf("\thdmi_group=1\t"); printf(CROSS_CHARACTER); printf("\n");
        response = Exec_Shell_Command("sudo echo 'hdmi_group=1' >> /boot/config.txt");
        Free_String_Array_Memory(response);
        printf("Appending line in /boot/config.txt: %s\n", "hdmi_group=1");
    }

    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "hdmi_mode=16") )
    {
        printf("\thdmi_mode=16\t"); printf(CROSS_CHARACTER); printf("\n");
        response = Exec_Shell_Command("sudo echo 'hdmi_mode=16' >> /boot/config.txt");
        Free_String_Array_Memory(response);
        printf("Appending line in /boot/config.txt: %s\n", "hdmi_mode=16");
    }

    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "dtoverlay=spi1-1cs,cs0_pin=25 #physical pin 22") )
    {
        printf("\tdtoverlay=spi1-1cs,cs0_pin=25 #physical pin 22\t"); printf(CROSS_CHARACTER); printf("\n");
        response = Exec_Shell_Command("sudo echo 'dtoverlay=spi1-1cs,cs0_pin=25 #physical pin 22' >> /boot/config.txt");
        Free_String_Array_Memory(response);
        printf("Appending line in /boot/config.txt: %s\n", "dtoverlay=spi1-1cs,cs0_pin=25 #physical pin 22");
    }

    if( !Search_String_in_File(FILE_PI_HARDWARE_CONFIG, "dtoverlay=pi3-disable-bt") )
    {
        printf("\tdtoverlay=pi3-disable-bt\t"); printf(CROSS_CHARACTER); printf("\n");
        response = Exec_Shell_Command("sudo echo 'dtoverlay=pi3-disable-bt' >> /boot/config.txt");
        Free_String_Array_Memory(response);
        printf("Appending line in /boot/config.txt: %s\n", "dtoverlay=pi3-disable-bt");
    }

    return Verify_Boot_File_Config();
}

/*
|--------------------------------------------------------------------------
| Get_Environment_Variables
|--------------------------------------------------------------------------
|
| Gets the kernel and shell environment variables, and stores to global
| variables (in this C program).
*/
void Get_Environment_Variables()
{
    USER = Get_Environment_Variable_Value(ENV_VAR_USER);
    HOME_FOLDER = Get_Environment_Variable_Value(ENV_VAR_HOME);
    HOSTNAME = Get_Environment_Variable_Value(ENV_VAR_HOSTNAME);
    printf(COLOR_BOLD_YELLOW "ENVIRONMENT VARIABLES:\n" COLOR_RESET);
    printf("\t$ %s: %s\n", ENV_VAR_USER, USER);
    printf("\t$ %s: %s\n", ENV_VAR_HOME, HOME_FOLDER);
    printf("\t$%s: %s\n", ENV_VAR_HOSTNAME, HOSTNAME);
}

/*
|--------------------------------------------------------------------------
| Get_Environment_Variable_Value
|--------------------------------------------------------------------------
|
| Get the value of an environment variable using the getenv command.
| The environment variable string is passed as an argument. A string
| of the value is returned.
|
| @param:  env_variable    the environment variable to retrieve the value of
| @return:                 a string of the value is returned
*/
char* Get_Environment_Variable_Value(char* env_variable)
{
  int BUFSIZE = 100;
  char env_value[BUFSIZE];


  if(!getenv(env_variable))   // verify string passed in is an env_variable that exists
  {
      Echo_Env_Variable(env_variable, env_value);   // if getenv can't find it, Echo the variable using shell to get value
      if(env_value == NULL)
      {
        fprintf(stderr, "The environment variable $%s was not found.\n", env_variable);
        return 0;
      }
      else return strdup(env_value);
  }

  // copy environment variable value into "env_value"
  if(snprintf(env_value, BUFSIZE, "%s", getenv(env_variable)) >= BUFSIZE)
  {
      fprintf(stderr, "BUFSIZE of %d was too small. Aborting\n", BUFSIZE);
      return 0;
  }

  return strdup(env_value);
}


/*
|--------------------------------------------------------------------------
| Exec_Shell_Command
|--------------------------------------------------------------------------
|
| Execute a command at the terminal prompt. The command is passed as argument.
| A string of the shell output response is returned. The string captures
| stdout and stderr.
|
| @param:  command    the shell command to execute
| @return:            a string of the shell response is returned
*/
char** Exec_Shell_Command(char* command)
{
    int MAX_LINES = 100;
    int MAX_LINE_LENGTH = 150;
    char read_line[250];

    FILE* command_shell = popen(command, POPEN_READ);                 //  The popen() function opens a process by creating a pipe, forking and invoking the shell.
    if (command_shell == NULL)
    {
        printf("Error opening pipe for shell command!!\n" );
        exit(1);
    }

    int line_count = 0;
    char**  string_array = malloc(sizeof(char*) * MAX_LINES);        // allocate memory for pointer to strings
    while (fgets(read_line, sizeof(read_line), command_shell) != NULL)     /* Read the output a line at a time - output it. */
    {
        Trim_Trailing_WhiteSpace(read_line);
        printf("LINE:\t%s\n", read_line);
        //string_array[line_count] = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH); // allocate memory for the
		string_array[line_count] = (char*)malloc(sizeof(char) * ( strlen(read_line) +10 ) ); // allocate memory for the return string
        strcpy(string_array[line_count], read_line);
        ++line_count;
    }
    string_array[line_count] = NULL;   // Add a marker for the last string in the array
    pclose(command_shell);     // close file pointer to STDOUT
    return string_array;
}

void Free_String_Array_Memory(char** string_array)
{
    int i = 0;
    while(string_array[i] != NULL)
    {
        free(string_array[i]);
        //printf("free string\n");
        ++i;
    }
    free(string_array);
    //printf("free array\n");

    return;
}

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
char* Shell_List_Files(char* path)
{
  unsigned char filetype;
  struct dirent *directory_entry;   // Pointer for directory entry
  DIR *directory = opendir(path);   // opendir() returns a pointer of DIR type.

  if (directory == NULL)  // opendir returns NULL if couldn't open directory
  {
      printf("Could not open directory: %s\n", path);
      return 0;
  }

  printf("\nLIST FILES:\n");
  printf(LINE_SEPARATOR);
  printf("ls %s\n", path);
  while ((directory_entry = readdir(directory)) != NULL)
  {
      filetype = directory_entry->d_type;
      if(filetype == DT_REG)
      {
            printf("\t%s\n", directory_entry->d_name);
      }
  }
  printf(LINE_SEPARATOR);

  closedir(directory);
  return 0;
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


//___________Helper Functions Below_______________________________________________________________________________________


//  Searches through string_list searching for string_to_match
// returns whether a match is found
bool String_List_Contains(char** string_list, char* string_to_match)
 {
    bool contains = false;

    int i = 0;
    while( string_list[ i ] != NULL)
    {
        if( String_Equals_String( string_list[ i ], string_to_match ) )
        {
            contains = true;
            break;
        }
        else
        {
            ++i;
            continue;
        }
    }

    return contains;
 }


 void Enable_Desktop_Autologin(char* USERNAME)
 {
   char command_find_and_replace[200];
   char** response_string;

   sprintf(command_find_and_replace, "sudo sed -i -e '/autologin-user/s/=[a-zA-Z0-9]*/=%s/' /etc/lightdm/lightdm.conf", USERNAME);  // command to replace previous autologin user with USERNAME
   response_string = Exec_Shell_Command(command_find_and_replace);                                                                 // execute the find and replace command
   Free_String_Array_Memory(response_string);                                                                                      // free the memory allocated for return string "current_line"
 }

 void Enable_Console_Autologin(char* USERNAME)
 {
   char command_find_and_replace[200];
   char** response_string;
   char regex_expression_autologin[] = "s/ExecStart=-\\/sbin\\/agetty --autologin[ ][a-zA-Z0-9]*[ ]/ExecStart=-\\/sbin\\/agetty --autologin ";
   sprintf(command_find_and_replace, "sudo sed -i -e '%s%s /' /etc/systemd/system/autologin@.service", regex_expression_autologin, USERNAME); // find and replace command. Find using regular expression
   Exec_Shell_Command(command_find_and_replace);
   response_string = Exec_Shell_Command(command_find_and_replace);                                                                 // execute the find and replace command
   Free_String_Array_Memory(response_string);                                                                           // Execute find and replace command
 }

 void Get_Desktop_Autologin_File_Entry(char* get_line)
 {
   char command_get_original_line[200];
   char** current_line;
   sprintf(command_get_original_line, "sudo sed -n '/autologin-user=/p' /etc/lightdm/lightdm.conf");       // command to search file /etc/lightdm/lightdm.conf for line:   autologin-user=[user]
   current_line = Exec_Shell_Command(command_get_original_line);                                           // execute the search command
   strcpy(get_line, current_line[0]);                                                                      // copy line to return string location
   Free_String_Array_Memory(current_line);                                                                 // free the memory allocated for return string "current_line"
 }


 void Get_Desktop_Autologin_User(char* get_user)
 {
   char command_get_original_user[200];
   char** current_user;
   sprintf(command_get_original_user, "sudo sed -n -e 's/autologin-user=\\([a-zA-Z]*\\)/\\1/p' /etc/lightdm/lightdm.conf");  // command to search file /etc/lightdm/lightdm.conf
   current_user = Exec_Shell_Command(command_get_original_user);                                                             // execute the search command
   strcpy(get_user, current_user[0]);
   Free_String_Array_Memory(current_user);
 }


 void Get_Console_Autologin_User(char* get_user)
 {
   char command_get_original_user[200];
   char** current_user;
   sprintf(command_get_original_user, "sudo sed -n -e 's/ExecStart=-[/]\\{1\\}sbin[/]\\{1\\}agetty --autologin \\([a-zA-Z]*\\)/\\1/p' /etc/systemd/system/autologin@.service | sed -ne 's/[ ]\\{1\\}.*//p'");
   current_user = Exec_Shell_Command(command_get_original_user);                                                     // execute command searching for current user (before changing in file)
   strcpy(get_user, current_user[0]);
   Free_String_Array_Memory(current_user);
 }


 void Get_Console_Autologin_File_Entry(char* get_line)
 {
   char command_get_original_line[200];
   char** current_line;
   sprintf(command_get_original_line, "sudo sed -n '/agetty --autologin /p' /etc/systemd/system/autologin@.service"); // string of command to search for orginal line in file (which we will modify)
   current_line = Exec_Shell_Command(command_get_original_line);                                                      // Execute the command
   strcpy(get_line, current_line[0]);
   Free_String_Array_Memory(current_line);                                                                           // free memory allocated for return string
 }


 /*
 |--------------------------------------------------------------------------
 | Parse_KBD_Country_Code
 |--------------------------------------------------------------------------
 |
 | Parses the country code from a string passed in as an argument. The country code comes from the file /etc/default/keyboard.
 | In the 'keyboard' file is a line:
 |       XKBLAYOUT=[country code]
 | Where country code is a two letter designation. The line "XKBLAYOUT=[country code]" should be passed as an argument to this function.
 | To parse the code, first the position of the '=' is located, then everything after that is copied to the return string
 |
 | @param    read_line   line parsed from keyboard file. Should contain the line "XKBLAYOUT=us"
 |
 | @returns              string of the country code
 |
 */
 char* Parse_KBD_Country_Code(char* read_line)
 {
     int parse_index = 0;
     char country_code[20];

     // Find the character position of the '=', then grab everything after it
     for(int i = 0; i<strlen(read_line); ++i)
     {
         if(read_line[i] == '=')
         {
             parse_index = i+1; // start copying at first character after the equals sign
             break;
         }
     }

     // copy the rest of the string into the return string. The copied characters are the "country_code"
     int copy_index = 0;
     for(parse_index; parse_index<strlen(read_line); ++parse_index)
     {
         if(read_line[parse_index] == '\n')  // don't copy a newline from the string, not necessary
             break;
         country_code[copy_index] = read_line[parse_index];
         ++copy_index;
     }
     country_code[copy_index] = '\0'; // add null terminating character to return string
     return strdup(country_code);
 }



 /*
 |--------------------------------------------------------------------------
 | Search_String_in_File
 |--------------------------------------------------------------------------
 |
 | Search the file given as an argument, looking for line given by match_string.
 | Checks the line is not pre-pended by a '#', (which comments out the line)
 |
 | @param:   filename      the path to the file to search
 | @return:  match_string  the string/line to search for in the file to verify is present in the file
 |                          true is returned for string_present, false for string_absent
 */
 bool Search_String_in_File(char *filename, char *match_string)
 {
 	FILE *file_pointer;
 	bool found_match = false;
 	char read_line[512];
   int line_num = 1;

 	if( (file_pointer = fopen(filename, "r")) == NULL )
   {
       printf("couldn't open file\n");
       printf("%s\n", filename);
 		  return(-1);
 	}

 	while( fgets(read_line, 512, file_pointer) != NULL )
   {
 		  if( String_Equals_String(match_string, read_line) )
       {
           if(read_line[0] == '#')   // if '#' begins a line in a file, the line is commented out and thus not active in the file
             break;
           //printf("match found, line: %d\t%s\n", line_num, match_string);
           printf("\t\t%s \t", match_string);
           printf(CHECKMARK_CHARACTER);
           printf("\n");
 			    found_match = true;
           fclose(file_pointer);
           return found_match;
 		  }
 		  line_num++;
 	}

 	if(found_match == false)
   {
 		printf("\nSorry, no match for '%s'.\t" CROSS_CHARACTER "\n", match_string);
 	}
 	fclose(file_pointer);
   return found_match;
 }

 bool String_Equals_String(char* target_string, char* input_string)
 {
     char string1[ strlen(target_string) +1];
     char string2[ strlen(input_string) +1];

     strcpy(string1, target_string);
     strcpy(string2, input_string);

     Trim_Leading_WhiteSpace(string1);
     Trim_Trailing_WhiteSpace(string1);

     Trim_Leading_WhiteSpace(string2);
     Trim_Trailing_WhiteSpace(string2);

     int string_length = strlen(string1);
     char character;
     int index = 0;
     bool equals = true;

     for(; index < string_length; ++index)
     {
         if(string1[index] != string2[index] && string2[index] != '\n' && string1[index] != ' ')
         {
             equals = false;
             //printf("target \"%s\" does not match \"%s\" at index %d\nASCII hex character %d[%c] != %d[%c]\n\n", string1, string2, index, string1[index], string1[index], string2[index], string2[index]);
             return equals;
         }
     }
     //printf("strlen: %d, target string, %s, input_string, %s\tequals: %d\n", string_length, target_string, input_string, equals);
     return equals;
 }

 void Trim_Leading_WhiteSpace(char* str)
 {
     int start_index=0, new_index=0, old_index=0;

     // find index of first non-whitespace character
     while(str[start_index] == ' ' || str[start_index] == '\t' || str[start_index] == '\n')
     { ++start_index;  }

     if(start_index != 0)
     {
         // copy all characters over to the left
         old_index = start_index;
         while( str[ old_index ] != '\0' )
         {
             str[ new_index ] = str[ old_index ];
             ++new_index;
             ++old_index;
         }
         str[new_index] = '\0'; // Make sure that string is NULL terminated
     }
 }

 void Trim_Trailing_WhiteSpace(char * str)    // removes trailing whitespace (spaces and newlines)
 {

   int stringLen = strlen(str);
   while(stringLen > 0 && isspace(str[stringLen -1]) )
   {
     stringLen--;
   }
   str[stringLen] = '\0';
 }

 char** parseUsers(char** long_user_list, int uid_min, int uid_max)
 {
   int MAX_LINE_LENGTH = 150;          // max number of characters in a single line of the response from "getent passwd"
   int MAX_REGULAR_USERS = 20;         // max number of filtered users
   int MAX_USERNAME_LENGTH = 50;       // max number of characters in the name from a user in the filtered list
   char** regular_user_list = malloc(sizeof(char*) * MAX_REGULAR_USERS);   //  allocate memory for list of users that meet filter reqts

   int i = 0, user_count = 0;

   while( long_user_list[ i ] )
   {
       int UID = parseInt( long_user_list[ i ] );
       if( uid_min <= UID && UID <= uid_max )
       {
           regular_user_list[ user_count ] = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH ); // allocate memory for the
           strcpy( regular_user_list[ user_count ], long_user_list[ i ] );
           ExtractUserName( regular_user_list[ user_count ] );
           //printf("\t%s\n", regular_user_list[ user_count ] );
           ++user_count;
       }
       ++i;
   }
   regular_user_list[ user_count ] = NULL;   // Add a marker for the last string in the array

   return regular_user_list;
 }


 //  takes in username of the form: pi:x:1000:1000:,,,:/home/pi:/bin/bash
 //  extracts only the "pi" part
 void ExtractUserName(char* long_user_string)
 {
     for( int i=0; i < strlen( long_user_string); ++i)
     {
         if( long_user_string[i] == ':')
         {
             long_user_string[i] = '\0';
             break;
         }
         else
             continue;
     }

     return;
 }

 int parseInt(char* integer_string)
 {

   Trim_Trailing_WhiteSpace(integer_string);

   // Get index of start of integer portion. Could be a digit or + or -
   int start_index = 0;
   for(int i = 0; i<strlen(integer_string); ++i )
   {
       if(integer_string[i] == '+' || integer_string[i] == '-')
       {
           if( isdigit(integer_string[i+1]) )
           {
               start_index = i;
               break;
           }
       }
       if( isdigit(integer_string[i]) )
       {
           start_index = i;
           break;
       }
   }

   // get index of last digit
   int end_index = start_index;    // start search of last "digit" character at the beginning of the integer portion
   char first_character = integer_string[end_index];

   if( first_character == '+' || first_character == '-' )  // if the first char is a sign, move on to the digits
       end_index = start_index + 1;
   else
       end_index = start_index;

   for(int i=0; i<strlen(integer_string); ++end_index )
   {
       if( isdigit( integer_string[end_index] ) )
           continue;
       else
           break;
   }

   // Copy Substring from start_index to end index
   char integer_substring[end_index - start_index +1];     // create temp storage for the substring
   for( int i = 0; i< (end_index - start_index +1); ++i)
   {
       integer_substring[i] = integer_string[i + start_index];
   }
   integer_substring[ strlen(integer_substring) ] = '\0';    // add null terminating character

   char* end_ptr;
   int parsed_int = strtol(integer_substring, &end_ptr, 10);   // parse the substring to integer using stringtolong function

   return parsed_int;
 }


 double parseDouble(char* integer_string)
 {

   Trim_Trailing_WhiteSpace(integer_string);

   // Get index of start of integer portion. Could be a digit or + or -
   int start_index = 0;
   for(int i = 0; i<strlen(integer_string); ++i )
   {
       if(integer_string[i] == '+' || integer_string[i] == '-')
       {
           if( isdigit(integer_string[i+1]) )
           {
               start_index = i;
               break;
           }
       }
       if( isdigit(integer_string[i]) )
       {
           start_index = i;
           break;
       }
   }

   // get index of last digit
   int end_index = start_index;    // start search of last "digit" character at the beginning of the integer portion
   char first_character = integer_string[end_index];

   if( first_character == '+' || first_character == '-' )  // if the first char is a sign, move on to the digits
       end_index = start_index + 1;
   else
       end_index = start_index;

   for(int i=0; i<strlen(integer_string); ++end_index )
   {
       if( isdigit( integer_string[end_index] ) )
           continue;
       else
       {
           if( integer_string[end_index] == '.' && isdigit( integer_string[ end_index +1 ] ) )
               continue;
           else
               break;
       }
   }

   // Copy Substring from start_index to end index
   char integer_substring[end_index - start_index +1];     // create temp storage for the substring
   for( int i = 0; i< (end_index - start_index +1); ++i)
   {
       integer_substring[i] = integer_string[i + start_index];
   }
   integer_substring[ strlen(integer_substring) ] = '\0';    // add null terminating character

   char* end_ptr;
   double parsed_double = strtod(integer_substring, &end_ptr);   // parse the substring to integer using stringtolong function

   return parsed_double;
 }

 bool String_Contains(char* base_string, char* match_string)
 {
     return strstr(base_string, match_string); // strstr returns a substring
 }

 void Erase_String_Contents(char* string)
 {
   memset(string,0,sizeof(string));    // zero out string memery locations
   string[0] = '\0';           // add null terminator
 }

 bool Verify_File_Exists(char* filepath)
 {
     if( access( filepath, F_OK ) != -1 )
         return true;
     else
         return false;
 }

 // Must free memory after this function
 char* Get_Substring(char* full_string, int start_index, int end_index)
 {
   int substring_length = end_index - start_index;
   char* substring = (char*)malloc(sizeof(char) * substring_length); // allocate memory for the substring

   Erase_String_Contents(substring);
   // Copy Substring from start_index to end index

   for( int i = 0; i< (end_index - start_index +1); ++i)
   {
       substring[i] = full_string[i + start_index];
   }

   substring[ substring_length+1 ] = '\0';    // add null terminating character
   return substring;
 }


 /*
 |--------------------------------------------------------------------------
 | Echo_Env_Variable
 |--------------------------------------------------------------------------
 |
 | Get the value of a shell variable that isnt returned with "printenv" or
 | "getenv". This function uses the "echo" shell command to retrieve the
 | value of the shell variable. The output is parsed from stdout
 |
 | @param:  variable    the environment variable to retrieve the value of
 | @param:  value       string to store the return value of environment variable
 | @return: values      return value is stored
 */
 void Echo_Env_Variable(char* variable, char* value)
 {
     char command[100];
     strcpy(command, "echo $");
     strcat(command, variable);
     char** response;

     response = Exec_Shell_Command(command);
     strcpy(value, response[0]);
     Free_String_Array_Memory(response);
 }

 char* Get_File_Suffix(char* filepath)
 {
     int index_first_period;

     for(int i=0; i < strlen(filepath); ++i)
     {
         char current_char = filepath[i];
         if( isalpha(current_char) || isdigit(current_char) || current_char == '/')
             continue;
         if( filepath[i] == '.' && filepath[i+1] == '/')
             continue;
         if( current_char == '.' )
         {
             index_first_period = i;
             break;
         }
     }

     return Get_Substring(filepath, index_first_period, strlen(filepath)-1);

 }
