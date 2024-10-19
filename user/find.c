#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// Function to concatenate the source path to the destination path
void concatenate_path(char *destination, const char *source) {
    while (*destination) destination++; // Move to the end of the current path
    while ((*destination++ = *source++) != '\0'); // Copy the new part of the path
}

// Function to search the directory for a specific file
void search_directory(const char *directory, const char *filename) {
    char full_path[512]; // Variable to store the complete path
    int file_descriptor; // File descriptor
    struct dirent dir_entry; // Directory entry structure
    struct stat file_status; // File status information

    // Open the directory
    if ((file_descriptor = open(directory, 0)) < 0) {
        fprintf(2, "Error: Cannot open directory %s\n", directory);
        return;
    }

    // Get the file status information
    if (fstat(file_descriptor, &file_status) < 0) {
        fprintf(2, "Error: Cannot get status for %s\n", directory);
        close(file_descriptor);
        return;
    }

    // If it's a directory, read its contents
    if (file_status.type == T_DIR) {
        while (read(file_descriptor, &dir_entry, sizeof(dir_entry)) == sizeof(dir_entry)) {
            if (dir_entry.inum == 0 || strcmp(dir_entry.name, ".") == 0 || strcmp(dir_entry.name, "..") == 0)
                continue; // Skip special entries like "." and ".."

            // Build the new path
            full_path[0] = '\0';
            concatenate_path(full_path, directory);
            concatenate_path(full_path, "/");
            concatenate_path(full_path, dir_entry.name);

            // Check if this is the file we're looking for
            if (strcmp(dir_entry.name, filename) == 0) {
                printf("%s\n", full_path);
            }

            // Recursively search in subdirectories
            search_directory(full_path, filename);
        }
    }

    close(file_descriptor); // Close the file descriptor
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(2, "Usage: find <directory> <filename>\n");
        exit(1);
    }

    search_directory(argv[1], argv[2]); // Call the search function
    exit(0);
}
