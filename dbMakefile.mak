all: librarydb

librarydb: librarydb.c
    gcc -o librarydb librarydb.c

clean:
    rm librarydb