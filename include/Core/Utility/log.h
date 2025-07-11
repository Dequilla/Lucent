/**
 * \file log.h
 * \brief Tools to make logging easier and more unified
 *
 * Currently only very simple and logs to the console only.
 */
#pragma once

#include <iomanip>
#include <iostream>
#include <string>

#include "Core/Utility/console.h"

/**
 * \macro Creates a c-style string of x
 */
#define LU_STR(x) #x

/**
 * \macro Creates a c-style string of x
 */
#define LU_TOSTRING(x) LU_STR(x)

/**
 * \macro Creates a c-style string with the location and line you currently at
 */
#define LU_C_AT __FILE__ ":" LU_TOSTRING(__LINE__)

/**
 * \macro Creates a C++ style string with the location and line you currently at
 */
#define LU_AT std::string(LU_C_AT)

namespace lu
{
    namespace core
    {

        /**
         * \brief Enum with the types of logging you can make
         */
        enum LogType
        {
            LOG_MESSAGE, /**< A message, in the console it has grey text */
            LOG_WARNING, /**< A warning, in the console it has yellow text */
            LOG_ERROR,   /**< An error, in the console it has red text */
            LOG_CRITICAL /**< A critical error, in the console it has red text
                            with yellow background */
        };

        /**
         * \brief Log a text message to the console
         *
         * @param output The output string/message
         * @param type The type of message this is, check LogType
         */
        inline void log(const std::string &output,
                        const LogType &type = LOG_MESSAGE)
        {
            std::string begin;
            ConsoleColor fColor;
            ConsoleColor bColor;

            switch (type)
            {
                case LOG_MESSAGE:
                    begin = "LU | MESSAGE: ";
                    fColor = CONSOLE_GREY;
                    bColor = CONSOLE_BLACK;
                    break;
                case LOG_WARNING:
                    begin = "LU | WARNING: ";
                    fColor = CONSOLE_YELLOW;
                    bColor = CONSOLE_BLACK;
                    break;
                case LOG_ERROR:
                    begin = "LU | ERROR: ";
                    fColor = CONSOLE_RED;
                    bColor = CONSOLE_BLACK;
                    break;
                case LOG_CRITICAL:
                    begin = "LU | CRITICAL-ERROR: ";
                    fColor = CONSOLE_RED;
                    bColor = CONSOLE_YELLOW;
                    break;
                default:
                    begin = "LU | MESSAGE: ";
                    fColor = CONSOLE_GREY;
                    bColor = CONSOLE_BLACK;
                    break;
            }

            std::string result = begin + output;
            printWithColors(result, fColor, bColor);
        }

        /**
         * \brief Log a text message to the console
         *
         * @param extra_info Extra output which is given it's own line
         * @param output The output string/message
         * @param type The type of message this is, check LogType
         */
        inline void log(const std::string &extra_info,
                        const std::string &output,
                        const LogType &type = LOG_MESSAGE)
        {
            lu::core::log(output + "\n   '--> " + extra_info, type);
        }

    }
} // Namespace end