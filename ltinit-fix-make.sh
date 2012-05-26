#!/bin/sh
make clean
phpize
aclocal
libtoolize --force
autoheader
autoconf
LDFLAGS="$LDFLAGS $(pkg-config glib-2.0 --libs)" CFLAGS="$CFLAGS $(pkg-config glib-2.0 --cflags)" ./configure --enable-markdown
make
