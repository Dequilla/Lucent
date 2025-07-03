/**
 * \file console.h
 *
 * \brief File containing some functions to handle the console
 */

#pragma once

#include <iostream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace lu
{
    namespace core
    {

        /**
         * \brief The supported colors for console output
         */
        enum ConsoleColor
        {
            CONSOLE_RESET,   /**< Used to reset to the standard colors of the
                                console */
            CONSOLE_BLUE,    /**< Console color blue */
            CONSOLE_CYAN,    /**< Console color cyan */
            CONSOLE_RED,     /**< Console color red */
            CONSOLE_MAGENTA, /**< Console color magenta */
            CONSOLE_GREEN,   /**< Console color green */
            CONSOLE_YELLOW,  /**< Console color yellow */
            CONSOLE_BLACK,   /**< Console color black */
            CONSOLE_GREY,    /**< Console color grey (white on linux) */
            CONSOLE_WHITE    /**< Console color white */
        };

#ifdef _WIN32
        // TODO: Find way to force doxygen to document these functions aswell
        inline void changeConsoleColor(ConsoleColor foreground,
                                       ConsoleColor background = CONSOLE_BLACK)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            WORD color;
            switch (foreground)
            {
                case CONSOLE_BLUE:
                    color = 9;
                    break;
                case CONSOLE_GREEN:
                    color = 10;
                    break;
                case CONSOLE_CYAN:
                    color = 11;
                    break;
                case CONSOLE_RED:
                    color = 12;
                    break;
                case CONSOLE_MAGENTA:
                    color = 13;
                    break;
                case CONSOLE_YELLOW:
                    color = 14;
                    break;
                case CONSOLE_WHITE:
                    color = 15;
                    break;
                case CONSOLE_GREY:
                    color = 8;
                    break;
                case CONSOLE_BLACK:
                    color = 0;
                    break;
                case CONSOLE_RESET:
                    color = 15;
                    break;
                default:
                    color = 15;
                    break;
            }

            switch (background)
            {
                case CONSOLE_BLUE:
                    color += 16 * 9;
                    break;
                case CONSOLE_GREEN:
                    color += 16 * 10;
                    break;
                case CONSOLE_CYAN:
                    color += 16 * 11;
                    break;
                case CONSOLE_RED:
                    color += 16 * 12;
                    break;
                case CONSOLE_MAGENTA:
                    color += 16 * 13;
                    break;
                case CONSOLE_YELLOW:
                    color += 16 * 14;
                    break;
                case CONSOLE_WHITE:
                    color += 16 * 15;
                    break;
                case CONSOLE_GREY:
                    color += 16 * 7;
                    break;
                case CONSOLE_BLACK:
                    color += 16 * 0;
                    break;
                case CONSOLE_RESET:
                    color += 16 * 0;
                    break;
                default:
                    color += 16 * 0;
            }

            SetConsoleTextAttribute(hConsole, color);
        }
#endif

#ifdef __linux__
        // TODO: Find way to force doxygen to document these functions aswell
        inline void changeConsoleColor(ConsoleColor foreground,
                                       ConsoleColor background)
        {
            std::string fColor = "";
            std::string bColor = "";

            switch (foreground)
            {
                case CONSOLE_BLUE:
                    fColor = "34";
                    break;
                case CONSOLE_GREEN:
                    fColor = "32";
                    break;
                case CONSOLE_CYAN:
                    fColor = "36";
                    break;
                case CONSOLE_RED:
                    fColor = "31";
                    break;
                case CONSOLE_MAGENTA:
                    fColor = "35";
                    break;
                case CONSOLE_YELLOW:
                    fColor = "33";
                    break;
                case CONSOLE_WHITE:
                    fColor = "37";
                    break;
                case CONSOLE_GREY:
                    fColor = "37";
                    break;
                case CONSOLE_BLACK:
                    fColor = "30";
                    break;
                default:
                    fColor = "37";
                    break;
            }

            switch (background)
            {
                case CONSOLE_BLUE:
                    bColor = "44";
                    break;
                case CONSOLE_GREEN:
                    bColor = "42";
                    break;
                case CONSOLE_CYAN:
                    bColor = "46";
                    break;
                case CONSOLE_RED:
                    bColor = "41";
                    break;
                case CONSOLE_MAGENTA:
                    bColor = "45";
                    break;
                case CONSOLE_YELLOW:
                    bColor = "43";
                    break;
                case CONSOLE_WHITE:
                    bColor = "47";
                    break;
                case CONSOLE_GREY:
                    bColor = "47";
                    break;
                case CONSOLE_BLACK:
                    bColor = "40";
                    break;
                default:
                    bColor = "40";
                    break;
            }

            std::string out;
            if (foreground != CONSOLE_RESET && background != CONSOLE_RESET)
                out = "\033[" + fColor + ";" + bColor + "m";
            else
                out = "\033[0m"; // reset colorchange

            std::cout << out;
        }
#endif

        /**
         * \brief Prints output to the console using the colors specified
         *
         * Is not supported for all systems, tested on:
         *	- Ubuntu
         *	- Windows
         *
         * @param foreground The color of the text/foreground
         * @param background The color of the background
         */
        inline void printWithColors(std::string output,
                                    ConsoleColor foreground,
                                    ConsoleColor background = CONSOLE_BLACK)
        {
            changeConsoleColor(foreground, background);

            std::cout << output << std::endl;

            changeConsoleColor(CONSOLE_RESET,
                               CONSOLE_RESET); // reset to default otherwise the
                                               // colorchange persists
        }

    }
}
