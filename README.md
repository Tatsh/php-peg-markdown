# Installation

## Gentoo

You can get it for Gentoo very easily for all your `PHP_TARGETS` (5.3 and 5.4) simply by using my overlay.

https://github.com/tatsh/tatsh-overlay

Once you have the overlay installed, simply `emerge dev-php/markdown`. You may need to unmask a few packages.

## Others

```bash
wget http://piumarta.com/software/peg/peg-0.1.9.tar.gz
tar xvf peg-0.1.9.tar.gz
cd peg-0.1.9
make
sudo make install

git clone git://github.com/Tatsh/peg-markdown.git
make
sudo make install

git clone git://github.com/tatsh/php-peg-markdown.git
cd php-peg-markdown
sh ltinit-fix-make.sh
sudo make install
```

From here, you can edit `php.ini` to specify the full path to the extension. Or you can place it in something like `/usr/lib/php5.3/lib/extensions/no-debug-zts-20090626`, but this is not recommended. Consult your distribution/OS documentation on the best way to install an extension.

## Windows

**NOTE:** This is out of date.

Follow instructions [here](https://wiki.php.net/internals/windows/stepbystepbuild) to set up your development environment. Make sure to install the Windows SDK *before* Visual Studio, update Windows through Windows Update, then install Visual Studio and all of its updates (this means SP1 for 2008).

Just before step *13*, perform these commands (where *x* is the major version you are using):

```batch
cd C:\php-sdk\php5xdev\vc9\x86
mkdir pecl
cd pecl
git clone git://github.com/Tatsh/php-peg-markdown.git markdown
cd ..\..\php-5.x-xyz
```

When specifying your compile line, use `--enable-markdown` to enable this extension.

Before you can build you need Glib dependencies:

1. Download the Glib development package from [GTK's site](http://www.gtk.org)
2. Extract the package to C:\php-sdk\php5xdev\vc9\x86\deps

1. Download the run-time Gettext run-time package from GTK's site
2. Extract the package to C:\php-sdk\php5xdev\vc9\x86\deps

Now you can build, but you will not be able to run `nmake snap` yet.

### Creating a Snapshot/Running `php.exe`

Before you can run `nmake snap` you need to put 2 DLLs into the `C:\php-sdk\php5xdev\vc9\x86\php-5.x-xyz\Release_TS` directory:

* `intl.dll` (from gettext run-time package)
* `libglib-2.0-0.dll` (from glib package)

Both of these should be in `C:\php-sdk\php5xdev\vc9\x86\deps\bin`. `php.exe` cannot run without the above mentioned DLLs and is required to run the `phar` file which is run when a snapshot is built.

Furthermore, you still need to add the aforementioned DLLs to the resulting zip file you intend to distribute. An easy way to do this is with a GUI app like 7-Zip's manager.

This is a temporary workaround that will be fixed in a future version.

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
