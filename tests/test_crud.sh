#!/bin/bash

echo "=============================="
echo " CDB CRUD TEST"
echo "=============================="

OUTPUT=$(printf '%s\n' \
"CREATE TABLE test_students (id INT, name TEXT, age INT)" \
"INSERT INTO test_students VALUES (1, \"Raghav\", 21)" \
"INSERT INTO test_students VALUES (2, \"Aman\", 19)" \
"SELECT * FROM test_students" \
"UPDATE test_students SET age = 22 WHERE id = 1" \
"SELECT * FROM test_students" \
"DELETE FROM test_students WHERE id = 2" \
"SELECT * FROM test_students" \
"exit" \
| ./cdb)

echo "$OUTPUT"

echo ""
echo "Checking results..."

if echo "$OUTPUT" | grep -q "Table created successfully."; then
    echo "PASS: CREATE"
else
    echo "FAIL: CREATE"
fi

if echo "$OUTPUT" | grep -q "Record inserted successfully."; then
    echo "PASS: INSERT"
else
    echo "FAIL: INSERT"
fi

if echo "$OUTPUT" | grep -q "Record updated successfully."; then
    echo "PASS: UPDATE"
else
    echo "FAIL: UPDATE"
fi

if echo "$OUTPUT" | grep -q "Record deleted successfully."; then
    echo "PASS: DELETE"
else
    echo "FAIL: DELETE"
fi


echo ""
echo "Checking final database state..."

FINAL_RECORD_COUNT=$(echo "$OUTPUT" | grep -c "Record 1: 1 | Raghav | 22")

if [ "$FINAL_RECORD_COUNT" -ge 1 ]; then
    echo "PASS: Raghav record exists"
else
    echo "FAIL: Raghav record missing"
fi
