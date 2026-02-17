#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <chrono>
using namespace std;

void initData(int *data, int n) {
    for (int i=0; i<n; i++) {
        data[i] = -1;
    }
}

bool isEmpty(int n, int cur, int *dataCol, int prev, bool area) {
    if (cur == prev-1 || cur==prev+1 || cur==prev) return false;
    if (dataCol[cur] != -1) return false;
    return !area;
}

void printRes(int *dataRow, int *dataCol, vector<string> row, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<dataRow[i]; j++) {
            cout << row[i][j];
        }
        if (dataRow[i] != -1) cout << "*";;
        for (int j=dataRow[i]+1; j<n; j++) {
            cout << row[i][j];
        }
        cout << endl;
    }
}

int main() {
    // input
    string fileName = "./testcase/", tempFilename;
    cout << "-- Queens Solver --\n";
    cout << "Input your test case filename in .txt (e.g. input.txt):\n";
    cout << ">> ";
    cin >> tempFilename;
    fileName.append(tempFilename);
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "File not found!\n";
        return 1;
    }

    vector<string> row;
    int it=0, n=0;
    string temp;
    getline(file, temp);
    n = temp.length();
    row.push_back(temp);
    while (it < n-1 && getline(file, temp)) {
        row.push_back(temp);
        it++;
    }
    file.close();

    if (row.size() != n) {
        cout << "Invalid file: Row and Column mismatch\n";
        cout << "Row = " << row.size() << "\n";
        cout << "Col = " << n << "\n";
        return 1;
    }

    // vars
    map<char, bool> alfa;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (alfa.find(row[i][j]) == alfa.end()) {
                alfa[row[i][j]] = false;
            }
        }
    }
    if (alfa.size() != n) {
        cout << "Invalid file: Color mismatch" << endl;
        return 1;
    }

    int iter=1, i=0, mark = 0, dataRow[n], dataCol[n];
    initData(dataRow, n);
    initData(dataCol, n);

    // process
    int choice;
    cout << "Choose one of the two algorithms:\n";
    cout << "1. Pure Brute-force\n";
    cout << "2. Backtrack optimization\n";
    cout << ">> ";
    cin >> choice;

    cout << "\nSearching...\n";
    cout << "----------\n";
    auto start = chrono::high_resolution_clock::now();
    if (choice == 1) { // exhaustive
        while (true) {
            while(i >= 0 && i < n) {
                bool found = false;
                int j=mark;
                while(j < n) {
                    if (dataCol[j] == -1) {
                        dataCol[j] = i; 
                        dataRow[i] = j;
                        mark = 0;
                        i++;
                        found = true;
                        break;
                    }
                    else j++;
                }
                if (!found) {
                    if (i==0) break;
                    dataCol[dataRow[i-1]] = -1;
                    mark = dataRow[i-1]+1;
                    dataRow[i-1] = -1;
                    i--;
                    iter++;
                }
                if (iter%100000000 == 0) {
                    printRes(dataRow, dataCol, row, n);
                    cout << "Tries = " << iter << endl;
                    cout << "----------\n";
                }
            }

            // iter++;
            bool check = true;
            
            for (int k = 1; k < n; k++) {
                int cur = dataRow[k];
                int prev = dataRow[k-1];
                if (cur == prev - 1 || cur == prev + 1) {
                    check = false;
                    break;
                }
            }

            if (check) {
                map<char, bool> secAlfa;
                for (int k = 0; k < n; k++) {
                    char c = row[k][dataRow[k]];
                    if (secAlfa.count(c)) {
                        check = false;
                        if (iter == 1) {
                            cout << "alfa\n";
                        }
                        break;
                    }
                    secAlfa[c] = true;
                }
            }

            if (check) {
                break;
            } else {
                if (i==0) break;
                i--; 
                int prevCol = dataRow[i];
                dataCol[prevCol] = -1;
                dataRow[i] = -1;
                mark = prevCol + 1;
            }
        }
    } else if (choice == 2) { // backtrack
        while(i >= 0 && i < n) {
            int j=mark;
            while(j < n) {
                int prev = (i==0)?-2:dataRow[i-1];
                if (isEmpty(n, j, dataCol, prev, alfa[row[i][j]])) { // masukin kalo empty doang
                    dataCol[j] = i;
                    dataRow[i] = j;
                    alfa[row[i][j]] = true;
                    mark = 0;
                    i++;
                    break;
                } else {
                    j++;
                }
            }
            if (j >= n) {
                if (i==0) break;
                alfa[row[i-1][dataRow[i-1]]] = false;
                dataCol[dataRow[i-1]] = -1;
                mark = dataRow[i-1]+1;
                dataRow[i-1] = -1;
                i--;
                iter++;
            }
            // printRes(dataRow, dataCol, row, n);
            // cout << "----------\n";
            if (iter%100000000 == 0) {
                printRes(dataRow, dataCol, row, n);
                cout << "Tries = " << iter << endl;
                cout << "----------\n";
            }
        }
    } else {
        cout << "Invalid choice!\n";
        return 1;
    }

    // print
    printRes(dataRow, dataCol, row, n);
    cout << "----------\n";

    auto end = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::milliseconds>(end-start);
    cout << "Program elapsed in " << dur.count() << "ms\n";
    cout << "A total of " << iter << " cases were checked\n";

    if (dataRow[0] == -1 && dataCol[0] == -1) {
        cout << "Test case configuration can't be solved!\n";
    } else {
        cout << "\nDo you want to save the result?\n";
        cout << "1. Yes\n";
        cout << "2. No\n";
        cout << ">> ";
        cin >> choice;

        if (choice == 1) {
            fileName = "./result/", tempFilename = "";
            cout << "\nInput your target filename in .txt (e.g. output.txt):\n";
            cout << ">> ";
            cin >> tempFilename;
            fileName.append(tempFilename);
            ofstream res(fileName);

            for (int i=0; i<n; i++) {
                for (int j=0; j<dataRow[i]; j++) {
                    res << row[i][j];
                }
                if (dataRow[i] != -1) res << "*";;
                for (int j=dataRow[i]+1; j<n; j++) {
                    res << row[i][j];
                }
                res << endl;
            }
            res.close();
            cout << "File saved!\n";
        }
    }

    cout << "\nProgram terminated\n";
    return 0;
}
