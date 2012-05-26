#!/bin/sh
make clean
phpize
aclocal
libtoolize --force
autoheader
autoconf
./configure --enable-markdown
make
