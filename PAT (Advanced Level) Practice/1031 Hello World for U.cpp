#include <iostream>
#include <string>
using namespace std;
int main() {
	string str;
	cin >> str;
	int len = str.length(), side = 0, low = 0;
	for (int i = len; i >= 3; --i) {
		if ((len + 2 - i) % 2 == 0) {
			side = (len + 2) / 3 - 1;
			low = len - side * 2;
			break;
		}
	}
	for (int i = 0; i < side; ++i) {
		printf("%c", str[i]);
		for (int j = 1; j < low - 1; ++j) printf(" ");
		printf("%c\n", str[len - i - 1]);
	}
	cout << str.substr(side, low);
	return 0;
}
