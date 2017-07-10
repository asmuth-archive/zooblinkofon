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
    size_t btn;
    switch (fgetc(stdin)) {
      case '1':
        btn = 0;
        break;
      case '2':
        btn = 1;
        break;
      case '3':
        btn = 2;
        break;
      case '4':
        btn = 3;
        break;
      case '5':
        btn = 4;
        break;
      case '6':
        btn = 5;
        break;
      case '7':
        btn = 6;
        break;
      case '8':
        btn = 7;
        break;
      case '9':
        btn = 8;
        break;
      case '0':
        btn = 9;
        break;
      default:
        continue;
    }

    {
      InputEvent ev;
      ev.type = InputEventType::KEYDOWN;
      ev.button = btn;
      events->emplace_back(ev);
    }

    {
      InputEvent ev;
      ev.type = InputEventType::KEYUP;
      ev.button = btn;
      events->emplace_back(ev);
    }
  }
}

} // namespace zooblinkofon


