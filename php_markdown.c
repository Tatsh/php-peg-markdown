#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_markdown.h"

#include "markdown_lib.h"

static function_entry markdown_functions[] = {
  PHP_FE(markdown_parse, NULL);
  {NULL, NULL, NULL}
};

zend_module_entry markdown_modulE_entry = {
#if ZEND_MODULE_API_NO >= 20010901
  STANDARD_MODULE_HEADER,
#endif
  PHP_MARKDOWN_EXTNAME,
  markdown_functions,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
#if ZEND_MODULE_API_NO >= 20010901
  PHP_HELLO_WORLD_VERSION,
#endif
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MARKDOWN
ZEND_GET_MODULE(markdown)
#endif

PHP_FUNCTION(markdown_parse) {
  char *input;
  int input_len;
  int flags;
  int output_format;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", &input, &input_len, &flags, &output_format) == FAILURE) {
    RETURN_NULL();
  }

  if (!flags) {
    RETURN_STRING(markdown_to_string(input));
  }

  if (!output_format) {
    RETURN_STRING(markdown_to_string(input, flags));
  }

  RETURN_STRING(markdown_to_string(input, flags, output_format));
}
