/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#include <iostream>
#include "includes/server/Server.hpp"

int main(int argc, char *argv[])
{
	try {
		boost::asio::io_service ios;
		Server s(ios, 8080);
		ios.run();
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
