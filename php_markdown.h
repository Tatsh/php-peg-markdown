#ifndef PHP_MARKDOWN_H
#define PHP_MARKDOWN_H 1

#define PHP_MARKDOWN_VERSION "1.0"
#define PHP_MARKDOWN_EXTNAME "markdown"

PHP_MINIT_FUNCTION(markdown);
PHP_MSHUTDOWN_FUNCTION(markdown);
PHP_RINIT_FUNCTION(markdown);
PHP_RSHUTDOWN_FUNCTION(markdown);
PHP_MINFO_FUNCTION(markdown);

PHP_FUNCTION(markdown_parse);
PHP_FUNCTION(markdown_parse_file);

#endif // PHP_MARKDOWN_H
