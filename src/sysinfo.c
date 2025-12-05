#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysinfo.h>

void get_ip() {
    printf("Adresse  IP locale   :\n");
    system("hostname -I | awk '{print $1}'");
}

void get_cpu_usage() {
    FILE* fp;
    char buffer[1024];
    unsigned long long int user1, nice1, system1, idle1;
    unsigned long long int user2, nice2, system2, idle2;

    fp = fopen("/proc/stat", "r");
    fgets(buffer, sizeof(buffer) - 1, fp);
    sscanf(buffer, "cpu %llu %llu %llu %llu", &user1, &nice1, &system1, &idle1);
    fclose(fp);

    sleep(1); // Attendre 1 seconde

    fp = fopen("/proc/stat", "r");
    fgets(buffer, sizeof(buffer) - 1, fp);
    sscanf(buffer, "cpu %llu %llu %llu %llu", &user2, &nice2, &system2, &idle2);
    fclose(fp);

    unsigned long long int total1 = user1 + nice1 + system1 + idle1;
    unsigned long long int total2 = user2 + nice2 + system2 + idle2;
    unsigned long long int total_diff = total2 - total1;
    unsigned long long int idle_diff = idle2 - idle1;

    double cpu_usage = 100.0 * (total_diff - idle_diff) / total_diff;
    printf("Utilisation CPU : %.2f%%\n", cpu_usage);
}

void get_ram_usage() {
    struct sysinfo info;
    sysinfo(&info);

    long total_ram = info.totalram / 1024 / 1024;
    long free_ram = info.freeram / 1024 / 1024;
    long used_ram = total_ram - free_ram;

    printf("RAM utilisée : %ld Mo / %ld Mo\n", used_ram, total_ram);
}

int main() {
    printf("Informations système :\n\n");

    get_ip();
    get_cpu_usage();
    get_ram_usage();

    return 0;
}
