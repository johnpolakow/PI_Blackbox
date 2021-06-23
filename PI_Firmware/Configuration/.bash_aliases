
alias ls='ls --group-directories-first --color=auto'       # list
alias la='ls -la --group-directories-first --color=auto'   # list all
alias dmesg='dmesg -T'                                     # print dmesg in human readable timestamps
alias update='sudo apt-get update'                         # update apt repository
alias upgrade='sudo apt-get upgrade'                       # upgrade packages
alias ps='ps auxf'                                         # list running processes in tree format
alias df="df -Tha --total"                                 # list disk usage
alias temp='printf "CPU_TEMP: \e[1;31m%s°C\e[0m\n" "$(/opt/vc/bin/vcgencmd measure_temp | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')"'
