/*
** EPITECH PROJECT, 2021
** CPP_babel_2018
** File description:
** Created by asianpw,
*/

#ifndef BABEL_ICOMPRESSOR_H
#define BABEL_ICOMPRESSOR_H

#include "DecodedSound.hpp"
#include "EncodedSound.hpp"

namespace Babel {

	class ICompressor {
	public:
		virtual ~ICompressor() = default;
		virtual EncodedSound encodeSound(const DecodedSound &decodedSound) = 0;
		virtual DecodedSound decodeSound(const EncodedSound &soundEncode) = 0;
	};
} // namespace Babel
#endif
