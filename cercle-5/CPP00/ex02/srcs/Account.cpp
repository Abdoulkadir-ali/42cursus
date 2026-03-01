/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 02:00:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/01 02:21:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"

int Account::getNbAccounts(void)
{
    return 	_nbAccounts;
}

int Account::getTotalAmount(void)
{
    return _totalAmount;
}

int Account::getNbDeposits(void)
{
    return _totalNbDeposits;
}

int Account::getNbWithdrawals(void)
{
    return _totalNbWithdrawals;
}

#include <ctime>


static void PrintNow(void)
{
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", std::localtime(&now));
    std::cout << "[" << buf << "] ";
}

static void displayTotalAccountsInfos(void)
{
    PrintNow();
    std::cout << "deposits:" << getTotalNbDeposits() << ";";
    std::cout << "deposits:" << getTotalNbWithdrawals() << ";";
    std::cout << "withdrawals:" << getTotalAmount() << ";";
}
    
void Account::displayAccountsInfos(void)
{
    for (unsigned int = 0; i < getNbAccounts(); ++i)
    {
        PrintNow();
        std::cout << "index:" << i << ";";
        std::cout << "deposits:" << getNbDeposits() << ";";
        std::cout << "withdrawals:" << getNbWithdrawals() << ";";
    }
    displayTotalAccountsInfos();
}
