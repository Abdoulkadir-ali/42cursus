/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 02:00:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 19:21:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(void)
{
	_accountIndex = _nbAccounts;
	_amount = 0;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	_nbAccounts++;
}

Account::Account(int initial_deposit)
{
    _accountIndex = _nbAccounts;
    _amount = initial_deposit;
    _nbDeposits = 0;
    _nbWithdrawals = 0;
    _nbAccounts++;
    _totalAmount += initial_deposit;

    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";"
              << "amount:" << _amount << ";"
              << "created" << std::endl;
}

Account::~Account(void)
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";"
              << "amount:" << _amount << ";"
              << "closed" << std::endl;

    _nbAccounts--;
    _totalAmount -= _amount;
}

int Account::getNbAccounts(void){return (_nbAccounts);}
int Account::getTotalAmount(void){return (_totalAmount);}
int Account::getNbDeposits(void){return (_totalNbDeposits);}
int Account::getNbWithdrawals(void){return (_totalNbWithdrawals);}
int Account::checkAmount(void) const
{
    return (_amount);
}

void Account::makeDeposit(int deposit)
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";"
              << "p_amount:" << _amount << ";"
              << "deposit:" << deposit << ";";

    _amount += deposit;
    _totalAmount += deposit;
    _nbDeposits++;
    _totalNbDeposits++;
	
    std::cout << "amount:" << _amount << ";"
              << "nb_deposits:" << _nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";"
              << "p_amount:" << _amount << ";"
              << "withdrawal:";

    if (_amount < withdrawal) {
        std::cout << "refused" << std::endl;
        return (false);
    }

    std::cout << withdrawal << ";";
    _amount -= withdrawal;
    _totalAmount -= withdrawal;
    _nbWithdrawals++;
    _totalNbWithdrawals++;
    std::cout << "amount:" << _amount << ";" << "nb_withdrawals:" << _nbWithdrawals << std::endl;
    return (true);
}

void Account::_displayTimestamp(void)
{
	char	buf[20];

	std::time_t now = std::time(NULL);
	std::strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", std::localtime(&now));
	std::cout << "[" << buf << "] ";
}

void Account::displayAccountsInfos(void)
{
	_displayTimestamp();
    std::cout << "accounts:" << _nbAccounts << ";";
    std::cout << "total:" << _totalAmount << ";";
	std::cout << "deposits:" << _totalNbDeposits << ";";
	std::cout << "withdrawals:" << _totalNbWithdrawals << ";" << std::endl;
}

void Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
    std::cout << "amount:" << _amount << ";";
	std::cout << "deposits:" << _nbDeposits << ";";
	std::cout << "withdrawals:" << _nbWithdrawals << ";" << std::endl;
}