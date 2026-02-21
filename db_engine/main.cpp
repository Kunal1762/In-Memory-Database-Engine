#include <iostream>
#include "../include/database.h"
#include <vector>
#include <string>

using namespace std;

void printRow(row* r) {
    if (!r) {
        cout << "NULL ROW\n";
        return;
    }

    for (size_t i = 0; i < r->get_size(); i++) {
        Value v = r->get(i);

        if (holds_alternative<int>(v))
            cout << get<int>(v);
        else if (holds_alternative<string>(v))
            cout << get<string>(v);
        else if (holds_alternative<double>(v))
            cout << get<double>(v);
        else if (holds_alternative<bool>(v))
            cout << (get<bool>(v) ? "true" : "false");

        cout << " | ";
    }
    cout << endl;
}

int main() {

    Database db;

    cout << "\n========== CREATE TABLE TEST ==========\n";

    vector<column> cols = {
        {"id", Type::INT},
        {"name", Type::STRING},
        {"salary", Type::DOUBLE},
        {"active", Type::BOOL}
    };

    schema empSchema(cols, 0);

    cout << "Create Employee table -> "
         << db.createTable("Employee", empSchema) << endl;

    cout << "Duplicate Employee table -> "
         << db.createTable("Employee", empSchema) << endl;

    auto emp = db.getTable("Employee");

    cout << "\n========== BASIC INSERT TEST ==========\n";

    emp->insert(row({1, "Kunal", 50000.5, true}));
    emp->insert(row({2, "Atharv", 45000.75, true}));
    emp->insert(row({3, "Somesh", 30000.25, false}));

    printRow(emp->find(1));
    printRow(emp->find(2));
    printRow(emp->find(3));

    cout << "\n========== PK VIOLATION TEST ==========\n";
    cout << emp->insert(row({1, "Duplicate", 0.0, false})) << endl;

    cout << "\n========== WRONG TYPE TEST ==========\n";
    cout << emp->insert(row({10, 999, 123.4, true})) << endl;

    cout << "\n========== WRONG COLUMN COUNT TEST ==========\n";
    cout << emp->insert(row({11, "OnlyName"})) << endl;

    cout << "\n========== UPDATE TEST ==========\n";

    cout << emp->update(2, 1, "UpdatedName") << endl;
    cout << emp->update(2, 2, 99999.99) << endl;
    cout << emp->update(2, 3, false) << endl;

    printRow(emp->find(2));

    cout << "Update PK column -> "
         << emp->update(2, 0, 100) << endl;

    cout << "Update wrong type -> "
         << emp->update(2, 2, string("WrongType")) << endl;

    cout << "\n========== DELETE TEST ==========\n";

    cout << emp->remove(3) << endl;
    printRow(emp->find(3));

    cout << "Double delete -> "
         << emp->remove(3) << endl;

    cout << "Update after delete -> "
         << emp->update(3, 1, "Ghost") << endl;

    cout << "\n========== HEAVY INSERT TEST ==========\n";

    for (int i = 4; i <= 1000; i++) {
        emp->insert(row({i, "User" + to_string(i), i * 1000.0, i % 2 == 0}));
    }

    cout << "Inserted 1000 rows.\n";

    cout << "\n========== HEAVY DELETE (ODD IDs) ==========\n";

    for (int i = 5; i <= 1000; i += 2) {
        emp->remove(i);
    }

    cout << "Deleted odd rows.\n";

    cout << "\n========== FREE LIST REUSE TEST ==========\n";

    emp->insert(row({2000, "ReusedSlot", 77777.7, true}));
    printRow(emp->find(2000));

    cout << "\n========== CROSS TABLE ISOLATION TEST ==========\n";

    vector<column> deptCols = {
        {"id", Type::INT},
        {"deptName", Type::STRING},
        {"budget", Type::DOUBLE},
        {"active", Type::BOOL}
    };

    schema deptSchema(deptCols, 0);

    db.createTable("Department", deptSchema);

    auto dept = db.getTable("Department");

    dept->insert(row({1, "HR", 100000.0, true}));
    dept->insert(row({2, "Finance", 200000.0, true}));

    cout << "Employee id=1:\n";
    printRow(emp->find(1));

    cout << "Department id=1:\n";
    printRow(dept->find(1));

    cout << "\n========== TABLE DELETE TEST ==========\n";

    cout << db.deleteTable("Department") << endl;
    cout << (db.getTable("Department") == nullptr) << endl;

    cout << "\n========== FINAL SANITY CHECK ==========\n";

    printRow(emp->find(1));
    printRow(emp->find(2));
    printRow(emp->find(2000));

    cout << "\n===== STORAGE ENGINE FULL STRESS TEST COMPLETE =====\n";

    return 0;
}

//g++ -std=c++17 -Iinclude main.cpp src/row_storage.cpp src/database.cpp -o db.exe