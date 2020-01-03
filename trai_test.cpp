#include <iostream>
#include <string>
#include <vector>
#include "trai.h"

using namespace std;

int main(int argc, char **argv) {
    trai<string> tr;
    vector<string> ibrahim {"Ibrahim"};
    vector<string> ahmed {"Ibrahim", "Ahmed"};
    vector<string> omar {"Ibrahim", "Ahmed", "Omar"};
    vector<string> hla {"Ibrahim", "Ahmed", "Hla"};
    tr.insert(ahmed);
    vector<string> ret = tr.ls(ibrahim);
    cout << "list ibrahim" << endl;
    for (auto &i : ret) {
        cout << i << endl;
    }
    cout << "list ahmed" << endl;
    ret = tr.ls(ahmed);
    for (auto &i : ret) {
        cout << i << endl;
    }
    tr.insert(omar);
    tr.insert(hla);
    ret = tr.ls(ahmed);
    cout << "list ahmed" << endl;
    for (auto &i : ret) {
        cout << i << endl;
    }
    return 0;
}
