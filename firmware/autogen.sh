#!/bin/sh

# Run this script to generate the configure script and other files that will
# be included in the distribution.  These files are not checked in because they
# are automatically generated.

set -ex

autoreconf -fi -Wall,no-obsolete
sed -ix -e 's/rm -f core /rm -f /g' configure
rm configurex

rm -rf autom4te.cache config.h.in~
exit 0
