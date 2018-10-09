/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#ifndef BABEL_IAUDIO_H
#define BABEL_IAUDIO_H

#include "DecodedSound.hpp"

namespace Babel {

	class IAudio {
	public:
		virtual ~IAudio() = default;
		virtual bool start() = 0;
		virtual bool stop() = 0;
		virtual Babel::DecodedSound getSound() const = 0;
		virtual void setSound(const DecodedSound &sound) = 0;
	};
} // namespace Babel
#endif
