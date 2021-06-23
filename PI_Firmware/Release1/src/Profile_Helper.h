
#ifndef PROFILE_HELPER
#define PROFILE_HELPER

#include "Struct_Defs.h"
#include "Timer_Helper.h"
#define MAX_NUM_PROFILE_COMMANDS 100


FILE* Open_File(char* filename);
char* Read_Line(FILE* file_pointer);
profile_object* Parse_Profile(char* path);
bool Parse_Profile_Header(profile_object* parse_file, FILE* file);
bool End_of_Header(char* line);
void Profile_Parse_Add_Response(profile_object* parse_file, char* response);
profile_t String_to_Profile_Type(char* string);
profile_key_t Profile_String_to_Key(char* string);
void Print_Profile(profile_object* profile_obj);
profile_command** Parse_Profile_Commands(profile_object* parse_file, FILE* file);
profile_command_t Parse_Profile_Command(char* string);
bool Profile_CMD_Has_Valid_Argument( profile_command_t cmd, char* cmd_arg_str );
void Print_Profile_Commands(profile_command** cmd_list);
void Print_Profile_Command(profile_command* cmd);

extern long Time_String_to_Seconds(char* time_string);  // in Timer_Helper.h
extern bool Is_Valid_Time_Argument(char* time_str);
extern int Parse_Hour(char* time_string);
extern int Parse_Minute(char* time_string);
extern int Parse_Second(char* time_string);



// make sure to free any previous profile memory

profile_object* Parse_Profile(char* path)
{
    // verify file extension is .profile
    // examine each line make sure first token is valid command
    // make sure second token is either timestamp or load value depending on command
    profile_object* Parse_File;
    Parse_File = (profile_object*)malloc( sizeof(struct profile_object) );
    Parse_File->filename = (char*)malloc( sizeof(char*) * strlen(path) +100);
    strcpy(Parse_File->filename, path);
    Parse_File->parse_response = (char**)malloc( sizeof(char*) * MAX_NUM_PROFILE_COMMANDS);   // initialize string array by allocating memory. Has space for MAX_NUM_PROFILE COMMANDS # of string lines
    Parse_File->parse_success = false;                                                       // initialize to false until the file has been validated
    Parse_File->response_index = 0;
    Parse_File->store_index = 0;

    FILE* profile_file = Open_File(path);
    if(profile_file == NULL)
        Profile_Parse_Add_Response(Parse_File, "cannot open profile file");
    bool valid_header = Parse_Profile_Header(Parse_File, profile_file);

    if( !valid_header)
    {
        Print_String_Array( Parse_File->parse_response );
        Parse_File->parse_success = false;
        Profile_Parse_Add_Response(Parse_File, "could not parse profile header" );
    }
    Parse_Profile_Commands(Parse_File, profile_file);
    Print_Profile( Parse_File);
    fclose(profile_file);
    return Parse_File;
}

void Print_Profile(profile_object* profile_obj)
{
    printf("print profile\n");
    printf("Filename: \t%s\n", profile_obj->filename );
    printf("Profile Name: \t%s\n", profile_obj->name );
    printf("Profile Type: \t");
    switch(profile_obj->type)
    {
        case LIFETIME:
            printf("LIFETIME\n");
            break;
        case PERFORMANCE:
            printf("PERFORMANCE\n");
            break;
        case SADA:
            printf("SADA\n");
            break;
        case BURNIN:
            printf("BURNIN\n");
            break;
        case CUSTOM:
            printf("CUSTOM\n");
            break;
        case PROFILE_NO_MATCH:
            printf("NO_MATCH\n");
            break;
    }
    printf("Description: \t%s\n", profile_obj->description );
    Print_String_Array( profile_obj->parse_response );
    printf("________________________________________________________________\n");

    Print_Profile_Commands(profile_obj->cmd_list);
}


