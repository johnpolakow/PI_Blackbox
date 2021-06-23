#!/bin/bash
gcc -g -fsanitize=address -static-libasan -o exec Execution_Engine.c -l pthread -l bcm2835 -l m

#sudo systemctl daemon-reload
#sudo systemctl start Blackberry.service
