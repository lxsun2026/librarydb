READMEdb.md

# Database Part 1: MVP
This project gives the MVP of a library database, able to modify two preexisting tables of users and books. It also allows
the user to create new tables with field types of string and int. The user is able to save data to txt files to achieve
persistence. 
## Instructions
Download librarydb.c file. In Linux terminal, compile with gcc -o librarydb librarydb.c. Run with ./librarydb. 

## Known Issues
For a few commands, I assume the user is putting the correct syntax, such as creating a file name. 
When I use .lookup, I end up opening all files in the directory. I think I have to create a new file just for tables.

## Implementing update and delete functions
Here is how I would implement:

Update: I need to pass in the file ID I want to update. If found, I will need to pass the key for the record I want to update. If it is found, write the updated record to a temporary file. I could either replace the old file or copy the contents of the temp file and paste them in the original one.

Delete: I need to pass in the file ID I want to update. If found, I will need to pass the key for the record I want to delete. I would go line by line and write to a temp file, skipping the key that matches what was passed in to be deleted. I could either replace the old file or copy the contents of the tmep file and paste them in the original one. 
