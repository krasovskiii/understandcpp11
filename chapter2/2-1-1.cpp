#include <iostream>
using namespace std;

int main() {
    cout << "Standard Clib: " << __STDC_HOSTED__ << endl;   // Standard Clib: 1
    cout << "Standard C: " << __STDC__ << endl;             // Standard C: 1
    // cout << "C Stardard version: " << __STDC_VERSION__ << endl; //compile error: not declared in this scope
    cout << "ISO/IEC " << __STDC_ISO_10646__ << endl;       // ISO/IEC 200009 -> local ubuntu: 201706
}
