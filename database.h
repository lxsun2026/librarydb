#ifndef __database_h__
#define __database_h__

typedef struct {
    int socket;
} Database;

Database* database_connect(char *port);
int database_execute(Database* database, char *command);
void database_close(Database* database); //based off recommended functions

#endif // __database_h__

