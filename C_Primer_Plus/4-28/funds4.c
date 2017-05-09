/* funds4.c --把结构数组传递给函数　*/
#include <stdio.h>
#include <string.h>
#define FUNDLEN 50
#define N 2

struct funds {
	char 	bank[FUNDLEN];
	double 	bankfund;
	char	save[FUNDLEN];
	double	savefund;
};

double sum(const struct funds money [],int n);

int main()
{
	struct funds jones[N] = {
			{	
				"Garlic-Melon Bank",
				4032.27,
				"Lucky's Savings and Loan",
				8543.94
			},
			{
				"Honest Jack's Bank",
				3620.66,
				"Party Time Savings",
				3802.91
			}
	};

printf("The Joneses have a total of $%.2f.\n",sum(jones,N));


	return 0;
}


double sum(const struct funds money[],int n)
{	
	double total;
	int i;
	
	for(i = 0,total = 0;i < n;i++)
		total += money[i].bankfund + money[i].savefund;


	return(total);
}
