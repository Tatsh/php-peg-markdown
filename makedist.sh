#!/bin/sh

VERSION="1.01"

rm -fR markdown-$VERSION markdown-$VERSION.tar.bz2
mkdir markdown-$VERSION
for i in config.m4 config.w32 ltinit-fix-make.sh php_markdown.c php_markdown.h;
	do cp "$i" markdown-$VERSION/
done

tar cjvf markdown-$VERSION.tar.bz2 markdown-$VERSION
rm -R markdown-$VERSION
