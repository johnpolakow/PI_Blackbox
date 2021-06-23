
#ifndef STRING_HELPER
#define STRING_HELPER

#define DEBUG_TIMEDATE false
#define NOT_FOUND   -1

#include <stdbool.h>
#include "Macros.h"

void Trim_Leading_WhiteSpace(char* str);
void Trim_Trailing_WhiteSpace(char * str);
void Trim_Leading_Trailing_Whitespace(char * str);

int Index_First_Whitespace( char* socket_string );
int Index_of_Decimal(char* string);

char* Parse_First_Token(char* socket_string);
char* Parse_Second_Token(char* socket_string);
double Parse_Double(char* double_string);
int Parse_Int(char* integer_string);

bool Contains_Only_Digits(char* digit_string);
bool String_Is_Double(char* double_string);
bool String_Is_Int(char* double_string);
bool String_Is_TimeDate(Instruction_Info* socket_instruction);
bool String_Equals_Ignore_Case(char* socket_string, const char* command_entry);
bool String_Contains(char* haystack, char* needle);
bool String_Array_Contains(char** haystack, char* needle);


char* Get_Substring(char* full_string, int start_index, int end_index);
void Erase_String_Contents(char* string);
char* Get_File_Extension(char* filename);
bool String_Is_Filename(char* filename);
char* Search_Key_Value_in_File(char *filename, char *heading);


int Index_First_Colon( char* string );
char* Parse_Key(char* string);
char* Parse_Value(char* string);
char* Extract_Key_in_String(char* line);
char* Extract_Value_in_String(char* line);

bool Is_Comment(char* string);
int Get_Index_Open_Bracket(char* str);
int Get_Index_Closed_Bracket(char* str);
void Free_String_Array_Memory(char** string_array);
bool String_Contains_Ignore_Case(char* haystack, char* needle);



bool String_Equals_Ignore_Case(char* socket_string, const char* command_entry)
{
    // ignore case
    // compare letters up until whitespace
    if(strlen(socket_string) != strlen(command_entry))
        return false;

    //printf("compare: %s\t to %s\n", socket_string, command_entry);
    int cur_index = 0;
    int index_whitespace = Index_First_Whitespace( socket_string );               // first character of whitespace

    while( (cur_index < index_whitespace) && socket_string[ cur_index ] != '\0')                                         // examine each character and determine if it matches
    {
        char cur_char_upper = toupper( socket_string[ cur_index ] ); // if lowercase, convert socket_string character to uppercase, so doesnt matter in comparison
        char match_char = toupper(command_entry[ cur_index ] );
        if( cur_char_upper != match_char )
        {
            //printf("%s does not match %s at index %d, \t %c != %c\n", socket_string, command_entry, cur_index, cur_char_upper, command_entry[ cur_index ] );
            return false;
        }
        ++cur_index;
    }
    if( strlen(command_entry) > cur_index)   // if the unknown string is shorter than the valid string it is supposed to match
        return false;
    return true;
}

int Index_First_Whitespace( char* socket_string )
{
    int index = 0;
    for( index = 0; socket_string[ index ] != '\0'; ++index)
    {
        char cur_char = socket_string[index];
        if( isspace(cur_char) )              // isspace() returns true for: space, tab, newline, form feed, carriage return, vertical tab
            break;
    }
    return index;
}

int Index_Second_Whitespace( char* socket_string )
{
    int index = 0;
    bool passed_first_whitespace = false;
    for( index = 0; socket_string[ index ] != '\0'; ++index)
    {
        char cur_char = socket_string[ index ];
        char next_char = socket_string[ index+1 ];
        if( isspace(cur_char) && !passed_first_whitespace && !isspace(next_char) )      // mark flag for first whitespace
            passed_first_whitespace = true;
        else if( isspace(cur_char) && passed_first_whitespace )                         // exit on second whitespace
        {
            break;
        }
        else
            continue;
    }
    return index;
}

