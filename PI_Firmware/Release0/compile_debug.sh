
gcc -g -fsanitize=address -static-libasan -fno-omit-frame-pointer -o exec Execution_Engine.c -l pthread -l bcm2835 -l m

