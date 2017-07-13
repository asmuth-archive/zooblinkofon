#include <array>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include "input.h"
#include "display.h"

namespace zooblinkofon {

VirtualInputDevice::VirtualInputDevice() {
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

void VirtualInputDevice::pollInputs(std::list<InputEvent>* events) {
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

static const size_t kGPIORegisterOffset = 0x20200000;
static const size_t kGPIORegisterSize = 4096;
static const std::array<uint8_t, DisplayState::kButtonCount> kGPIOButtonMap = {
  2, 3, 4, 7, 9, 10, 11, 17, 22, 27
};

HardwareInputDevice::HardwareInputDevice() : gpio_(nullptr) {
  {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
      std::cerr << "ERROR: can't open /dev/mem: " << ::strerror(errno) << std::endl;
      exit(1);
    }

     /* mmap GPIO */
     gpio_ = mmap(
          NULL,
          kGPIORegisterSize,
          PROT_READ | PROT_WRITE,
          MAP_SHARED,
          fd,
          kGPIORegisterOffset);

     close(fd);
  }

  if (gpio_ == MAP_FAILED) {
    std::cerr << "ERROR: can't open mmap() gpio register" << std::endl;
    exit(1);
  }
}

HardwareInputDevice::~HardwareInputDevice() {
  if (gpio_) {
    munmap((void*) gpio_, kGPIORegisterSize);
  }
}

void HardwareInputDevice::pollInputs(std::list<InputEvent>* events) {
  auto gpio_reg = *((uint32_t*) gpio_ + 13);

  for (size_t i = 0; i < DisplayState::kButtonCount; ++i) {
    if ((gpio_reg & (1 << kGPIOButtonMap[i])) == 0) {
      std::cerr << "press: " << i << std::endl;
    }
  }
}

} // namespace zooblinkofon


