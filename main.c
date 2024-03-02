#include <c++/11/bits/ranges_util.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Opts {
    bool srcDir;
    bool pathAlias;
    bool apiRoutesLogging;
    bool opinionatedStruct;
};

const struct Opts DEFAULT_OPTIONS = {
    .srcDir = true,
    .pathAlias = true,
    .opinionatedStruct = true,
    .apiRoutesLogging = true};

const char *FOLDERS_TO_CREATE[] = {"config", "controllers", "helpers", "models", "lib", "routes"};

bool isPackageManagerValid(char pm[10]) {
    const bool isValid = strcmp(pm, "npm") == 0 || strcmp(pm, "yarn") == 0 || strcmp(pm, "pnpm") == 0;
    return isValid;
}

void installIfPackageManagerNotInstalled(char pm[10]) {
    char checkCommand[50];
    sprintf(checkCommand, "%s --version", pm);

    if (system(checkCommand) == 1) {
        printf("%s is not installed. Installing...\n", pm);
        char installCommand[50];
        sprintf(installCommand, "npm install -g %s", pm);

        if (system(installCommand) == 1) {
            printf("Error installing %s. Please install it manually.\n", pm);
            exit(0);
        }

        printf("%s installed successfully.\n", pm);
        return;
    }
    printf("%s is installed.\n", pm);
}

struct Opts askForOpts() {
    struct Opts opts;

    printf("Do you want to include the 'src' directory? (y/n, default: y): ");
    char srcDirChoice;
    scanf(" %c", &srcDirChoice);
    opts.srcDir = (srcDirChoice == 'y' || srcDirChoice == 'Y');

    printf("Do you want to include a path alias? (y/n, default: y): ");
    char pathAliasChoice;
    scanf(" %c", &pathAliasChoice);
    opts.pathAlias = (pathAliasChoice == 'y' || pathAliasChoice == 'Y');

    printf("Do you want API routes logging? (y/n, default: y): ");
    char apiRoutesLoggingChoice;
    scanf(" %c", &apiRoutesLoggingChoice);
    opts.apiRoutesLogging = (apiRoutesLoggingChoice == 'y' || apiRoutesLoggingChoice == 'Y');

    printf("Do you want an opinionated folder structure? (y/n, default: y): ");
    char opinionatedStructChoice;
    scanf(" %c", &opinionatedStructChoice);
    opts.opinionatedStruct = (opinionatedStructChoice == 'y' || opinionatedStructChoice == 'Y');

    return opts;
}

void createFolders(char **namesArray, size_t folderCount) {
    if (chdir("src") == -1) {
        perror("Unable to change directory to src");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < folderCount; i++) {
        if (mkdir(namesArray[i], 0777) == -1) {
            perror("Unable to create folders");
            exit(EXIT_FAILURE);
        }
    }
}

void completeInstallation(const struct Opts options) {
    if (options.srcDir && mkdir("src") == 1) {
        printf("Unable to create folders, quitting");
        exit(0);
    }
    if (options.opinionatedStruct) {
        size_t folderSize = sizeof(FOLDERS_TO_CREATE) / sizeof(FOLDERS_TO_CREATE[0]);
        createFolders(FOLDERS_TO_CREATE, folderSize);
    }
}

void controller() {
    printf("Welcome to TypeScript Express generator. You need to have Node.js installed to run this utility.\n");

    char packageManager[10];

    printf("Which package manager do you want to use? (npm/yarn/pnpm): ");
    fgets(packageManager, sizeof(packageManager), stdin);
    packageManager[strcspn(packageManager, "\n")] = '\0';

    if (!isPackageManagerValid(packageManager)) {
        printf("Invalid package manager choice. Please choose npm/yarn/pnpm.\n");
        exit(0);
    }

    installIfPackageManagerNotInstalled(packageManager);

    printf("You selected: %s\n", packageManager);

    struct Opts opts = askForOpts();

    completeInstallation(opts);
}

main() {
    controller();
    return 0;
}
