#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

int main() {
    // Get system information
    struct utsname system_info;
    uname(&system_info);

    // Get host name
    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    // Get total RAM installed
    struct sysinfo meminfo;
    sysinfo(&meminfo);
    long total_ram = meminfo.totalram / (1024 * 1024); // Convert to MB

    // Custom ASCII art for the OS logo
    printf("      ._____.\n");
    printf("    .'       `.\n");
    printf("   /           \\\n");
    printf("  |             |\n");
    printf("  |             |\n");
    printf("   \\           /\n");
    printf("    `._______.'\n");

    // Print system information
    printf("\n");
    printf("System Information:\n");
    printf("  Hostname: %s\n", hostname);
    printf("  OS: %s %s %s\n", system_info.sysname, system_info.release, system_info.machine);
    printf("  Total RAM: %ld MB\n", total_ram);

    return 0;
}
