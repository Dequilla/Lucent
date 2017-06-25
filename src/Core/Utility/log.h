/**
* \file log.h
* \brief Tools to make logging easier and more unified
*
* Currently only very simple and logs to the console only.
*/
#pragma once

#include <string>
#include <iostream>
#include <iomanip>

#include "Core/Utility/console.h"

namespace ce { namespace core {

	/**
	* \brief Enum with the types of logging you can make
	*/
	enum LogType
	{
		LOG_MESSAGE,	/**< A message, in the console it has grey text */
		LOG_WARNING,	/**< A warning, in the console it has yellow text */
		LOG_ERROR,		/**< An error, in the console it has red text */
		LOG_CRITICAL	/**< A critical error, in the console it has red text with yellow background */
	};

	/**
	* \brief Log a text message to the console
	*
	* @param output The output string/message
	* @param type The type of message this is, check LogType
	*/
	inline void log(const std::string& output, const LogType& type = LOG_MESSAGE)
	{
		std::string begin;
		ConsoleColor fColor;
		ConsoleColor bColor;

		switch (type)
		{
		case LOG_MESSAGE:
			begin = "CE | MESSAGE: ";
			fColor = CONSOLE_GREY;
			bColor = CONSOLE_BLACK;
			break;
		case LOG_WARNING:
			begin = "CE | WARNING: ";
			fColor = CONSOLE_YELLOW;
			bColor = CONSOLE_BLACK;
			break;
		case LOG_ERROR:
			begin = "CE | ERROR: ";
			fColor = CONSOLE_RED;
			bColor = CONSOLE_BLACK;
			break;
		case LOG_CRITICAL:
			begin = "CE | CRITICAL-ERROR: ";
			fColor = CONSOLE_RED;
			bColor = CONSOLE_YELLOW;
			break;
		default:
			begin = "CE | MESSAGE: ";
			fColor = CONSOLE_GREY;
			bColor = CONSOLE_BLACK;
			break;
		}

		std::string result = begin + output;
		printWithColors(result, fColor, bColor);
	}

}} // Namespace end