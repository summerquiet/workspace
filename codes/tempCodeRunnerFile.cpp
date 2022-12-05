#include <iostream>

using namespace std;


int main()
{
	int i=15;
	int count = 0;
	while (i > 0)
	{
		count++;
		i = i & (i - 1);
	}
	cout << count << endl;
	return 0;
}
