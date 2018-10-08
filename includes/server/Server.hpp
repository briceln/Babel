/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/
#ifndef CPP_BABEL_2018_SERVER_HPP
#define CPP_BABEL_2018_SERVER_HPP

#include <boost/asio.hpp>
#include <list>
#include "Session.hpp"
#include "Client.hpp"

using boost::asio::ip::tcp;

class Server {
public:
	Server(boost::asio::io_service &ios, unsigned short port);
	void handle_accept(std::shared_ptr<Session> session, const boost::system::error_code &err);
private:
	boost::asio::io_service &ios;
	tcp::acceptor          acceptor;
	std::list<Client>      _participants;
	std::list<std::string> _msg;
};

#endif //CPP_BABEL_2018_SERVER_HPP
