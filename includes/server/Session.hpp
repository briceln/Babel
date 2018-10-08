/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/
#ifndef CPP_BABEL_2018_SESSION_HPP
#define CPP_BABEL_2018_SESSION_HPP

#include <boost/asio.hpp>
#include <list>
#include "includes/server/Client.hpp"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
	Session(boost::asio::io_service &ios, std::list<Client>&, std::list<std::string>&);

	tcp::socket &get_socket();
	void		start();
	void		handle_read(std::shared_ptr<Session> &s, const boost::system::error_code &err, size_t bytes_transferred);
	void		handle_write(std::shared_ptr<Session> &s, const boost::system::error_code &err, size_t bytes_transferred);
	std::string	check_code(std::string);
private:
	tcp::socket socket;
	enum {
		max_length = 1024
	};
	char			data[max_length];
	std::list<Client>	&participants_list;
	std::list<std::string>	&msg_list;
};

#endif //CPP_BABEL_2018_SESSION_HPP
