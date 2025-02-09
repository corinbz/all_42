#include "Account.hpp"
#include <iostream>

int main()
{
	Account test(20);
	test.makeDeposit(5);
	test.makeWithdrawal(99);
	test.displayAccountsInfos();
}
