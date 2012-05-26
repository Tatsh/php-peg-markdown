# Installation

## Gentoo

You can get it for Gentoo very easily for all your `PHP_TARGETS` (5.3 and 5.4) simply by using my overlay.

https://github.com/tatsh/tatsh-overlay

Once you have the overlay installed, simply `emerge dev-php/markdown`. You may need to unmask.

## Others

```bash
git clone git://github.com/tatsh/php-peg-markdown.git
cd php-peg-markdown
sh ltinit-fix-make.sh
```

From here, you can edit `php.ini` to specify the full path to the extension. Or you can place it in something like `/usr/lib/php5.3/lib/extensions/no-debug-zts-20090626`, but this is not recommended. Consult your distribution/OS documentation on the best way to install an extension.

# Usage

Simple. Two functions and a few constants:

```
string markdown_parse(string $input [, int $flags = NULL, int $output_format = NULL])
```

string `$input` - The input Markdown string

int `$flags` - Flags that can affect the output. Multiple flags can be specified using the `|` operator.

* `MARKDOWN_EXT_SMART`: Enable smart quotes, dashes, and ellipses
* `MARKDOWN_EXT_NOTES`: Enable footnote syntax like Pandoc or PHP Markdown Extra
* `MARKDOWN_EXT_FILTER_HTML`: Filter out any HTML other than HTML blocks (except for styles)
* `MARKDOWN_EXT_FILTER_STYLES`: Filter out CSS styles in HTML

int `$output_format`: Change the output format to someting else besides HTML

* `MARKDOWN_OUTPUT_FORMAT_HTML`: The default output format
* `MARKDOWN_OUTPUT_FORMAT_LATEX`: Output in LaTeX format
* `MARKDOWN_OUTPUT_FORMAT_GROFF`: Output Groff format (usable with `nroff`)
* `MARKDOWN_OUTPUT_FORMAT_ODF`: Output OpenDocument format (openable with most current editors, notably OpenOffice, LibreOffice, and Microsoft Word 2007 and above)

```
string markdown_parse_file(string $filename [, int $flags = NULL, int $output_format = NULL])
```

This is the same as the above function but the first argument is a file name.

# Motivations

Like [JSON](http://php.net/manual/en/function.json-decode.php) and [YAML](http://www.php.net/manual/en/function.yaml-parse.php), I think Markdown should be parsed using native C to get a speed boost and to keep things modular.

## PHP Markdown comparison

* [PHP Markdown](http://michelf.com/projects/php-markdown/) is based on John Gruber's Perl Markdown parser (which is slow) (by comparison, this extension is about 9-10x faster)
* PHP Markdown is [GPL only](http://michelf.com/projects/php-markdown/license/) (which is silly for a library)
* PHP Markdown uses a series of regular expressions instead of a grammar definition
* PHP Markdown has PHP 4 crud (PHP 4 is long deprecated). Line 218 of `markdown.php`:

```php
<?php
	# Needed to insert a maximum bracked depth while converting to PHP.
		var $nested_brackets_depth = 6;
```

* PHP Markdown has extra WordPress and bBlog crud. Line 79 of `markdown.php`:

```php
<?php
if (isset($wp_version)) {
}
```
