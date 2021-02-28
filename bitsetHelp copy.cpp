#include <iostream>
#include <bitset>
using namespace std;


int main() {
	int a;
	cin >> a;

	cout << "before: " << bitset<32>(a) << endl;
	cout << "&     : " << bitset<32>(0b0000000001111) << endl;

	a = (a & 0b0000000001111);

	cout << "after:  " << bitset<32>(a) << endl;
	int k = a>>2;
	cout << bitset<32>(k) << endl;

	return 0;
}