ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = foreign

AM_CXXFLAGS = \
    -std=c++14 \
    -ftemplate-depth=500 \
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

bin_PROGRAMS = zooblinkofon

zooblinkofon_SOURCES = \
    audio.h \
    audio.cc \
    display.h \
    display.cc \
    input.h \
    input.cc \
    scene.h \
    scene.cc \
    scene_farm.h \
    scene_farm.cc \
    scene_water.h \
    scene_water.cc \
    zooblinkofon.cc

zooblinkofon_LDADD = -lSDL2 -lSDL2_mixer

