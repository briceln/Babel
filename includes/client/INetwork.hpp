/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#ifndef BABEL_INETWORK_H
#define BABEL_INETWORK_H

namespace Babel {

	//This is an interface for Network Plugin
	class INetwork {
	public:
		virtual        ~INetwork() = default;
		virtual bool initConnection() = 0;
		virtual void sendData() = 0;
	};
} // namespace Babel
#endif
