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

int main() {
    // input
    ifstream file("./test/input.txt");

    if (!file.is_open()) {
        cout << "File not found" << endl;
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

    auto start = chrono::high_resolution_clock::now();
    // vars
    map<char, bool> alfa;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (alfa.find(row[i][j]) == alfa.end()) {
                alfa[row[i][j]] = false;
            }
        }
    }

    int iter=1, i=0, mark = 0, dataRow[n], dataCol[n];
    initData(dataRow, n);
    initData(dataCol, n);

    // process
    while(i >= 0 && i < n) {
        int j=mark;
        while(j < n) {
            int prev = (i==0)?-2:dataRow[i-1];
            if (isEmpty(n, j, dataCol, prev, alfa[row[i][j]])) {
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
    }

    // print
    for (int i=0; i<n; i++) {
        for (int j=0; j<dataRow[i]; j++) {
            cout << row[i][j];
        }
        cout << "+";
        for (int j=dataRow[i]+1; j<n; j++) {
            cout << row[i][j];
        }
        cout << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::milliseconds>(end-start);
    cout << "Program elapsed in " << dur.count() << "ms" << endl;
    cout << "A total of " << iter << " cases were checked" << endl;
    cout << "Do you want to save the result? (Y/n)" << endl << ">> ";
    // ntaran dh outputny

}
