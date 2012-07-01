#!/bin/sh

rm -fR markdown-1.0 markdown-1.0.tar.bz2
mkdir markdown-1.0
for i in config.m4 config.w32 ltinit-fix-make.sh php_markdown.c php_markdown.h;
	do cp "$i" markdown-1.0/
done

tar cjvf markdown-1.0.tar.bz2 markdown-1.0
rm -R markdown-1.0
