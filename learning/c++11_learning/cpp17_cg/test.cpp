//请编写一个函数，该函数计算出一个字节中被置 1的位的个数

#include<iostream>

int func1(unsigned char c)
{
	int ans=0;
	while(c) {
		c = c & (c - 1);
		ans++;
		printf("%x\n", c);
	}

	return ans;
}

int func2(unsigned char c)
{
	int ans=0;
	while(c) {
		ans += (c & 0x1) ? 1 : 0;
		c >>= 1;
		printf("%x\n", c);
	}

	return ans;
}

int func3(unsigned char c)
{
	int ans=0;
	while(c) {
		ans += (c & 0x80) ? 1 : 0;
		c <<= 1;
		printf("%x\n", c);
	}

	return ans;
}

int main()
{
	char input = 0xf1;
	printf("func1 %d\n", func1(input));
	printf("func2 %d\n", func2(input));
	printf("func3 %d\n", func3(input));
	return 0;
}
