PHP_ARG_ENABLE(markdown, whether to enable Markdown parsing support,
[  --enable-markdown       Enable Markdown parsing support])
if test "$PHP_MARKDOWN" = "yes"; then
  AC_DEFINE(HAVE_MARKDOWN, 1, [Whether you have Markdown support])

  PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.32.3])
  PHP_EVAL_LIBLINE("$GLIB_LIBS")
  PHP_EVAL_INCLINE("$GLIB_CFLAGS")
  
  PEG_MARKDOWN_SOURCES="peg-markdown/markdown_lib.c peg-markdown/markdown_output.c peg-markdown/markdown_parser.c"

  PHP_NEW_EXTENSION(markdown, $PEG_MARKDOWN_SOURCES php_markdown.c, $ext_shared)
fi
