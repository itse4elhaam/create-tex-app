#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Welcome to TypeScript Express generator. You need to have Node.js installed to run this utility.\n");

    char packageManager[10];

    // Get package manager choice
    printf("Which package manager do you want to use? (npm/yarn/pnpm): ");
    fgets(packageManager, sizeof(packageManager), stdin);
    packageManager[strcspn(packageManager, "\n")] = '\0';  // Remove the newline character

    // Check if it is installed and install if necessary
    if (strcmp(packageManager, "npm") == 0 || strcmp(packageManager, "yarn") == 0 || strcmp(packageManager, "pnpm") == 0) {
        printf("You selected: %s\n", packageManager);

        // Check if the package manager is installed
        char checkCommand[50];
        sprintf(checkCommand, "%s --version", packageManager);

        if (system(checkCommand) == 0) {
            printf("%s is installed.\n", packageManager);
        } else {
            printf("%s is not installed. Installing...\n", packageManager);

            // Install the package manager
            char installCommand[50];
            sprintf(installCommand, "npm install -g %s", packageManager);

            if (system(installCommand) == 0) {
                printf("%s installed successfully.\n", packageManager);
            } else {
                printf("Error installing %s. Please install it manually.\n", packageManager);
            }
        }
    } else {
        printf("Invalid package manager choice. Please choose npm, yarn, or pnpm.\n");
    }

    return 0;
}

