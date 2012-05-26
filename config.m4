PHP_ARG_ENABLE(markdown, whether to enable Markdown parsing support,
[ --enable-markdown   Enable Markdown parsing support])
if test "$PHP_MARKDOWN" = "yes"; then
  AC_DEFINE(HAVE_MARKDOWN, 1, [Whether you have Markdown support])
  PHP_NEW_EXTENSION(markdown, php_markdown.c, $ext_shared)
fi 
