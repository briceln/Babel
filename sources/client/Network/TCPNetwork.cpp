/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#include <includes/client/Network/TCPNetwork.hpp>
#include <QtWidgets/QMessageBox>
#include <iostream>
#include "includes/common/Binary.hpp"

TCPNetwork::TCPNetwork(const QString &ip, int port, int timeToWait) : _ip(ip),
	_port(port), _timeToWait(timeToWait), _socket(new QTcpSocket(this))
{
	connect(_socket, QOverload<QAbstractSocket::SocketError>::of(
		&QAbstractSocket::error), this, &TCPNetwork::displayError);
	connect(_socket, SIGNAL(readyRead()), this, SLOT(readData()));
	connect(_socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	_socket->connectToHost(_ip, (quint16)_port);
	if (!_socket->waitForConnected(_timeToWait)) {
		throw std::runtime_error("The server doesn't respond !");
	}
}

void TCPNetwork::displayError(QAbstractSocket::SocketError socketError)
{
	switch (socketError) {
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		QMessageBox::information(nullptr, tr("Skipe"),
					 tr("The host was not found. Please check the "
					    "host name and port settings."));
		break;
	case QAbstractSocket::ConnectionRefusedError:
		QMessageBox::information(nullptr, tr("Skipe"),
					 tr("The connection was refused by the server. "
					    "Make sure the skipe server is running, "
					    "and check that the host name and port "
					    "settings are correct."));
		break;
	default:
		QMessageBox::information(nullptr, tr("Skipe"),
					 tr("The following error occurred: %1.").arg(
						 _socket->errorString()));
	}
}

void TCPNetwork::readData()
{
	int	x = 0;

	QString data = _socket->readAll();
	QString data2 = QString::fromStdString(binaryToStr(data.toStdString()));
	while (data2[x] != '\0') {
		if (data2[x] == '\n')
			data2.remove(x+1, data2.size());
		x++;
	}
	qDebug() << data2;
	if (data2.toStdString() == "200\n") {
		return;
	}
	if (data2.startsWith("300|")) {
		data2.remove(0, 4);
		emit dataToRead(data2);
	}
	if (data2.startsWith("500|")) {
		data2.remove(0, 4);
		emit incomingCall(data2);
	}
	if (data2.startsWith("404\n")) {
		//other doesn't answer
	}
}

void TCPNetwork::connected()
{
}

void TCPNetwork::disconnected()
{
}

bool TCPNetwork::writeData(const std::string &msg)
{
	if (_socket->state() != QTcpSocket::ConnectedState) {
		return false;
	}
	_socket->write((msg + "\n").data());
	_socket->waitForBytesWritten();
	return true;
}
