#include <stdio.h>

	int main(int argc, char * argv[]) {
		if (argc > 0){
			int i = 0;
			for (;i < argc; ++i) {
				if (argv[i] == "--help") {
					printf("====ARGUMENTS====\n --help for help\n --version to get the current version");
				} else if (argv[i] == "--version") {
					printf("The current version is 00\n");
				} else {
					printf("Argument not found\n");
				}
			}
		}
		printf("Ninja virtual machine started\n");
		printf("Ninja virtual machine stopped\n");
		return 0;
	}