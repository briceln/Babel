/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#ifndef BABEL_DECODEDSOUND_H
#define BABEL_DECODEDSOUND_H

#include <vector>

namespace Babel {
	typedef struct DecodedSound {
		std::vector<float> buffer;
		int                size = 0;
	} DecodedSound;
} // namespace Babel
#endif
