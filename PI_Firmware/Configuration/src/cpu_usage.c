/*
        cpumeter1.c
        Ragnar Jensen 2013

        Based on cpumeter.c by
        Michael Rodenhurst, 30/09/12

        gcc --std=gnu99 -o cpumeter1 cpumeter1.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define VERSION "1.0"

void update();
int get_cpu_usage();

int main()
{
int i;
    for(i = 0; i <= 1; i++) // Loop twice.
    {
        update(i);
        if (i == 0) sleep(1);
    }

    return 0;
}


void update(int second_sample)
{

    int cpu_usage = get_cpu_usage();

    if ( second_sample ) { // Skip the first sample, which is CPU% since boot.
        printf("%i%%\n", cpu_usage);
        fflush(stdout);
    }
}

int previous_tjif = 0;
int previous_ijif = 0;

// Return value 0-100
int get_cpu_usage()
{
    int i;
    char *buf = malloc(70);

    // Read the cpu status from /proc/stat
    FILE *fp = fopen("/proc/stat", "r");
    fread(buf, sizeof(char), 62, fp);
    fclose(fp);

    // Strip the prefixed "cpu  "
    char *cpuline = malloc(70);
    for(i=5; i<strlen(buf); i++)
        cpuline[i-5] = buf[i];

    // Parse the proc/stat information into separate jiffie containers
    int user_jif, nice_jif, system_jif, idle_jif;
    int iowait_jif;
    int irq_jif;
    int softirq_jif;

    char *tokbuf = strtok(cpuline, " ");
    user_jif = atoi(tokbuf);
    tokbuf = strtok(NULL, " ");
    nice_jif = atoi(tokbuf);
    tokbuf = strtok(NULL, " ");
    system_jif = atoi(tokbuf);
    tokbuf = strtok(NULL, " ");
    idle_jif = atoi(tokbuf);
    tokbuf = strtok(NULL, " ");
    iowait_jif = atoi(tokbuf);

// Ragnar: added irq jiffies.
    tokbuf = strtok(NULL, " ");
    irq_jif = atoi(tokbuf);
    tokbuf = strtok(NULL, " ");
    softirq_jif = atoi(tokbuf);
    // Get the workload from that
// printf("%i %i %i %i %i %i %i\n", user_jif , nice_jif , system_jif , idle_jif , iowait_jif , irq_jif , softirq_jif);
    int tjif = user_jif + nice_jif + system_jif + idle_jif + iowait_jif + irq_jif + softirq_jif;

    int delta_total = tjif - previous_tjif;
    int delta_idle = idle_jif - previous_ijif;
    int delta_usage = (1000*(delta_total-delta_idle)/(delta_total+5))/10;
    previous_tjif = tjif;
    previous_ijif = idle_jif;

    free(cpuline);
    free(buf);

    return delta_usage;
}
