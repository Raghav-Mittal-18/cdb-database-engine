# CDB - Lightweight Database Engine

CDB is a lightweight database engine being built from scratch using the C programming language.

The purpose of this project is to understand the fundamental concepts behind Database Management Systems by implementing a simplified database engine rather than relying on an existing DBMS.

## Project Goals

- Understand how database engines work internally
- Learn how data can be represented and stored using C
- Implement tables and records
- Implement CRUD operations
- Build a simple query parser
- Implement persistent storage
- Implement basic indexing
- Study database performance and storage concepts

## Technology Stack

- C
- GCC
- Make
- GDB
- Git

## Current Status

### Version 0.1

Currently implemented:

- Basic CDB command-line interface
- Interactive command loop
- `help` command
- `exit` command
- Unknown command handling

## Planned Features

- Database and table structures
- CREATE TABLE
- INSERT
- SELECT
- UPDATE
- DELETE
- WHERE conditions
- Primary key support
- Persistent file storage
- Indexing
- Testing
- Error handling

## Project Structure

```text
cdb-database-engine/
├── src/
├── include/
├── tests/
├── data/
├── README.md
├── Makefile
├── .gitignore
└── LICENSE
