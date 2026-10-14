# CDB - Lightweight Database Engine

CDB is a lightweight database engine built from scratch using the C programming language. It provides a command-line interface for creating tables, inserting records, retrieving data, updating records, and deleting records.

The purpose of this project is to understand the fundamental concepts behind database systems by implementing a simplified database engine instead of relying on an existing DBMS.

## Project Objectives

- Understand how a database engine works internally
- Learn how tables and records can be represented in C
- Implement SQL-like commands and a basic query parser
- Perform CRUD operations: Create, Read, Update, and Delete
- Implement persistent data storage using binary files
- Understand how database modules interact with one another
- Practice modular programming in C

## Technology Stack

- **Language:** C
- **Compiler:** GCC
- **Debugging:** GDB
- **Build System:** Make
- **Version Control:** Git and GitHub
- **Environment:** Linux / Ubuntu
- **Testing:** Bash shell script

## Current Status

### Version 0.1

CDB currently supports:

- Interactive command-line interface
- Multiple tables
- Table creation with column definitions
- Record insertion
- Record selection
- Conditional record selection using `WHERE`
- Conditional record updates
- Conditional record deletion
- `INT` and `TEXT` data types
- Database persistence using binary file storage
- Loading saved database data when the program starts
- Saving database data when the program exits
- `help` command
- `tables` command
- `exit` command
- Automated CRUD testing

## Supported Commands

### 1. Create a Table

Create a table with column names and data types.

```sql
CREATE TABLE students (id INT, name TEXT, age INT)
```

Supported data types are `INT` and `TEXT`.

### 2. Insert Records

Insert records into an existing table.

```sql
INSERT INTO students VALUES (1, "Raghav", 21)
INSERT INTO students VALUES (2, "Aman", 19)
```

### 3. Select All Records

Retrieve all records from a table.

```sql
SELECT * FROM students
```

### 4. Select Records Using a Condition

Retrieve records matching a condition.

```sql
SELECT * FROM students WHERE id = 1
```

### 5. Update Records

Update a column value for records matching a condition.

```sql
UPDATE students SET age = 22 WHERE id = 1
```

### 6. Delete Records

Delete records matching a condition.

```sql
DELETE FROM students WHERE id = 2
```

### 7. Show Tables

Display the tables stored in the database.

```text
tables
```

### 8. Display Help

Display the available commands.

```text
help
```

### 9. Exit

Exit the application.

```text
exit
```

The application saves the database when it exits normally.

## System Architecture

The project is divided into modules responsible for parsing commands, executing operations, managing tables and records, and storing data.

```text
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
        +------+------+
        |             |
        v             v
     Database       Storage
        |             |
        v             v
      Tables      database.db
        |
        v
      Records
```

### Main Modules

- `main.c` - Handles command-line interaction and overall program flow.
- `parser.c` - Parses SQL-like commands and extracts their components.
- `executor.c` - Executes database operations.
- `database.c` - Manages the database and multiple tables.
- `table.c` - Manages table definitions and table-related operations.
- `record.c` - Handles record-related functionality.
- `storage.c` - Saves and loads database data from disk.

Header files containing declarations and data structures are located in the `include/` directory.

## Data Representation

A database contains multiple tables. Each table stores its name, column definitions, data types, and records.

Currently supported data types are:

- `INT` - Stores integer values.
- `TEXT` - Stores text values.

C structures represent database objects, tables, columns, and records. A union is used to represent values of different supported data types.

The implementation uses fixed-size arrays and predefined limits for various database components.

## Persistent Storage

CDB stores persistent data in:

```text
data/database.db
```

The current implementation uses binary file operations through `fwrite()` and `fread()`.

The complete fixed-size `Database` structure is written to and read from the database file. This approach keeps the storage implementation simple and helps demonstrate basic file handling in C.

Because the implementation stores a fixed-size structure, the database file can be larger than the actual amount of data it contains.

**Important:** The current binary storage format is intended for this educational project. Changes to structure definitions or compiler/platform details may make previously saved database files incompatible.

## Project Structure

```text
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
│   └── test_crud.sh
├── data/
├── Makefile
├── README.md
├── .gitignore
└── LICENSE
```

The `data/` directory contains runtime database files. These files are ignored by Git and are not intended to be committed to the repository.

## Compilation and Execution

### Prerequisites

Make sure GCC and Make are installed on your system.

On Ubuntu, you can install the build tools using:

```bash
sudo apt update
sudo apt install build-essential
```

### Build the Project

From the project root directory, run:

```bash
make
```

This compiles the C source files and creates the `cdb` executable.

### Run CDB

```bash
./cdb
```

If the runtime data directory does not exist, create it before starting the application:

```bash
mkdir -p data
```

### Run Automated CRUD Tests

Run the test script from the project root directory:

```bash
bash tests/test_crud.sh
```

The test script exercises basic CRUD operations and checks expected output.

### Clean Build Output

To remove the compiled executable:

```bash
make clean
```

The clean command does not remove the database files stored in `data/`.

## Example Session

The following example illustrates a typical interaction with CDB. The output may vary depending on the current database contents.

```text
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

CDB> DELETE FROM students WHERE id = 2
Record deleted successfully.

CDB> exit
Database saved successfully.
Goodbye!
```

## Current Limitations

- Only `INT` and `TEXT` data types are supported.
- Only a limited subset of SQL-like syntax is implemented.
- Fixed-size arrays impose limits on tables, columns, and records.
- Error handling and input validation are basic.
- No concurrent access support.
- No transaction support.
- No query optimization.
- No indexing.
- No primary key or unique constraint enforcement.
- The binary storage format is not designed for portability across arbitrary structure changes or platforms.
- The storage implementation is not optimized for large databases.

## Future Scope

Potential improvements include:

- Primary key and unique constraint support
- Additional data types
- More SQL conditions, including `AND` and `OR`
- Indexing for faster queries
- More efficient and portable storage formats
- Dynamic memory allocation
- Improved input validation and error handling
- Transaction support
- Query optimization
- Improved automated test coverage

## Learning Outcomes

This project provides practical experience with:

- C structures and unions
- Arrays, strings, and pointers
- Modular programming and header files
- File handling and binary file I/O
- Command parsing
- Query execution
- Database and record representation
- Persistent storage
- Debugging using GDB
- Compilation using GCC and Make
- Automated testing
- Git and GitHub workflows

## Author

**Raghav Mittal**

B.Tech - Computer Science and Engineering (AI & ML)
