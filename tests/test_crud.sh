#!/bin/bash

set -e

PROJECT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
TEST_DIR="$(mktemp -d)"

cleanup() {
    rm -rf "$TEST_DIR"
}
trap cleanup EXIT

cp -r "$PROJECT_DIR/src" "$PROJECT_DIR/include" "$PROJECT_DIR/Makefile" "$TEST_DIR/"
cp -r "$PROJECT_DIR/tests" "$TEST_DIR/"
mkdir -p "$TEST_DIR/data"

cd "$TEST_DIR"

echo "=============================="
echo " CDB CRUD TEST"
echo "=============================="

make clean
make

OUTPUT=$(printf '%s\n' \
"CREATE TABLE test_students (id INT, name TEXT, age INT)" \
"INSERT INTO test_students VALUES (1, \"Raghav\", 21)" \
"INSERT INTO test_students VALUES (2, \"Aman\", 19)" \
"SELECT * FROM test_students" \
"UPDATE test_students SET age = 22 WHERE id = 1" \
"SELECT * FROM test_students" \
"DELETE FROM test_students WHERE id = 2" \
"SELECT * FROM test_students" \
"exit" | ./cdb)

echo "$OUTPUT"
echo ""
echo "Checking results..."

check() {
    if echo "$OUTPUT" | grep -Fq "$1"; then
        echo "PASS: $2"
    else
        echo "FAIL: $2"
        exit 1
    fi
}

check "Table created successfully." "CREATE"
check "Record inserted successfully." "INSERT"
check "Record updated successfully." "UPDATE"
check "Record deleted successfully." "DELETE"
check "Record 1: 1 | Raghav | 22" "UPDATE result"
check "Record 2: 2 | Aman | 19" "INSERT result"

echo ""
echo ""
echo "Running DELETE parser edge-case tests..."

gcc -Wall -Wextra -std=c11 -Iinclude \
    tests/test_parse_delete.c src/parser.c src/table.c \
    -o /tmp/test_parse_delete

/tmp/test_parse_delete
rm -f /tmp/test_parse_delete
echo "All CRUD tests passed."
