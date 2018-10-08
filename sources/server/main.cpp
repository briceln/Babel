/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#include <iostream>
#include "includes/server/Server.hpp"
#include "includes/common/Binary.hpp"

int main(int ac, char **argv)
{
	int	port;

	if (ac != 2) {
		std::cerr << "Usage: ./babel_server port" << std::endl;
		std::cerr << "Port must me a number" << std::endl;
		return (84);
	}
	port = atoi(argv[1]);
	if (port <= 0) {
		std::cerr << "Bad port value" << std::endl;
		return (84);
	}
	try {
		boost::asio::io_service ios;
		Server s(ios, port);
		ios.run();
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