void Print_Profile_Commands(profile_command** cmd_list)
{
    int i = 0;
    printf("Print Command List\n");
    while( cmd_list[i] != NULL)
    {
        switch( cmd_list[i]->profile_cmd)
        {
            case PROFILE_START_LOG:
                printf("--START_LOG\n");
                printf("\tExecute time: %s\n", cmd_list[i]->time_execute_str);
                printf("\tExecute @ seconds: %ld\n", cmd_list[i]->execute_time_seconds);
                break;
            case PROFILE_RELAY_ON:
                printf("--RELAY_ON\n");
                printf("\tExecute time: %s\n", cmd_list[i]->time_execute_str);
                printf("\tExecute @ seconds: %ld\n", cmd_list[i]->execute_time_seconds);
                break;
            case PROFILE_RELAY_OFF:
                printf("--RELAY_OFF\n");
                printf("\tExecute time: %s\n", cmd_list[i]->time_execute_str);
                printf("\tExecute @ seconds: %ld\n", cmd_list[i]->execute_time_seconds);
                break;
            case PROFILE_SET_LOAD:
                printf("--SET_LOAD\n");
                printf("\tLoad mW: %f\n", cmd_list[i]->load_setting_mW);
                break;
            case PROFILE_LOAD_ON:
                printf("--LOAD_ON\n");
                printf("\tExecute time: %s\n", cmd_list[i]->time_execute_str);
                printf("\tExecute @ seconds: %ld\n", cmd_list[i]->execute_time_seconds);
                break;
            case PROFILE_LOAD_OFF:
                printf("--LOAD_OFF\n");
                printf("\tExecute time: %s\n", cmd_list[i]->time_execute_str);
                printf("\tExecute @ seconds: %ld\n", cmd_list[i]->execute_time_seconds);
                break;
            case PROFILE_STOP_TEST:
                printf("--STOP_TEST\n");
                printf("\tExecute time: %s\n", cmd_list[i]->time_execute_str);
                printf("\tExecute @ seconds: %ld\n", cmd_list[i]->execute_time_seconds);
                break;
        }
        ++i;
    }
}

void Print_Profile_Command(profile_command* cmd)
{
        switch( cmd->profile_cmd)
        {
            case PROFILE_START_LOG:
                printf("--START_LOG\n");
                printf("\tExecute time: %s\n", cmd->time_execute_str);
                printf("\tExecute seconds: %ld\n", cmd->execute_time_seconds);
                break;
            case PROFILE_RELAY_ON:
                printf("--RELAY_ON\n");
                printf("\tExecute time: %s\n", cmd->time_execute_str);
                printf("\tExecute seconds: %ld\n", cmd->execute_time_seconds);
                break;
            case PROFILE_RELAY_OFF:
                printf("--RELAY_OFF\n");
                printf("\tExecute time: %s\n", cmd->time_execute_str);
                printf("\tExecute seconds: %ld\n", cmd->execute_time_seconds);
                break;
            case PROFILE_SET_LOAD:
                printf("--SET_LOAD\n");
                printf("\tLoad mW: %f\n", cmd->load_setting_mW);
                break;
            case PROFILE_LOAD_ON:
                printf("--LOAD_ON\n");
                printf("\tExecute time: %s\n", cmd->time_execute_str);
                printf("\tExecute seconds: %ld\n", cmd->execute_time_seconds);
                break;
            case PROFILE_LOAD_OFF:
                printf("--LOAD_OFF\n");
                printf("\tExecute time: %s\n", cmd->time_execute_str);
                printf("\tExecute seconds: %ld\n", cmd->execute_time_seconds);
                break;
            case PROFILE_STOP_TEST:
                printf("--STOP_TEST\n");
                printf("\tExecute time: %s\n", cmd->time_execute_str);
                printf("\tExecute seconds: %ld\n", cmd->execute_time_seconds);
                break;
        }


}

void Profile_Parse_Add_Response(profile_object* parse_file, char* response)
{
    if( (response != NULL) && (strlen(response) >= 1) )
    {
        int cur_index = parse_file->response_index;
        parse_file->parse_response[ cur_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 2);
        strcpy(parse_file->parse_response[ cur_index ], response);
        ++parse_file->response_index;
    }
    return;
}

