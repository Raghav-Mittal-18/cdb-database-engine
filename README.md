# CDB - Lightweight Database Engine

CDB is a lightweight database engine built from scratch using the C programming language.

The purpose of this project is to understand the fundamental concepts behind database systems by implementing a simplified database engine instead of relying on an existing DBMS.

## Project Objectives

- Understand how a database engine works internally
- Learn how tables and records can be represented in C
- Implement basic SQL-like commands
- Build a simple query parser
- Implement CRUD-style operations
- Implement persistent data storage
- Understand how different modules of a database engine work together
- Practice modular programming in C

## Technology Stack

- C
- GCC
- GDB
- Git and GitHub
- Linux / Ubuntu

## Current Status

### Version 0.1

CDB currently supports:

- Interactive command-line interface
- Database and table structures
- Multiple tables
- CREATE TABLE
- INSERT
- SELECT
- SELECT ... WHERE
- UPDATE ... WHERE
- INT and TEXT data types
- Database persistence
- Loading saved data when the program starts
- Saving data when the program exits
- help
- tables
- exit
## Supported Commands

### Create a Table

```sql

CREATE TABLE students (id INT, name TEXT, age INT)
### Insert Records

Example:

INSERT INTO students VALUES (1, "Raghav", 21)
INSERT INTO students VALUES (2, "Aman", 19)

### Select Records

Example:

SELECT * FROM students

### Select With a Condition

Example:

SELECT * FROM students WHERE id = 1

### Update Records

Example:

UPDATE students SET age = 22 WHERE id = 1

### Show Tables

Example:

tables

### Display Help

Example:

help

### Exit

Example:

exit

When the program exits, the database is automatically saved to disk.

## System Architecture

CDB is divided into multiple modules:

User
 |
 v
Command Line Interface
 |
 v
Parser
 |
 v
Executor
 |
 +-------------------+
 |                   |
 v                   v
Database            Storage
 |                   |
 v                   v
Tables            database.db
 |
 v
Records

### Main Modules

- main.c - Command-line interface and program flow
- parser.c - Parses SQL-like commands
- executor.c - Executes queries
- database.c - Manages multiple tables
- table.c - Manages tables and records
- record.c - Manages records
- storage.c - Saves and loads database data
## Data Representation

A database contains multiple tables.

Each table contains:

- Table name
- Column definitions
- Data types
- Records

Currently supported data types are:

- INT
- TEXT

Records store values using C structures and a union.

## Persistent Storage

CDB stores the database in:

data/database.db

The current implementation uses binary file storage with fwrite() and fread().

The complete fixed-size Database structure is written to and read from the file.

This approach is intentionally simple because the main goal of the project is to understand database concepts and C programming rather than building a production-level storage engine.

Because fixed-size structures are used, the database file can be larger than the amount of actual data stored in it.

## Project Structure

cdb-database-engine/
├── src/
│   ├── main.c
│   ├── table.c
│   ├── parser.c
│   ├── executor.c
│   ├── storage.c
│   ├── record.c
│   └── database.c
├── include/
│   ├── table.h
│   ├── parser.h
│   ├── executor.h
│   ├── storage.h
│   ├── record.h
│   └── database.h
├── tests/
├── data/
├── README.md
├── .gitignore
└── LICENSE

The database file inside data/ is generated locally and is ignored by Git.

## Compilation

Compile the project using GCC:

gcc -Wall -Wextra -std=c11 -Iinclude src/main.c src/table.c src/parser.c src/executor.c src/storage.c src/record.c src/database.c -o cdb

Run the database:

./cdb

## Example Session

CDB> CREATE TABLE students (id INT, name TEXT, age INT)
Table created successfully.

CDB> INSERT INTO students VALUES (1, "Raghav", 21)
Record inserted successfully.

CDB> INSERT INTO students VALUES (2, "Aman", 19)
Record inserted successfully.

CDB> SELECT * FROM students

Records:
Record 1: 1 | Raghav | 21
Record 2: 2 | Aman | 19

CDB> UPDATE students SET age = 22 WHERE id = 1
Record updated successfully.

CDB> SELECT * FROM students

Records:
Record 1: 1 | Raghav | 22
Record 2: 2 | Aman | 19

CDB> exit
Database saved successfully.
Goodbye!

## Current Limitations

- Only INT and TEXT data types are supported
- Only limited SQL-like syntax is supported
- Fixed-size arrays are used for tables and records
- Maximum table and record counts are predefined
- Error handling is basic
- No concurrent access support
- No transactions
- No query optimization
- No indexing
- No primary key enforcement
- DELETE is not implemented yet
- Storage is not optimized for large databases

## Future Scope

- DELETE command
- Better error handling
- Automated testing
- Primary key support
- Unique constraints
- More SQL conditions
- AND and OR operators
- Indexing
- More efficient storage formats
- Dynamic memory allocation
- Improved query execution
- Makefile-based build system

## Learning Outcomes

Through this project, the following concepts are explored:

- C structures and unions
- Arrays and strings
- Pointers
- Modular programming
- Header files
- File handling
- Binary file I/O
- Command parsing
- Query execution
- Data representation
- Database architecture
- Persistent storage
- Debugging using GDB
- Git and GitHub workflow

## Author

Raghav Mittal

B.Tech CSE - AI & ML
