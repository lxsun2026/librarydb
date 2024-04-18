#include "database.h"
#include "sockutils.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for close() function

Database* database_connect(char *port) {
    Database* db = malloc(sizeof(Database));
    if (!db) {
        return NULL; //failed memory allocation
    }
    db->socket = make_server(port, 5);
    if (db->socket < 0) {
        free(db);
        return NULL; //if failed socket creation
    }
    return db; 
}

int database_execute(Database* database, char *command) {
    if (!database) { //database not there
        return DATABASE_NULL_POINTER; 
    }
    ssize_t bytes_written = write(database->socket, command, strlen(command));
    if (bytes_written < 0) { //nothing written
        return DATABASE_WRITE_ERROR; 
    }
    return DATABASE_SUCCESS;
}

void database_close(Database* database) {
    if (!database) {
        return;
    }
    close(database->socket);
    free(database);
}