bool Parse_Profile_Header(profile_object* parse_file, FILE* file)
{
    // ignore lines starting w/ "//" or #
    // look for  PIBB_Profile_Definition_File or PIBB Profile Definition File
    // look for Profile_Type: key & associated value. must be [Lifetime | Performance | SADA | BurnIn | Custom]
    // look for Profile_Name: key & associated value
    // look for description key & associated value
    // look for line separator (min number of underscores)

    bool declaration_line_present = false;
    bool profile_type_present = false;
    bool profile_name_present = false;
    bool profile_description_present = false;

    char* read_line = Read_Line( file );
    char* value;
    char* key_str;

    while( !End_of_Header(read_line) )
    {
        if( Is_Comment(read_line) )
        {
            free(read_line);
            read_line = Read_Line( file );    // get next line
            continue;
        }

        key_str = Extract_Key_in_String( read_line );
        if( key_str == NULL )
        {
            int string_size = strlen(read_line) + strlen("Error parsing key from line:  ") + 8;
            char add_response_str[ string_size ];
            sprintf( add_response_str, "%s Error parsing key from line:  %s", X_ERROR, read_line);
            Profile_Parse_Add_Response( parse_file, add_response_str );
            free(read_line);
            read_line = Read_Line( file );    // get next line
            continue;
        }

        profile_key_t key = Profile_String_to_Key(key_str);
        //printf("\tkey: \"%s\"\n", key_str);

        if( key != PROFILE_DECLARATION)   // profile declaration is not a key value pair, just a file entry, so dont need to extract a value
        {
            value = Extract_Value_in_String( read_line );
            //printf("readline: %s \tvalue: %s\n", read_line, value);
            if( value == NULL )
            {
                int string_size = strlen(read_line) + strlen("Error parsing value from line:  ") + 2;
                char add_response_str[ string_size ];
                sprintf( add_response_str, "%s Error parsing value from line:  %s", X_ERROR, read_line);
                Profile_Parse_Add_Response( parse_file, add_response_str );
                free(read_line);
                read_line = Read_Line( file );    // get next line
                continue;
            }
        }

        switch( key )
        {
            case PROFILE_DECLARATION:
              declaration_line_present = true;
              break;

            case PROFILE_TYPE:
              profile_type_present = true;
              parse_file->type = String_to_Profile_Type( value );
              Profile_Parse_Add_Response( parse_file, "parsed profile type correctly");
              break;

            case PROFILE_NAME:
              profile_name_present = true;
              parse_file->name = value;
              Profile_Parse_Add_Response( parse_file, "parsed profile name correctly");
              break;

            case PROFILE_DESCRIPTION:
              profile_description_present = true;
              parse_file->description = value;
              Profile_Parse_Add_Response( parse_file, "parsed profile description correctly");
              break;

            case PROFILE_KEY_UNKNOWN:
              printf("key unknown\n");
              break;
        }
        free(read_line);
        read_line = Read_Line( file );    // get next line
    }

    if( !declaration_line_present )
        Profile_Parse_Add_Response( parse_file, "missing Header line: 'PIBB_Profile_Definition_File' ");

    if( declaration_line_present && profile_type_present && profile_name_present && profile_description_present)
        return true;
    else
        return false;
}

profile_key_t Profile_String_to_Key(char* string)
{

    if( String_Contains( string, "PIBB_Profile_Definition_File"))
        return PROFILE_DECLARATION;
    else if( String_Equals_Ignore_Case( string, "Profile_Type") )
        return PROFILE_TYPE;
    else if( String_Equals_Ignore_Case( string, "Profile_Name") )
        return PROFILE_NAME;
    else if( String_Equals_Ignore_Case( string, "Profile_Description") )
        return PROFILE_DESCRIPTION;
    else
        return PROFILE_KEY_UNKNOWN;
}

profile_t String_to_Profile_Type(char* string)
{
    if( String_Equals_Ignore_Case(string, "LIFETIME" ) )
        return LIFETIME;
    else if( String_Equals_Ignore_Case(string, "PERFORMANCE" ) )
        return PERFORMANCE;
    else if( String_Equals_Ignore_Case(string, "SADA" ) )
        return SADA;
    else if( String_Equals_Ignore_Case(string, "BURNIN" ) )
        return BURNIN;
    else if( String_Equals_Ignore_Case(string, "CUSTOM" ) )
        return CUSTOM;
    else
        return NO_MATCH;
}

//  VERIFY ALL PROFILE COMMAND TIMES ARE SUCCESIVE
// precondition: file pointer is past line separator delimiter
// read each line at a time
// verify command
// after parsing the command validate the argument
// if argument and command are good put the results in struct
// if error, stop
profile_command** Parse_Profile_Commands(profile_object* parse_file, FILE* file)
{
    parse_file->cmd_list = (profile_command**)malloc( sizeof(profile_command*) * MAX_NUM_PROFILE_COMMANDS); // Allocate memory for the command list (array of profile commands)
    int store_index = parse_file->store_index;

    char* line;
    char* cmd_str;
    char* cmd_arg_str;

    line = Read_Line(file);
    while( line != NULL )
    {
        cmd_str = Parse_Key(line);
        profile_command_t profile_cmd = Parse_Profile_Command( cmd_str );

        if( profile_cmd == PROFILE_COMMAND_UNKNOWN )
        {
            parse_file->parse_success = false;
            int string_size = strlen(line) + strlen("Error parsing CMD from line:  ") + 6;
            char add_response_str[ string_size ];
            sprintf( add_response_str, "%s Error parsing key from line:  %s", X_ERROR, line);
            Profile_Parse_Add_Response( parse_file, add_response_str );
            line = Read_Line( file );    // get next line
            continue;
        }

        cmd_arg_str = Parse_Value(line);
        int time_start_index = Get_Index_Open_Bracket(cmd_arg_str);
        int time_end_index = Get_Index_Closed_Bracket(cmd_arg_str);
        char* time_string = Get_Substring( cmd_arg_str, time_start_index+1, time_end_index-1);

        if( Profile_CMD_Has_Valid_Argument(profile_cmd, cmd_arg_str) )
        {
            store_index = parse_file->store_index;
            parse_file->cmd_list[ store_index ] = (profile_command*)malloc( sizeof(profile_command*) );
            parse_file->cmd_list[ store_index ]->profile_cmd = profile_cmd;

            if( profile_cmd == PROFILE_SET_LOAD )
            {
                parse_file->cmd_list[ store_index ]->load_setting_mW = Parse_Double( cmd_arg_str);
                //printf("cmd_str %s\n", cmd_str);
                //printf("arg_str %s\n", cmd_arg_str);
            }
            else
            {
                //printf("cmd_str %s\n", cmd_str);
                //printf("arg_str %s\n", cmd_arg_str);
                parse_file->cmd_list[ store_index ]->time_execute_str = time_string;
                parse_file->cmd_list[ store_index ]->execute_time_seconds = Time_String_to_Seconds(time_string);
            }
            //printf("")
            ++parse_file->store_index;
        }
        else
        {
            parse_file->parse_success = false;
            int string_size = strlen(line) + strlen("Error parsing key from line:  ") + 6;
            char add_response_str[ string_size ];
            sprintf( add_response_str, "%s Error parsing key from line:  %s", X_ERROR, line);
            Profile_Parse_Add_Response( parse_file, add_response_str );
        }
        line = Read_Line(file);   // read in next line
    }
    parse_file->cmd_list[ parse_file->store_index ] = NULL;

    return parse_file->cmd_list;
    // for all tests but lifetime & custom, verify there is a stop test time
    // verify for every load on there is a load off
}