int Index_First_Colon( char* string )
{
    int index = 0;
    for( index = 0; string[ index ] != '\0'; ++index)
    {
        char cur_char = string[index];
        if( cur_char == '[' && isspace( string[index-1] ) )   // handles case of no colon separating key and value, just a space
          return index-2;
        if( cur_char == ':' )
            break;
    }
    return index;
}
/*
 |--------------------------------------------------------------------------
 | Search_Key_Value_in_File
 |--------------------------------------------------------------------------
 |
 | Search the file given as an argument, looking for line which begins with 'heading' argument.
 | Returns the 'entry' which is the remaining line after 'heading'. Ignores lines beginning w/ "//" or "#".
 | If not found return NULL.
 | For example:
 | // testfile.txt //
 | heading1: entry1
 | heading2: entry2
 | heading3: entry3
 | heading4: entry4
 |
 | @param:   filename      the path to the file to search
 | @return:  match_string  the value string. In example above it would be "entry1" or "entry2" etc.
 |                          true is returned for string_present, false for string_absent
 */
 char* Search_Key_Value_in_File(char *filename, char *heading)
 {
   	FILE *file_pointer;
   	char read_line[512];

   	if( (file_pointer = fopen(filename, "r")) == NULL )
    {
         printf("couldn't open file\n");
         printf("%s\n", filename);
   		  return NULL;
   	}

   	while( fgets(read_line, 512, file_pointer) != NULL )
    {
        Trim_Leading_WhiteSpace(read_line);
        if(read_line[0] == '#')   // if '#' begins a line in a file, the line is commented out and thus not active in the file
            continue;
        else if( read_line[0] == '/' && read_line[1] == '/') // if line begins with '//' it is considered commented out
            continue;

        int start_index = 0;
        int end_index = strlen(read_line) -1;
   		  if( String_Contains(read_line, heading) )
        {
             for(int i=0; i< strlen(read_line); ++i)
             {
                if( read_line[i]==':' || isspace(read_line[i]) )
                    start_index = i+1;
             }
             char* entry = Get_Substring(read_line, start_index, end_index);

             //printf("match found for heading \"%s\" entry:\t%s\n", heading, entry);
             return entry;
   		  }
   	}
    return NULL;
 }

/*
 |--------------------------------------------------------------------------
 | Extract_Value_in_String
 |--------------------------------------------------------------------------
 |
 | Search the string given as an argument, examining if it begins with 'heading' argument.
 | Returns the 'entry' which is the remaining line after 'heading'. Ignores lines beginning w/ "//" or "#".
 | If not found return NULL.
 | For example the strings:
 | // testfile.txt //         - NULL return value
 | heading1: entry1           - if heading argument is "heading1" returns entry1
 |
 | @param:   line          the string to search
 | @return:  value         the value string. In example above it would be "entry1" or "entry2" etc.
 |
 */
 char* Extract_Value_in_String(char* line)
 {
   	char read_line[512];
    bool found = false;

   	if( line == NULL )
    {
        printf("KeyValueError: line argument is NULL\n");
   		  return NULL;
   	}

    Trim_Leading_WhiteSpace(line);
    strcpy(read_line, line);
    if(read_line[0] == '#')   // if '#' begins a line in a file, the line is commented out and thus not active in the file
          return NULL;
    else if( read_line[0] == '/' && read_line[1] == '/') // if line begins with '//' it is considered commented out
          return NULL;

    int start_index = 0;
    int end_index = strlen(read_line) - 1;

    for(int i=0; i< strlen(read_line); ++i)
    {
        if( read_line[i]==':' || isspace(read_line[i]) )  // look for delimiter between key and value, which is either ':' or ' '
        {
            found = true;
            start_index = i+1;
            break;
        }
    }
    if( !found )
        return NULL;

    char* value = Get_Substring(read_line, start_index, end_index);
        return value;
 }

bool Is_Comment(char* string)
{
   	if( string == NULL )
    {
        printf("IsCommentError: line argument is NULL\n");
   		  return NULL;
   	}

    Trim_Leading_WhiteSpace(string);
    if(string[0] == '#')   // if '#' begins a line in a file, the line is commented out and thus not active in the file
        return true;
    else if( (string[0] == '/') && (string[1] == '/') ) // if line begins with '//' it is considered commented out
        return true;
    else
        return false;
}

