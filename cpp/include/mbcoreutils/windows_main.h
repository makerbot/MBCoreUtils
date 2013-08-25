/*
 * windows_main.h
 *
 * Copyright Makerbot 2013
 *
 * Contains an implementation of the windows WinMain function that wraps
 * around the standard main() function and passes it the correct things.
 */

#ifndef WINDOWS_MAIN_H_
#define WINDOWS_MAIN_H_

#include <windows.h>

int main(int argc, char **argv);

int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE,
                    PWSTR pCmdLine,
                    int nCmdShow) {
  main(__argc, __argv);
}

#endif  // WINDOWS_MAIN_H_