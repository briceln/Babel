/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

//#include "Server.hpp"


//int	main(int ac, char **argv)
//{
//	int	port;
//
//	if (ac != 2) {
//		std::cerr << "Usage: ./babel_server port" << std::endl;
//		std::cerr << "Port must me a number" << std::endl;
//		return (84);
//	}
//	port = atoi(argv[1]);
//	if (port <= 0) {
//		std::cerr << "Bad port value" << std::endl;
//		return (84);
//	}
//	try
//	{
//		boost::asio::io_service io_service;
//		Tcp server(io_service, port);
//		io_service.run();
//	}
//	catch (std::exception& e)
//	{
//		std::cerr << e.what() << std::endl;
//	}
//
//	return 0;
//}

#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

//thanks kalven for tips/debugging

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(boost::asio::io_service& ios)
		: socket(ios) {}

	tcp::socket& get_socket()
	{
		return socket;
	}

	void start()
	{
		socket.async_read_some(
			boost::asio::buffer(data, max_length),
			boost::bind(&Session::handle_read, this,
				    shared_from_this(),
				    boost::asio::placeholders::error,
				    boost::asio::placeholders::bytes_transferred));
	}

	void handle_read(std::shared_ptr<Session>& s, const boost::system::error_code& err, size_t bytes_transferred)
	{
		if (!err) {
			std::cout << "recv: " << data << std::endl;
			socket.async_read_some(boost::asio::buffer(data, max_length), boost::bind(&Session::handle_read, this, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		} else {
			std::cerr << "err (recv): " << err.message() << std::endl;
		}
	}

private:
	tcp::socket socket;
	enum { max_length = 1024 };
	char data[max_length];
};

class Server {
public:
	Server(boost::asio::io_service& ios,
		short port) : ios(ios), acceptor(ios, tcp::endpoint(tcp::v4(), port))
	{
		std::shared_ptr<Session> session = std::make_shared<Session>(ios);
		acceptor.async_accept(session->get_socket(),
				      boost::bind(&Server::handle_accept, this,
						  session,
						  boost::asio::placeholders::error));
	}

	void handle_accept(std::shared_ptr<Session> session,
		const boost::system::error_code& err)
	{
		if (!err) {
			session->start();
			session = std::make_shared<Session>(ios);
			acceptor.async_accept(session->get_socket(),
					      boost::bind(&Server::handle_accept, this, session,
							  boost::asio::placeholders::error));
		}
		else {
			std::cerr << "err: " + err.message() << std::endl;
			session.reset();
		}
	}
private:
	boost::asio::io_service& ios;
	tcp::acceptor acceptor;
};

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
