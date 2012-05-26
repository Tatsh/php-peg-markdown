#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_markdown.h"

#include "peg-markdown/markdown_lib.h"

const zend_function_entry markdown_functions[] = {
  PHP_FE(markdown_parse, NULL)
  PHP_FE(markdown_parse_file, NULL)
  PHP_FE_END
};

zend_module_entry markdown_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
  STANDARD_MODULE_HEADER,
#endif
  PHP_MARKDOWN_EXTNAME,
  markdown_functions,
  PHP_MINIT(markdown),
  PHP_MSHUTDOWN(markdown),
  PHP_RINIT(markdown),
  PHP_RSHUTDOWN(markdown),
  PHP_MINFO(markdown),
#if ZEND_MODULE_API_NO >= 20010901
  PHP_MARKDOWN_VERSION,
#endif
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MARKDOWN
ZEND_GET_MODULE(markdown)
#endif

PHP_MINIT_FUNCTION(markdown) {  
  REGISTER_LONG_CONSTANT("MARKDOWN_EXT_SMART", EXT_SMART, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("MARKDOWN_EXT_NOTES", EXT_NOTES, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("MARKDOWN_EXT_FILTER_HTML", EXT_FILTER_HTML, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("MARKDOWN_EXT_FILTER_STYLES", EXT_FILTER_STYLES, CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("MARKDOWN_OUTPUT_FORMAT_HTML", HTML_FORMAT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("MARKDOWN_OUTPUT_FORMAT_LATEX", LATEX_FORMAT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("MARKDOWN_OUTPUT_FORMAT_GROFF", GROFF_MM_FORMAT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("MARKDOWN_OUTPUT_FORMAT_ODF", ODF_FORMAT, CONST_CS | CONST_PERSISTENT);

  return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(markdown) {
  return SUCCESS;
}

PHP_RINIT_FUNCTION(markdown) {
  return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(markdown) {
  return SUCCESS;
}

PHP_MINFO_FUNCTION(markdown) {
  php_info_print_table_start();
  php_info_print_table_header(2, "markdown parsing", "enabled");
  php_info_print_table_end();
}

int get_valid_output_format(output_format) {
  if (output_format != HTML_FORMAT &&
      output_format != LATEX_FORMAT &&
      output_format != GROFF_MM_FORMAT &&
      output_format != ODF_FORMAT) {
    output_format = HTML_FORMAT;
  }
  return output_format;
}

/* {{{ proto string markdown_parse(string input [, int flags, int output_format ])
   Convert Markdown string to another string */
PHP_FUNCTION(markdown_parse) {
  char *input;
  int input_len;
  int flags = 0;
  int output_format = 0;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", &input, &input_len, &flags, &output_format) == FAILURE) {
    RETURN_NULL();
  }

  output_format = get_valid_output_format();

  RETURN_STRING(markdown_to_string(input, flags, output_format), 1);
}

PHP_FUNCTION(markdown_parse_file) {
  php_stream *stream;
  char *filename;
  int filename_len;
  char *contents;
  int flags = 0;
  int output_format = 0;
  int len;
  long offset = -1;
  long maxlen = PHP_STREAM_COPY_ALL;
  char *decoded;
  php_stream_context *context = NULL;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", &filename, &filename_len, &flags, &output_format) == FAILURE) {
    RETURN_NULL();
  }

  output_format = get_valid_output_format();
  stream = php_stream_open_wrapper_ex(filename, "rb", 0 | REPORT_ERRORS, NULL, NULL);

  if (!stream) {
    RETURN_FALSE;
  }

  if (offset > 0 && php_stream_seek(stream, offset, SEEK_SET) < 0) {
    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to seek position %ld in the stream", offset);
    php_stream_close(stream);
    RETURN_FALSE;
  }

  if ((len = php_stream_copy_to_mem(stream, &contents, maxlen, 0)) > 0) {
    decoded = markdown_to_string(contents, flags, output_format);
    len = strlen(decoded);
    RETVAL_STRINGL(decoded, len, 1);
  }
  else if (len == 0) {
    RETVAL_EMPTY_STRING();
  }
  else {
    RETVAL_FALSE;
  }

  php_stream_close(stream);
}
