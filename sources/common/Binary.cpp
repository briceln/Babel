/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Binary.cpp
*/

#include <algorithm>
#include "includes/common/Binary.hpp"

std::string	strToBinary(std::string	s){
	std::string	value;
	std::string	retVal;
	int n = s.length()-1;

	for (int i = 0; i <= n; i++)
	{
		retVal += std::bitset<8>(s[i]).to_string();
	}
	return retVal;
}

std::string	binaryToStr(std::string binary)
{
	std::string	result = "";
	char		parsed;
	unsigned int		mark = 0;
	int		nb;

	while (mark < binary.length()) {
		parsed = 0;
		nb = 0;
		for (unsigned int i = mark; i < mark+8; i++) {
			if (binary[i] == '1') {
				parsed |= 1 << (7 - nb);
			}
			nb++;
		}
		result.push_back(parsed);
		mark += 8;
	}
	return result;
}