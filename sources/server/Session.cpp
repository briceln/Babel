/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#include <boost/bind.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "includes/server/Session.hpp"

Session::Session(boost::asio::io_service &ios, std::list<Client> &clients, std::list<std::string> &msg) : socket(ios), participants_list(clients), msg_list(msg)
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

std::string Session::check_code(std::string data)
{
	std::vector<std::string>	tokens;
	int				code;
	std::string			user;
	std::string			ip;
	std::list<Client>::iterator	it1;
	std::list<std::string>::iterator	it2;
	bool				find = false;

	ip = socket.remote_endpoint().address().to_string();
	if (data.empty()) {
		return "0\n";
	}
	boost::algorithm::split(tokens, data, boost::is_any_of("|"));
	code = std::stoi(tokens[0]);
	user = tokens[1].erase(tokens[1].length()-1);
	if (code == 0) {
		Client new_client(ip, user, true);
		participants_list.emplace_back(new_client);
		return ("200\n");
	}
	else if (code == 1) {
		Client	current_client(ip, user, false);
		for (it1 = participants_list.begin(); it1 != participants_list.end(); it1++) {
			if ((*it1).getIp() == current_client.getIp() &&
				(*it1).getUsername() ==
					current_client.getUsername()) {
				std::cout << user << " leaved the server"
					<< std::endl;
				it1 = participants_list.erase(it1);
			}
		}
	}
	else if (code == 2) {
		for (it1 = participants_list.begin(); it1 != participants_list.end(); it1++) {
			if ((*it1).getUsername() == user) {
				find = true;
				std::string returnMsg ="500|" + (*it1).getIp() +"\n";
				std::string msg = (*it1).getIp() + "|" + "500|" + ip;
				msg_list.push_back(msg);
				return returnMsg;
			}
		}
		if (!find) {
			std::string msg = "404\n";
			return msg;
		}
	}
	else if (code == 3) {
		std::string msg;
		msg = "300";
		for (it1 = participants_list.begin(); it1 != participants_list.end(); it1++) {
			msg += "|";
			msg += (*it1).getIp() + ":" + (*it1).getUsername();
		}
		msg += "\n";
		return msg;
	}
	else if (code == 5) {
		for (it2 = msg_list.begin(); it2 != msg_list.end(); it2++) {
			boost::algorithm::split(tokens, (*it2), boost::is_any_of("|"));
			std::string delivery = tokens[1] + "|" + tokens[2] + "\n";
			if (tokens[0] == ip) {
				find = true;
				it2 = msg_list.erase(it2);
				return delivery;
			}
		}
		if (!find)
		{
			std::string msg = "0\n";
			return msg;
		}
	}
	return "0\n";
}

void Session::handle_read(std::shared_ptr<Session> &s, const boost::system::error_code &err, size_t bytes_transferred)
{
	std::string msg;

	if (!err) {
		std::cout << socket.remote_endpoint().address().to_string() <<std::endl;
		socket.async_read_some(boost::asio::buffer(data, max_length),
				       boost::bind(&Session::handle_read, this,
						   shared_from_this(),
						   boost::asio::placeholders::error,
						   boost::asio::placeholders::bytes_transferred));
		msg = check_code(data);
		socket.async_write_some(boost::asio::buffer(msg, max_length),
			boost::bind(&Session::handle_write, this,
				shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		memset(data, 0, sizeof data);
	} else {
		std::clog << "error: " << err.message() << std::endl;
	}
	(void)bytes_transferred;
	(void)s;
}

void	Session::handle_write(std::shared_ptr<Session> &s,
	const boost::system::error_code &err, size_t bytes_transferred
)
{
	(void)s;
	(void)err;
	(void)bytes_transferred;
}
