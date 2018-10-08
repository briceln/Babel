/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/
#ifndef CPP_BABEL_2018_SESSION_HPP
#define CPP_BABEL_2018_SESSION_HPP

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
	Session(boost::asio::io_service &ios);

	tcp::socket &get_socket();
	void start();
	void handle_read(std::shared_ptr<Session> &s, const boost::system::error_code &err, size_t bytes_transferred);
private:
	tcp::socket socket;
	enum {
		max_length = 1024
	};
	char        data[max_length];
};

#endif //CPP_BABEL_2018_SESSION_HPP
