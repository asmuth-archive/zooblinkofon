ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = foreign

AM_CXXFLAGS = \
    -std=c++14 \
    -ftemplate-depth=500 \
    -mno-omit-leaf-frame-pointer \
    -fno-omit-frame-pointer \
    -g \
    -Wall \
    -Wextra \
    -Wno-unused-parameter \
    -Wno-sign-compare \
    -Wdelete-non-virtual-dtor \
    -Wno-predefined-identifier-outside-function \
    -Wno-invalid-offsetof \
    -DFNORDMETRIC_VERSION=\"v@PACKAGE_VERSION@\" \
    $(PTHREAD_CFLAGS) \
    -I$(abs_top_srcdir)/src \
    -I$(abs_top_srcdir)/

bin_PROGRAMS = zbf-firmware

zbf_firmware_SOURCES = \
    audio.h \
    audio.cc \
    input.h \
    input.cc \
    firmware.cc

zbf_firmware_LDADD = -lSDL -lSDL_mixer -lncurses

