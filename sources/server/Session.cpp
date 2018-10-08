/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#include <boost/bind.hpp>
#include <iostream>
#include "includes/server/Session.hpp"

Session::Session(boost::asio::io_service &ios) : socket(ios)
{
}

tcp::socket &Session::get_socket()
{
	return socket;
}

void Session::start()
{
	socket.async_read_some(boost::asio::buffer(data, max_length),
			       boost::bind(&Session::handle_read, this,
					   shared_from_this(),
					   boost::asio::placeholders::error,
					   boost::asio::placeholders::bytes_transferred));
}

void Session::handle_read(std::shared_ptr<Session> &s, const boost::system::error_code &err, size_t bytes_transferred)
{
	if (!err) {
		socket.async_read_some(boost::asio::buffer(data, max_length),
				       boost::bind(&Session::handle_read, this,
						   shared_from_this(),
						   boost::asio::placeholders::error,
						   boost::asio::placeholders::bytes_transferred));
	} else {
		std::clog << "error: " << err.message() << std::endl;
	}
}
