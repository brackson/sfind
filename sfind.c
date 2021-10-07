#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "searchDirectory.h"

char *search_string;
char *file_type;

int main(int argc, char **argv) {
	char *base_path;

	int index;
	int c;

	opterr = 0;

	while ((c = getopt(argc, argv, "s:n:t:")) != EOF) {
		switch (c) {
			case 's':
				base_path = optarg;
				break;
			case 'n':
				search_string = optarg;
				break;
			case 't':
				file_type = optarg;
				break;
			case '?':
				if (optopt == 's' || optopt == 'n' || optopt == 't')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint(optopt))
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
				return 1;
			default:
				abort();
		}
    }

    for (index = optind; index < argc; index++) {
        printf("Non-option argument %s\n", argv[index]);
        exit(1);
    }

	if (base_path == NULL) {
		char temp_base_path[1024] = ".";
		base_path = temp_base_path;
	} else {
		// remove any trailing slash
		if (base_path[strlen(base_path) - 1] == '/') {
			base_path[strlen(base_path) - 1] = '\0';
		}
	}

	if (search_string == NULL) {
		if (file_type == NULL) {
			fprintf( stderr, "ERROR: Use without a search string only allowed when searching for a file type (-t flag). Exiting...\n");
			exit(1);
		}
	}

	if (file_type != NULL) {
		if (strlen(file_type) != 1) {
			fprintf( stderr, "ERROR: Only one file_type (-t flag) allowed. Exiting...\n");
			exit(1);
		}

		if (strstr("fdcblps", file_type) == NULL) {
			fprintf( stderr, "ERROR: Not a valid file_type (-t flag). Exiting...\n");
			exit(1);
		}
	}

	searchDirectory(base_path, 0);

	return 0;
}
