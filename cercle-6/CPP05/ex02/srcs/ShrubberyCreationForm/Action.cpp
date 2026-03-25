/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Action.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:36:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 10:36:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>

void ShrubberyCreationForm::executeAction(void) const
{
    std::string filename = this->getName() + "_shrubbery";
    std::ofstream ofs(filename.c_str());
    if (!ofs)
    {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }
    ofs << "  _\\/_\n";
    ofs << "   /\\  \n";
    ofs << "  /  \\ \n";
    ofs << "   ||   \n";
    ofs << "   ||   \n";
    ofs << "  -----\n";
    ofs.close();
}
