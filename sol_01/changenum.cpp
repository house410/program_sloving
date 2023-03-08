#include <iostream>

using namespace std;

int rev(unsigned short n)
{
	unsigned short v = 0;

	while (n != 0) {

		v *= 10;
		v += n % 10;
		n /= 10;
	}
	return v;
}

int main()
{
	unsigned short n;
	cin >> n;
	cout << rev(n);

	return 0;
}