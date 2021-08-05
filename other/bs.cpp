#include <iostream>
#include <bitset>
using namespace std;


int main() {
	int a;
	// cin >> a;

	cout << "before: " << bitset<32>(8) << endl;
	cout << "&     : " << bitset<32>(0b10101010101010101010101010101010) << endl;

	a = (8 & 0b10101010101010101010101010101010);

	cout << "after:  " << bitset<32>(a) << endl;

	return 0;
}

