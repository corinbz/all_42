#include "../include/Account.hpp"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <iterator>

// WARN: do i need it? init default values
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

//default constructor
Account::Account(){}

//destructor
Account::~Account(void) {
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
				<< ";" << "amount:" << this->_amount
				<< ";closed"  << std::endl;
}

//constructor with specified deposit;
Account::Account(int deposit)
{
	this->_accountIndex = Account::_nbAccounts;
	this->_amount = deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;

	Account::_totalAmount += this->_amount;
	Account::_nbAccounts++;

	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
				<< ";" << "amount:" << this->_amount
				<< ";created" << std::endl;
}

//getters
int Account::getNbAccounts()
{
	return _nbAccounts;
}

int Account::getTotalAmount()
{
	return _totalAmount;
}

int Account::getNbDeposits()
{
	return _totalNbDeposits;
}

int Account::getNbWithdrawals()
{
	return _totalNbWithdrawals;
}

int Account::checkAmount(void) const
{
	return this->_amount;
}

void Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
				<< ";" << "p_amount:" << checkAmount()
				<< ";" << "deposit:" << deposit;
	this->_amount += deposit;
	this->_nbDeposits++;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;
	std::cout << ";" << "amount:" << checkAmount() << ";"
				<< "nb_deposits:" << this->_nbDeposits
				<< std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
				<< ";" << "p_amount:" << checkAmount()
				<< ";" << "withdrawal:";
	if (withdrawal > checkAmount())
	{
		std::cout << "refused" << std::endl;
		return false;
	}
	this->_amount -= withdrawal;
	this->_nbWithdrawals++;
	Account::_totalNbWithdrawals++;
	Account::_totalAmount -= withdrawal;
	std::cout << withdrawal << ";" << "amount:"
				<< checkAmount() << ";"
				<< "nb_withdrawals:" << this->_nbWithdrawals
				<< std::endl;
	return true;
}

void Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
		<< "amount:" << checkAmount() << ";"
		<< "deposits" << this->_nbDeposits << ";"
		<< "withdrawals" << this->_nbWithdrawals << std::endl;
}

void Account::displayAccountsInfos()
{
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts()
				<< ";" << "total:" << getTotalAmount()
				<< ";" << "deposits:" << getNbDeposits()
				<< ";" << "withdrawals:" << getNbWithdrawals()
				<< std::endl;
}

void Account::_displayTimestamp(void) 
{
    // Get current time
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[20];  // Buffer to hold our formatted string: [YYYYMMDD_HHMMSS]
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(buffer, sizeof(buffer), "[%Y%m%d_%H%M%S] ", timeinfo);
    
    std::cout << buffer;
}

