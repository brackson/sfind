#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>


// extern char *base_path;
extern char *search_string;
extern char *file_type;
extern int errno;

int searchDirectory(char *path, int depth) {
    DIR *dir_stream;
    struct dirent *dp;
    struct stat file_status;

    // if we can't open the directory, skip
    if ((dir_stream = opendir(path)) == NULL) {
        return 0;
    }

    // if directory is empty, skip
    if (!(dp = readdir(dir_stream))) {
        // fprintf( stderr, "Specified path is empty, skipping...\n");
        return 0;
    }

    while ((dp = readdir(dir_stream)) != NULL) {

        char new_path[1024];

        // ignore "." and ".."
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }

        // update base_path
        sprintf(new_path, "%s/%s", path, dp->d_name);

        // assign lstat, continue if there's a permission error
        // if (lstat(new_path, &file_status) != 0) {
        //     continue;
        // }

        if (lstat(new_path, &file_status) != 0) {
            if (errno == ENOENT) {
                fprintf( stderr, "Specified path doesn't exist. Exiting...\n");
    			exit(1);
            } else if (errno == EACCES) {
                fprintf( stderr, "sfind: '%s': Permission denied\n", new_path);
    			exit(1);
            } else {
                fprintf( stderr, "sfind: '%s': Unspecified error\n", new_path);
                continue;
            }
        }

        if (S_ISDIR(file_status.st_mode)) {
            // check if file_type is specified, then check if file_type matches
            if (file_type != NULL) {
                int result = 0; // set to 1 if we get a match

                switch (file_status.st_mode & S_IFMT) {
                    case S_IFREG:
                        if (strcmp(file_type, "f") == 0) { result = 1; }
                        break;
                    case S_IFDIR:
                        if (strcmp(file_type, "d") == 0) { result = 1; }
                        break;
                    case S_IFCHR:
                        if (strcmp(file_type, "c") == 0) { result = 1; }
                        break;
                    case S_IFBLK:
                        if (strcmp(file_type, "b") == 0) { result = 1; }
                        break;
                    case S_IFLNK:
                        if (strcmp(file_type, "l") == 0) { result = 1; }
                        break;
                    case S_IFIFO:
                        if (strcmp(file_type, "p") == 0) { result = 1; }
                        break;
                    case S_IFSOCK:
                        if (strcmp(file_type, "s") == 0) { result = 1; }
                        break;
                }

                if (result == 1) {
                    // check if search_string was provided; try to match if so
                    if (search_string != NULL) {
                        if (strstr(dp->d_name, search_string) != NULL) {
                            printf("%s\n", new_path);
                            searchDirectory(new_path, depth + 1);
                        }
                    } else {
                        printf("%s\n", new_path);
                        searchDirectory(new_path, depth + 1);
                    }
                } else {
                    searchDirectory(new_path, depth + 1);
                }

            } else {
                // check if directory name includes search term
                if (strstr(dp->d_name, search_string) != NULL) {
                    printf("%s\n", new_path);
                    searchDirectory(new_path, depth + 1);
                }
            }

        } else {
            // check if file_type is specified, then check if file_type matches
            if (file_type != NULL) {
                int result = 0; // set to 1 if we get a match

                switch (file_status.st_mode & S_IFMT) {
                    case S_IFREG:
                        if (strcmp(file_type, "f") == 0) { result = 1; }
                        break;
                    case S_IFDIR:
                        if (strcmp(file_type, "d") == 0) { result = 1; }
                        break;
                    case S_IFCHR:
                        if (strcmp(file_type, "c") == 0) { result = 1; }
                        break;
                    case S_IFBLK:
                        if (strcmp(file_type, "b") == 0) { result = 1; }
                        break;
                    case S_IFLNK:
                        if (strcmp(file_type, "l") == 0) { result = 1; }
                        break;
                    case S_IFIFO:
                        if (strcmp(file_type, "p") == 0) { result = 1; }
                        break;
                    case S_IFSOCK:
                        if (strcmp(file_type, "s") == 0) { result = 1; }
                        break;
                }

                if (result == 1) {
                    // check if search_string was provided; try to match if so
                    if (search_string != NULL) {
                        if (strstr(dp->d_name, search_string) != NULL) {
                            printf("%s\n", new_path);
                        }
                    } else {
                        printf("%s\n", new_path);
                    }
                }

            } else {
                // check if search_string was provided; try to match if so
                if (search_string != NULL) {
                    if (strstr(dp->d_name, search_string) != NULL) {
                        printf("%s\n", new_path);
                    }
                } else {
                    printf("%s\n", new_path);
                }
            }
        }
    }

    closedir(dir_stream);

    return 0;
}
