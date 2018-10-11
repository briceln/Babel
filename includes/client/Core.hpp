/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#ifndef CPP_BABEL_2018_CORE_HPP
#define CPP_BABEL_2018_CORE_HPP

#include <QtWidgets/QStackedWidget>
#include "includes/client/Network/TCPNetwork.hpp"
#include "includes/client/UI/Login.hpp"
#include "includes/client/UI/Home.hpp"
#include "includes/client/UI/Call.hpp"
#include "includes/client/Settings.hpp"

class Core : public QMainWindow {
Q_OBJECT
public:
	Core(Settings const &settings);
	~Core();

public slots:
	void checkForCall(int);

private:
	QStackedWidget   *_stackedWidget;
	Babel::UI::Login *_loginScreen;
	Babel::UI::Home  *_homeScreen;
	Babel::UI::Call  *_callScreen;
	TCPNetwork       *_tcpNetwork;
};

#endif //CPP_BABEL_2018_CORE_HPP
