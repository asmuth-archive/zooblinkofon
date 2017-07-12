#include <termios.h>
#include <unistd.h>
#include <iostream>
#include "input.h"

namespace zooblinkofon {

InputHandler::InputHandler() {
  {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    t.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
  }
}

bool stdin_pending() {
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &fds);
}

void InputHandler::pollInputs(std::list<InputEvent>* events) {
  // read key presses fron stdin
  while (stdin_pending()) {
    InputButton btn;
    switch (fgetc(stdin)) {
      case '1':
        btn = InputButton::BTN0;
        break;
      case '2':
        btn = InputButton::BTN1;
        break;
      case '3':
        btn = InputButton::BTN2;
        break;
      case '4':
        btn = InputButton::BTN3;
        break;
      case '5':
        btn = InputButton::BTN4;
        break;
      case '6':
        btn = InputButton::BTN5;
        break;
      case '7':
        btn = InputButton::BTN6;
        break;
      case '8':
        btn = InputButton::BTN7;
        break;
      case '9':
        btn = InputButton::BTN8;
        break;
      case '0':
        btn = InputButton::BTN9;
        break;
      case 'q':
        btn = InputButton::QUIT;
        break;
      default:
        continue;
    }

    {
      InputEvent ev;
      ev.action = InputAction::KEYDOWN;
      ev.button = btn;
      events->emplace_back(ev);
    }

    {
      InputEvent ev;
      ev.action = InputAction::KEYUP;
      ev.button = btn;
      events->emplace_back(ev);
    }
  }
}

} // namespace zooblinkofon


