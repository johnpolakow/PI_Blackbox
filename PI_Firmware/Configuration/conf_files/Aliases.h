#define BASH_ALIAS_FILE               "/home/pi/.bash_aliases"
#define BASHRC_FILE                   "/home/pi/.bashrc"

#define ALIAS_LS              "alias ls='ls --group-directories-first --color=auto'       # list"
#define ALIAS_LA              "alias la='ls -la --group-directories-first --color=auto'   # list all"
#define ALIAS_DMESG           "alias dmesg='dmesg -T'                                     # print dmesg in human readable timestamps"
#define ALIAS_UPDATE          "alias update='sudo apt-get update'                         # update apt repository"
#define ALIAS_UPGRADE         "alias upgrade='sudo apt-get upgrade'                       # upgrade packages"
#define ALIAS_PS              "alias ps='ps auxf'                                         # list running processes in tree format"
#define ALIAS_DF              "alias df=\"df -Tha --total\"                               # list disk usage"


// Append these lines to .bashrc file
#define BASHRC_LINE_SEP       "#---------------------------------------"
#define BASHRC_APPEND1        "# Following function lists dir contents whenever changing directories with 'cd' command"
#define BASHRC_APPEND2        "function cd "
#define BASHRC_APPEND3        "{"
#define BASHRC_APPEND4        "     builtin cd \"$@\" && ls"
#define BASHRC_APPEND5        "}"
#define BASHRC_APPEND6        "source /home/pi/.bash_aliases"
