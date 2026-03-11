/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sed.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:01:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/02 20:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>

void    replace(std::string filename, std::string s1, std::string s2)
{
    std::ifstream inFile(filename.c_str());
    if (!inFile.is_open())
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string content = buffer.str();
    inFile.close();
    if (s1.empty())
    {
        std::cerr << "Error: Search string cannot be empty." << std::endl;
        return;
    }
    size_t pos = 0;
    while ((pos = content.find(s1, pos)) != std::string::npos)
    {
        content.erase(pos, s1.length());
        content.insert(pos, s2);
        pos += s2.length();
    }
    std::ofstream outFile((filename + ".replace").c_str());
    if (outFile.is_open())
    {
        outFile << content;
        outFile.close();
    }
    else
        std::cerr << "Error: Unable to create output file." << std::endl;
}

int main(int argc, char **argv)
{
    if (argc == 4)
        replace(argv[1], argv[2], argv[3]);
    else
        std::cerr << "Usage: " << argv[0] << " <filename> <find> <replace>" << std::endl;
    return 0;
}