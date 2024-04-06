// a simple package manager that clones from git or gets it from a server you provide!
// remember! this software it's still on development so you might find a lot of bugs or glitches while you use it!
// if this software results useful for you, i would be glad to hear your thoughts on this program!
// created by LillyDev, following the GPL License!
// the J Package Manager!

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//end of libraries importing

// Function to check for $temp/build and $temp/jpm folders
void checkDir() {
    const char *tempPath = "/tmp";
    const char *jpmBuildDir = "/tmp/jpm/build";
    const char *jpmDir = "/tmp/jpm";

    // Check if /tmp/jpm/build directory exists
    if (system("test -d /tmp/jpm/build") != 0) {
        // Create the directory if it doesn't exist
        printf("Creating directory: %s\n", jpmBuildDir);
        if (system("sudo mkdir -p /tmp/jpm/build") != 0) {
            printf("Failed to create directory: %s\n", jpmBuildDir);
            return;
        }
    }

    // Check if /tmp/jpm directory exists
    if (system("test -d /tmp/jpm") != 0) {
        // Create the directory if it doesn't exist
        printf("Creating directory: %s\n", jpmDir);
        if (system("sudo mkdir -p /tmp/jpm") != 0) {
            printf("Failed to create directory: %s\n", jpmDir);
            return;
        }
    }
}

// Function to download the repo source code from GitHub
void download(const char *url) {
    printf("Downloading from: %s\n", url);

    // Checks and creates directories if necessary
    checkDir();

    // Determine the directory name for the repository
    char repoName[256];
    char *token, *saveptr;
    strcpy(repoName, url);
    token = strtok_r(repoName, "/", &saveptr);
    while ((token = strtok_r(NULL, "/", &saveptr)) != NULL) {
        strcpy(repoName, token);
    }
    repoName[strlen(repoName) - 4] = '\0'; // Remove ".git" from the end

    // Clone the repository into a subdirectory of /tmp/jpm
    char cmd[512]; // Increased buffer size
    snprintf(cmd, sizeof(cmd), "git clone %s /tmp/jpm/%s", url, repoName); // Using snprintf
    int result = system(cmd);

    // Check if the download was successful
    if (result != 0) {
        printf("Error: Download failed.\n Maybe the server returned a non-valid reply or there's an internal JPM error.\n");
        return;
    }

    // Build the software if "--build" option is present
    char buildCmd[512];
    if (strstr(url, ".git") != NULL && strstr(url, "--build") != NULL) {
        // Extract build arguments
        const char *buildArgs = strstr(url, "--build") + 7; // Length of "--build"
        snprintf(buildCmd, sizeof(buildCmd), "cd /tmp/jpm/%s && %s", repoName, buildArgs);
        printf("Building from: /tmp/jpm/%s\n", repoName);
        system(buildCmd);
    }
}

// Function to build the software
// still development
void build(const char *commands) {
    //checks if build arguments were given
	if (strcmp(commands, "[]") == 0) {
	  printf("Sorry, no arguments were given, retiring...\n");
	  return;
	}

	printf("Building software...\n");
	//executes the given build arguments.
	// but before, it checks and creates directories if necessary
    	checkDir();
	system(commands);
}

// Function to install the software
// still on development
void install(const char *binary) {
    printf("Installing...\n");
    // Checks and creates directories if necessary
    checkDir();
    // Move binary to installation directory
    char cmd[100];
    sprintf(cmd, "mv /tmp/jpm/build/%s /usr/bin/jpm/installed/%s", binary, binary);
    system(cmd);
}

int main(int argc, char *argv[]) {
    // Check if user has provided arguments
    if (argc < 2) {
        printf("Usage: JPM [--download <url> | --build <commands> | --install <binary>]\n");
        return 1;
    }

    // Determine the action requested by the user
    if (strcmp(argv[1], "--download") == 0 && argc >= 3) {
        download(argv[2]);
    } else if (strcmp(argv[1], "--build") == 0 && argc >= 3) {
        build(argv[2]);
    } else if (strcmp(argv[1], "--install") == 0 && argc >= 3) {
        install(argv[2]);
    } else {
        printf("Invalid command\n");
        return 1;
    }
//more prefixes will be added soon!
    return 0;
}