/*
 |--------------------------------------------------------------------------
 | Extract_Key_in_String
 |--------------------------------------------------------------------------
 |
 | Search the string given as an argument, extracting the key from the line.
 | key is defined from a key value pair, shown in example below. Ignores lines beginning w/ "//" or "#".
 | If not found return NULL.
 | For example:
 | // testfile.txt //         - NULL return value
 | key123: value           - returns "key123"
 |
 | @param:   line          the string to search
 | @return:  key         the key string. In example above it would be "key123"
 |
 */
 char* Extract_Key_in_String(char* line)
 {
   	char read_line[512];

   	if( line == NULL )
    {
        printf("KeyValueError: line argument is NULL\n");
   		  return NULL;
   	}

    Trim_Leading_Trailing_Whitespace(line);
    strcpy(read_line, line);
    if(read_line[0] == '#')   // if '#' begins a line in a file, the line is commented out and thus not active in the file
    {
        printf("ERROR: #\n");
        return NULL;
    }
    else if( read_line[0] == '/' && read_line[1] == '/') // if line begins with '//' it is considered commented out
    {
        printf("ERROR: // \n");
        return NULL;
    }

    int start_index = 0;
    int end_index = strlen(read_line) - 1;

    for(int i=0; i< strlen(read_line); ++i)
    {
        if( read_line[i]==':' || isspace(read_line[i]) )  // look for delimiter between key and value, which is either ':' or ' '
        {
            end_index = i-1;
            break;
        }

    }
    char* key = Get_Substring(read_line, start_index, end_index);
    return key;
 }



 bool String_Contains(char* haystack, char* needle)
 {
    if( haystack == NULL || needle == NULL)
        return false;
    else if( strlen(needle) == 1)
    {
        char needle_char = needle[0];
        if( strchr(haystack, needle_char) == NULL)
        {
            return false;
        }
    }
    else if( strstr(haystack, needle) == NULL ) // strstr returns a substring if needle is in haystack, otherwise it returns null
    {
        return false;
    }
    return true;
 }

 bool String_Contains_Ignore_Case(char* haystack, char* needle)
 {
    if( haystack == NULL || needle == NULL)
        return false;
    else if( strlen(needle) == 1)
    {
        if( strchr(haystack, toupper( needle[0]) ) == NULL)  // strchr returns whether a character is contained within a substring
        {
            return false;
        }
    }

    char haystack_cpy[strlen(haystack) + 2];
    memset(haystack_cpy,0,sizeof(haystack_cpy));
    strcpy(haystack_cpy, haystack);
    haystack_cpy[ strlen(haystack) ] = '\0';

    char needle_cpy[strlen(needle) + 2];
    memset(needle_cpy,0,sizeof(needle_cpy));
    strcpy(needle_cpy, needle);
    needle_cpy[ strlen(needle) ] = '\0';

    // convert both strings to uppercase
    int i=0;
    while( (haystack_cpy[i] != '\0') )
    {
        haystack_cpy[i] = toupper(haystack_cpy[i]);
        ++i;
    }

    i=0;
    while( (needle_cpy[i]) != '\0' )
    {
        needle_cpy[i] = toupper(needle_cpy[i]);
        ++i;
    }

    char* substring = strstr(haystack_cpy, needle_cpy); // strstr returns ppointer to first char of ocurrence if needle is in haystack, otherwise it returns null
    if( substring == NULL )
        return false;

    return true;
 }


 bool String_Array_Contains(char** haystack, char* needle)
 {
    int i = 0;

    while(haystack[i])
    {
        char* element = haystack[i];
        if( String_Contains(element, needle) )
            return true;
        ++i;
    }
    return false;
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


char* Parse_First_Token(char* socket_string)
{
    Trim_Leading_WhiteSpace(socket_string);
    int start_index = 0;
    if( socket_string[ start_index ] == '>' || socket_string[ start_index ] == '?')             // skip first character (0 index), which should be a '>' or a '?' to indicate a command or query
        start_index += 1;

    int index_first_whitespace = Index_First_Whitespace( socket_string );   // first character of whitespace after start of token

    return Get_Substring( socket_string, start_index, index_first_whitespace);
}

char* Parse_Key(char* string)
{
    Trim_Leading_WhiteSpace(string);
    int start_index = 0;

    int index_first_colon = Index_First_Colon( string );   // first character of ':' which marks end of key

    char* key =  Get_Substring( string, start_index, index_first_colon-1);
    return key;
}


char* Parse_Value(char* string)
{
    int start_index = Get_Index_Open_Bracket( string );
    int end_index   = Get_Index_Closed_Bracket( string );

    return Get_Substring( string, start_index, end_index);
}

char* Parse_Second_Token(char* socket_string)
{
    int start_index = Index_First_Whitespace( socket_string );
    int end_index   = Index_Second_Whitespace( socket_string );

    return Get_Substring( socket_string, start_index, end_index);
}

// Must free memory after this function
char* Get_Substring(char* full_string, int start_index, int end_index)
{
   int substring_length = end_index - start_index + 1;
   char* substring = (char*)malloc(sizeof(char*) * substring_length + 1);        // allocate memory for the substring

   //Erase_String_Contents(substring);
   // Copy Substring from start_index to end index

   for( int i = 0; i< (end_index - start_index + 1); ++i)
   {
       substring[i] = full_string[i + start_index];
   }

   substring[ substring_length ] = '\0';                                // add null terminating character
   Trim_Leading_WhiteSpace( substring );
   Trim_Trailing_WhiteSpace( substring );
   return substring;
}

void Erase_String_Contents(char* string)
{
   memset(string,0,sizeof(string));                                     // zero out string memery locations
   string[0] = '\0';                                                    // add null terminator
}

void Free_String_Array_Memory(char** string_array)
{
    int i = 0;
    if(string_array == NULL)
        return;
    while(string_array[i] != NULL)
    {
        free(string_array[i]);
        ++i;
    }
    free(string_array);

    return;
}

void Print_String_Array(char** string_array)
{
  int i = 0;
  while(string_array[i] != NULL)
  {
      printf("\t%s\n", string_array[i]);
      ++i;
  }
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

void Trim_Trailing_WhiteSpace(char * str)                              // removes trailing whitespace (spaces and newlines)
{

   int stringLen = strlen(str);
   while(stringLen > 0 && isspace(str[stringLen -1]) )
   {
      stringLen--;
   }
   str[stringLen] = '\0';
}

void Trim_Leading_Trailing_Whitespace(char * str)
{
    Trim_Leading_WhiteSpace( str );
    Trim_Trailing_WhiteSpace( str );
}

// verify first char is a digit or + or -
// verify subesquent chars are digit or decimal
// if decimal is encountered, verify subsequent chars are digits
bool String_Is_Double(char* double_string)
{
    Trim_Leading_WhiteSpace( double_string );
    Trim_Trailing_WhiteSpace( double_string );
    int cur_index = 0;
    bool seen_decimal_place = false;

    if( double_string[cur_index] == '+' || double_string[cur_index] == '-' || isdigit( double_string[cur_index] ) )   // first character can be a digit, '+', or '-'
        ++cur_index;
    else if( double_string[cur_index] == '.' )    // also first digit can be a decimal place for values between 0->1
    {
        ++cur_index;
        seen_decimal_place = true;
    }
    else return false;

    char cur_char = double_string[cur_index];
    while(cur_char != '\0')                     // loop through until end of string
    {
        if( !seen_decimal_place )              // if decimal hasn't been read yet, valid characters are decimal place or digit
        {
            if( cur_char  == '.' )
            {
                ++cur_index;
                seen_decimal_place = true;
            }
            else if( isdigit( cur_char  ) )
                ++cur_index;
            else
            {
                return false;
            }
        }
        else
        {
          if( isdigit( cur_char ) )
                ++cur_index;
          else
                return false;
        }
        cur_char = double_string[cur_index];        // update current character being examined
    }
    return true;
 }

 // verify first char is a digit (not negative integer)
 // verify subesquent chars are digit
 bool String_Is_Int(char* double_string)
 {
     Trim_Leading_WhiteSpace( double_string );
     Trim_Trailing_WhiteSpace( double_string );
     int cur_index = 0;
     bool seen_decimal_place = false;

     char cur_char = double_string[cur_index];
     while(cur_char != '\0')                     // loop through until end of string
     {
        if( isdigit( cur_char ) )
            ++cur_index;
        else
            return false;

        cur_char = double_string[cur_index];        // update current character being examined
     }

     return true;
  }

int Index_of_Decimal(char* arg_string)
{
    int decimal_index = 0;
    char cur_char;

    if( strchr(arg_string, '.') == NULL )
    {
        return NOT_FOUND;
    }
    else
    {
        cur_char = arg_string[ decimal_index ];
        while( cur_char != '\0' )
        {
            if( cur_char == '.' )
                return decimal_index;

            ++decimal_index;
            cur_char = arg_string[ decimal_index ];
        }
    }
    return NOT_FOUND;
}

// to be a "filename" this function assumes the string must have a "." and extension
// filename must be [string].[extension]
// extension must be min 3 characters
bool String_Is_Filename(char* filename)
{
    Trim_Leading_WhiteSpace( filename );
    Trim_Trailing_WhiteSpace( filename );

     // get index of period
     // verify 1 or more characters before decimal
     // verify min 3 characters after decimal

    int decimal_index = Index_of_Decimal( filename );
    if( decimal_index == NOT_FOUND)
        return false;

    // verify at least 1 character before decimal:
    if( !(decimal_index >= 1) )
        return false;

    // verify file extension (after decimal) is at least 3 characters
    char* extension = Get_File_Extension(filename);
    //printf("Extension: %s\n", extension);
    int length = strlen(extension);
    free(extension);

    if( !(length >= 3) )
        return false;

    return true;
}

char* Get_File_Extension(char* filename)
{
    int decimal_index = Index_of_Decimal(filename);
    if( decimal_index == NOT_FOUND)
        return NULL;

    char temp[ strlen(filename) ];
    Erase_String_Contents( temp );
    int temp_index = 0;

    int cur_index = decimal_index;
    ++cur_index;
    char cur_char = filename[ cur_index ];

    while( cur_char != '\0' && !isspace(cur_char) )
    {
        temp[ temp_index ] = cur_char;
        ++cur_index;
        ++temp_index;
        cur_char = filename[ cur_index];
    }

    char* rtn_string = malloc( sizeof(char*) * strlen(temp) + 1 );
    strcpy(rtn_string, temp);

    return rtn_string;
}




// looking for first index of "["
int Get_Index_Open_Bracket(char* str)
{
    int index = 0;
    while( str[ index ] != '\0' )
    {
        if( str[ index ] == '[' )
            return index;
        ++index;
    }
    return NONE;
}

// looking for first index of "]"
int Get_Index_Closed_Bracket(char* str)
{
    int index = 0;
    while( str[ index ] != '\0' )
    {
        if( str[ index ] == ']' )
            return index;
        ++index;
    }
    return NONE;
}

//      03-19-2020_11.45.00
bool String_Is_TimeDate(Instruction_Info* socket_instruction)
{
    // verify first token before '-' can be parse to integer between 1-12 max 2 chars
    // verify second token (day) can be parsed to integer between 1-31 max 2 chars
    // verify 4 digit year
    // verify '_'
    // verify hour can be parsed to integer 00-23, max 2 chars
    // verify min can be parsed to integer 00-59, max 2 chars
    // verify second can be parsed to integer 00-59, max 2 chars
    char *str_month, *str_day, *str_year, *str_hour, *str_minute, *str_second;
    int month, day, year, hour, minute, second;
    int look_ahead_index = 0;
    int substr_start_index=0, substr_end_index=0, substring_length = 0;

    char* time_string = socket_instruction->argument_str;
// PARSE "DATE" PART OF TIMEDATE STRING
//
    // PARSE MONTH PART OF THE STRING
    while( time_string[look_ahead_index] != '-' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index first '-', should be max 2 chars before '-'
    substr_end_index = look_ahead_index -1;
    substring_length = substr_end_index - substr_start_index + 1;
    if( substring_length > 2 || substring_length < 1)             // max 2 characters for "str_month", but at least one character
        return false;
    else
    {
        str_month = Get_Substring(time_string, substr_start_index, substr_end_index);
        if( !Contains_Only_Digits(str_month) )
            return false;
        month = Parse_Int( str_month );     // parse month string to an integer
        if( month < 1 || month > 12)
        {
            printf("Error: month \"%d\" is not in valid month range (1-12)\n", month);
            return false;
        }

        if(DEBUG_TIMEDATE) printf("Month: %d\n", month);
        free(str_month);
    }
    // PARSE "DAY OF MONTH" PART OF STRING
    ++look_ahead_index;                           // increment, so now look_ahead_index should be in "DAY" part of the timedate string
    substr_start_index = look_ahead_index;        // start of substring containing one or two digit month day
    while( time_string[look_ahead_index] != '-' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of second '-', should be max 2 chars before '-'

    substr_end_index = look_ahead_index-1;          // end of substring containing one or two digit day of month
    substring_length = substr_end_index - substr_start_index + 1;
    if( substring_length > 2 || substring_length < 1)             // max 2 characters for "day", but at least one character
        return false;
    else
    {
        str_day = Get_Substring(time_string, substr_start_index, substr_end_index);
        if( !Contains_Only_Digits(str_day) )
            return false;
        day = Parse_Int( str_day );     // parse month string to an integer
        if( day < 1 || day > 31)
        {
            printf("Error: day \"%d\" is not in valid day range (1-12)\n", day);
            return false;
        }
        if(DEBUG_TIMEDATE) printf("Day: \"%d\"\n", day);
        free(str_day);
    }
    // PARSE YEAR PART OF THE STRING
    ++look_ahead_index;                           // increment, so now look_ahead_index should be in "YEAR" part of the timedate string
    substr_start_index = look_ahead_index;        // start of substring containing four or two digit YEAR
    while( time_string[look_ahead_index] != '_' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index '_' marking end of year

    substr_end_index = look_ahead_index-1;          // end of substring containing four or two digit year
    substring_length = substr_end_index - substr_start_index + 1;
    if( substring_length != 4 && substring_length != 2)             // max 4 characters for "year", but at least two characters
    {
        printf("Error: year in time string \"%s\" is not either 4 or 2 digits\n", time_string);
        return false;
    }
    else
    {
        str_year = Get_Substring(time_string, substr_start_index, substr_end_index);
        year = Parse_Int( str_year );     // parse month string to an integer
        if( !Contains_Only_Digits(str_year) )
        {
            free(str_year);
            return false;
        }

        if( year < 2000 && substring_length == 4)
        {
            printf("Error: 4 digit year \"%d\" is not in range (more recent than 2000)\n", year);
            free(str_year);
            return false;
        }
        else if( year < 2000 && substring_length == 2)
            year += 2000;
        if(DEBUG_TIMEDATE) printf("Year: \"%d\"\n", year);
        free(str_year);
    }
// PARSE "TIME" PART OF TIMEDATE STRING
//
    // PARSE THE HOUR
    ++look_ahead_index;                           // increment, so now look_ahead_index should be in "HOUR" part of the timedate string
    substr_start_index = look_ahead_index;        // start of substring containing one or two digit hour
    while( time_string[look_ahead_index] != '.' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of first '.', should be max 2 chars before '.'

    substr_end_index = look_ahead_index-1;          // end of substring containing one or two digit hour
    substring_length = substr_end_index - substr_start_index + 1;
    if( substring_length > 2 || substring_length < 1)             // max 2 characters for "hour", but at least one character
    {
        printf("Error: hour in time string \"%s\" has less than one or more than 2 digits\n", time_string);
        return false;
    }
    else
    {
        str_hour = Get_Substring(time_string, substr_start_index, substr_end_index);
        if( !Contains_Only_Digits(str_hour) )
        {
            free(str_hour);
            return false;
        }
        hour = Parse_Int( str_hour );     // parse month string to an integer
        if( hour < 0 || hour > 23)
        {
            printf("Error: hour \"%d\" is not in valid range (0-23)\n", hour);
            free(str_hour);
            return false;
        }
        if(DEBUG_TIMEDATE) printf("Hour: \"%d\"\n", hour);
        free(str_hour);
    }
    // PARSE THE MINUTE
    ++look_ahead_index;                           // increment, so now look_ahead_index should be in "MINUTE" part of the timedate string
    substr_start_index = look_ahead_index;        // start of substring containing one or two digit minute
    while( time_string[look_ahead_index] != '.' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of first '.', should be max 2 chars before '.'

    substr_end_index = look_ahead_index-1;          // end of substring containing one or two digit minute
    substring_length = substr_end_index - substr_start_index + 1;
    if( substring_length > 2 || substring_length < 1)             // max 2 characters for "minute", but at least one character
    {
        printf("Error: minute in time string \"%s\" has less than one or more than 2 digits\n", time_string);
        return false;
    }
    else
    {
        str_minute = Get_Substring(time_string, substr_start_index, substr_end_index);
        if( !Contains_Only_Digits(str_minute) )
        {
            free(str_minute);
            return false;
        }
        minute = Parse_Int( str_minute );     // parse month string to an integer
        if( minute < 0 || minute > 59)
        {
            printf("Error: minute \"%d\" is not in valid range (0-59)\n", minute);
            free(str_minute);
            return false;
        }
        if(DEBUG_TIMEDATE) printf("Minute: \"%d\"\n", minute);
        free(str_minute);
    }
    // PARSE THE SECOND
    ++look_ahead_index;                           // increment, so now look_ahead_index should be in "SECOND" part of the timedate string
    substr_start_index = look_ahead_index;        // start of substring containing one or two digit SECOND
    while( time_string[look_ahead_index] != '.' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of first '.', should be max 2 chars before '.'

    substr_end_index = look_ahead_index-1;          // end of substring containing one or two digit SECOND
    substring_length = substr_end_index - substr_start_index + 1;
    if( substring_length > 2 || substring_length < 1)             // max 2 characters for "SECOND", but at least one character
    {
        printf("Error: second \"%s\" has less than one or more than 2 digits)\n", str_second);
        return false;
    }
    else
    {
        str_second = Get_Substring(time_string, substr_start_index, substr_end_index);
        if( !Contains_Only_Digits(str_second) )
        {
            free(str_second);
            return false;
        }
        second = Parse_Int( str_second );     // parse month string to an integer
        if( second < 0 || second > 59)
        {
            printf("Error: second \"%d\" is not in valid range (0-59)\n", second);
            free(str_second);
            return false;
        }
        if(DEBUG_TIMEDATE) printf("Second: \"%d\"\n", second);
        free(str_second);
    }
    return true;
}

bool Contains_Only_Digits(char* digit_string)
{
    int index = 0;
    while( digit_string[index] != '\0')
    {
        if( !isdigit( digit_string[index] ) )
        {
            printf("Error: digit string \"%s\" contains non digit at character \'%c\'\n", digit_string, digit_string[index]);
            return false;
        }
        ++index;
    }
    return true;
}

int Parse_Int(char* integer_string)
{
   char* end_ptr;
   int parsed_int = strtol(integer_string, &end_ptr, 10);   // parse the substring to integer using stringtolong function
   return parsed_int;
 }


double Parse_Double(char* double_string)
{
    bool is_negative = false;
    Trim_Trailing_WhiteSpace(double_string);

    // Get index of start of integer portion. Could be a digit or + or -
    int start_index = 0;
    for(int i = 0; i<strlen(double_string); ++i )
    {
        if(double_string[i] == '+' || double_string[i] == '-')
        {
            if( isdigit(double_string[i+1]) && double_string[i] == '-' )
            {
                start_index = i+1;
                is_negative = true;
                break;
            }
        }
        if( isdigit(double_string[i]) )
        {
            start_index = i;
            break;
        }
    }

    // get index of last digit
    int end_index = start_index;                              // start search of last "digit" character at the beginning of the integer portion
    for(int i=start_index; i<strlen(double_string); ++i )
    {
        if( isdigit( double_string[i] ) )
        {
            end_index = i;
            continue;
        }
        else
        {
            if( double_string[i] == '.' && isdigit( double_string[ i +1 ] ) )
            {
                end_index = i+1;
                continue;
            }
            else
                break;
        }
     }

     char* integer_substring = Get_Substring(double_string, start_index, end_index);
     integer_substring[ strlen(integer_substring) ] = '\0';    // add null terminating character

     char* end_ptr;
     double parsed_double = strtod(integer_substring, &end_ptr);   // parse the substring to integer using stringtolong function
     if( is_negative )
        parsed_double *= -1;
    free(integer_substring);

     return parsed_double;
 }

void Seconds_To_Elapsed_Time_String(long long total_seconds, char* string_buffer)
{
		int display_seconds = total_seconds % 60;
		int total_minutes   = total_seconds / 60;
		int display_minutes = total_minutes % 60;
		int display_hours 		= total_minutes / 60;

		sprintf(string_buffer, "%dhr %dmin %dsec", display_hours, display_minutes, display_seconds);
}

void Syntax_Error(char* target_str, char* parse_string, char* error_message)
{
    char response[MAX_RESPONSE_LENGTH];
    sprintf(response, "\t%s SyntaxError: received \"%s\", %s", X_ERROR, parse_string, error_message);
    strcat( target_str, response);          // copy error message into parse_instruction data structure
}




#endif
