/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#include <iostream>
#include "includes/client/Core.hpp"

Core::Core(Settings const &settings) :
	_tcpNetwork(new TCPNetwork(QString::fromStdString(settings.getIp()), std::stoi(settings.getPort())))
{
	if (!settings.isContinue())
		throw std::invalid_argument("");
	_stackedWidget = new QStackedWidget();
	_loginScreen   = new Login(_stackedWidget, _tcpNetwork.get());
	_homeScreen    = new Home(_stackedWidget, _tcpNetwork.get());
	_callScreen    = new Call(_stackedWidget);
	_stackedWidget->addWidget(_loginScreen);
	_stackedWidget->addWidget(_homeScreen);
	_stackedWidget->addWidget(_callScreen);
	_stackedWidget->show();
	QObject::connect(_stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(checkForCall(int)));
}

void Core::checkForCall(int index)
{
	if (index == _stackedWidget->indexOf(_callScreen)) {
		_callScreen->makeCall(_homeScreen->getIp(), _homeScreen->getName());
	} else if (index == _stackedWidget->indexOf(_homeScreen)) {
		_homeScreen->setUsername(_loginScreen->getUsername());
		_tcpNetwork->writeData("3|user");
	}
}

Core::~Core()
{
	if (!_homeScreen->getUsername().toStdString().empty())
		_tcpNetwork->writeData("1|" + _homeScreen->getUsername().toStdString());
}
