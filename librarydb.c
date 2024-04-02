#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void remove_newline(char* string); 
void read_from_file(char* filename);

//pre-written tables
typedef struct {
    char title[50];
    char author[50];
    char isbn[20];
    char checkout_date[11];
    char return_date[11];
} Book;

typedef struct {
    char name[50];
    char dob[11]; 
    char address[100];
    Book* checked_out_book;
} User;

void write_to_file(void* data, char* type, char* filename) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Could not open file\n");
        return;
    }
    if (strcmp(type, "Book") == 0) {
        Book* book = (Book*)data;
        fprintf(file, "%s,%s,%s,%s,%s\n", book->title, book->author, book->isbn, book->checkout_date, book->return_date);
    } else if (strcmp(type, "User") == 0) {
        User* user = (User*)data;
        fprintf(file, "%s,%s,%s,%s\n", user->name, user->dob, user->address, user->checked_out_book ? user->checked_out_book->isbn : "None");
    }
    fclose(file);
}

void handle_command(char* command) {
    
    if (strcmp(command, ".checkout") == 0) { //enter data into Books table
        Book book;
        printf("Enter title: ");
        fgets(book.title, 50, stdin);
        remove_newline(book.title);
        printf("Enter author: ");
        fgets(book.author, 50, stdin);
        remove_newline(book.author);
        printf("Enter ISBN: ");
        fgets(book.isbn, 20, stdin);
        remove_newline(book.isbn);
        printf("Enter checkout date (YYYY-MM-DD): ");
        fgets(book.checkout_date, 20, stdin);
        remove_newline(book.checkout_date);
        printf("Enter return date (YYYY-MM-DD): ");
        fgets(book.return_date, 20, stdin);
        remove_newline(book.return_date);
        write_to_file(&book, "Book", "books.txt");

    } else if (strcmp(command, ".newUser") == 0) { //enter data into Users table
        User user;
        printf("Enter full name: ");
        fgets(user.name, 50, stdin);
        remove_newline(user.name);
        printf("Enter date of birth (YYYY-MM-DD): ");
        fgets(user.dob, 11, stdin);
        remove_newline(user.dob);
        printf("Enter address: ");
        fgets(user.address, 100, stdin);
        remove_newline(user.address);
        user.checked_out_book = NULL;
        write_to_file(&user, "User", "users.txt");

    } else if (strncmp(command, ".create ", 7) == 0) { //create a new table
        char* command_copy = strdup(command); //copy string
        char* token = strtok(command_copy, " "); //tokenize string
        token = strtok(NULL, " "); // table name
        char filename[50];
        strncpy(filename, token, 50);
        strcat(filename, ".txt"); // append .txt to the filename
        token = strtok(NULL, " "); // "("
        FILE* file = fopen(filename, "w"); // create a new file (table)
        if (file == NULL) {
            printf("Could not create table\n");
            free(command_copy); //deallocate memory to command_copy
            return;
        }
        while ((token = strtok(NULL, ",)")) != NULL) {
            fprintf(file, "%s,", token); // write the column name to the file
        }
        fseek(file, -1, SEEK_END); // remove the last comma
        fprintf(file, "\n");
        fclose(file);
        printf("Table created successfully\n");
        free(command_copy);//deallocate memory to command_copy

    }else if (strncmp(command, ".enterData ", 10) == 0) {
        char* command_copy = strdup(command);
        char* token = strtok(command_copy, " "); // tokenize
        token = strtok(NULL, " "); // table name
        char filename[50];
        strncpy(filename, token, 50);
        strcat(filename, ".txt"); // append .txt 
        FILE* file = fopen(filename, "a"); // open with "a" to append
        if (file == NULL) {
            printf("Could not open table\n");
            free(command_copy);
            return;
        }
        token = strtok(NULL, " "); // "("
        while ((token = strtok(NULL, ",)")) != NULL) {
            fprintf(file, "%s,", token); // write the data to the file
        }
        fseek(file, -1, SEEK_END); // remove the last comma
        fprintf(file, "\n"); // end the line
        fclose(file);
        printf("Data entered successfully\n");
        free(command_copy);

    }else if (strcmp(command, ".lookup") == 0) { //lookup command
        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        if (d) {
            while ((dir = readdir(d)) != NULL) {
                if (strstr(dir->d_name, ".txt") != NULL) { // if the file is a .txt file
                    printf("%s:\n", dir->d_name);
                    read_from_file(dir->d_name);
                }
            }
            closedir(d);
        }

    } else if (strcmp(command, ".exit") == 0) {
        exit(0);

    } else if (strcmp(command, ".help") == 0) {
        printf("Commands:\n");
        printf(".checkout: Create a new book checkout record\n");
        printf(".newUser: Create a new user\n");
        printf(".lookup: Print all records\n");
        printf(".create <table> (<column1> <type1>, ...): Create a new table with specified columns with field types string and int\n");
        printf(".enterData: Enter data into a table\n");
        printf(".exit: Exit the program\n");
        printf(".help: Print help message\n");
    }else {
        printf("Invalid command\n");
    }
}

void read_from_file(char* filename) {
    char buffer[255];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return;
    }
    while (fgets(buffer, 255, file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

void remove_newline(char* string) { //same logic used in tamidsh.c
    int length = strlen(string);
    if (length > 0 && string[length - 1] == '\n') {
        string[length - 1] = '\0';
    }
}

int main() {
    char command[50];
    printf("Welcome to the library database.\nTo get started, type .help.\n");
    while (1) {
        printf("> ");
        fgets(command, 50, stdin);
        remove_newline(command);
        handle_command(command);
    }
    return 0;
}