// if command is set_load, then argument must be of type double
// for any other command must be a time & time values must succeed one another
bool Profile_CMD_Has_Valid_Argument( profile_command_t cmd_type, char* cmd_arg_str )
{
    if( cmd_arg_str == NULL)
        return false;

    if( cmd_type == PROFILE_SET_LOAD )   // verify can parse arg to double value greater than 0
    {
        double arg = Parse_Double( cmd_arg_str );
        if( arg >= 0 )
            return true;
        else
            return false;
    }
    else // verify can parse to time value
    {
        if( Is_Valid_Time_Argument(cmd_arg_str) )
            return true;
        else
            return false;
    }
}


profile_command_t Parse_Profile_Command(char* string)
{
    if( string == NULL)
        return PROFILE_COMMAND_UNKNOWN;
    if( String_Equals_Ignore_Case( string, "START_LOG") )
        return PROFILE_START_LOG;
    else if( String_Equals_Ignore_Case( string, "RELAY_ON") )
        return PROFILE_RELAY_ON;
    else if( String_Equals_Ignore_Case( string, "RELAY_OFF") )
        return PROFILE_RELAY_OFF;
    else if( String_Equals_Ignore_Case( string, "SET_LOAD") )
        return PROFILE_SET_LOAD;
    else if( String_Equals_Ignore_Case( string, "LOAD_ON") )
        return PROFILE_LOAD_ON;
    else if( String_Equals_Ignore_Case( string, "LOAD_OFF") )
        return PROFILE_LOAD_OFF;
    else if( String_Equals_Ignore_Case( string, "STOP_TEST") )
        return PROFILE_STOP_TEST;
    else
        return PROFILE_COMMAND_UNKNOWN;
}


// the end of the file header is indicated by a separation line: "______________" across the screen
bool End_of_Header(char* line)
{
    Trim_Leading_WhiteSpace(line);
    int length = strlen(line);

    for(int i=0; i<length; ++i)
    {
        char ch = line[i];
        if( ch == '_' || ch == '-' || isspace(ch) )
            continue;
        else if( (ch == '\n') && (i >= 20) )
            return true;
        else
            return false;
    }
    return true;
}

// returns a string of next line in file
// if line is only whitespace skips to next line
char* Read_Line(FILE* file_pointer)
{
   	char read_line[512];
    int line_length = 0;

    do
    {
        if( fgets(read_line, 512, file_pointer) == NULL)
            return NULL;

        Trim_Leading_Trailing_Whitespace(read_line);
        line_length = strlen(read_line);
    }while(line_length <= 0);

    char* return_string = malloc( sizeof(char*) * strlen(read_line) + 2);
    strcpy(return_string, read_line);
    return return_string;
}

FILE* Open_File(char* filename)
{
   	FILE *file_pointer;

   	if( (file_pointer = fopen(filename, "r")) == NULL )
    {
         printf("couldn't open file: ");
         printf("%s\n", filename);
   		   return NULL;
   	}
    return file_pointer;
}


/*
// filename: lifetime_test.profile
	PIBB_Profile_Definition_File
	Profile_Type: Lifetime
	Profile_Name: lifetime_test
	Description:  testing long term performance of compressor
________________________________________________________________

START_LOG   [00:00:00]
RELAY_ON		[00:00:01]
SET_LOAD    [100.0] mW
LOAD_ON     [00:00:10]
LOAD_OFF    [00:00:15]
RELAY_OFF   [00:00:17]
STOP_TEST   [00:00:20]
*/
#endif
