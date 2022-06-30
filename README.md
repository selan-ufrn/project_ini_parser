# Introduction

This project provides a C++ **tiny parser for INI files**. If you don't know what INI files are, please check this [wikipedia entry](https://en.wikipedia.org/wiki/INI_file).

The goal of this project is to provide a parser that detects basic syntax erros and provide a basic API to retrieve information from a INI file.

# Important Concepts

<!-- + Define what is section and what is a field (property). -->
The basic components in the INI format are the **sections** and **properties**.
Usually a _property_ is defined under a _section_, but global properties (i.e. properties with no parent section) are also supported.


# The PRI API

The motivation behind this project is to design an API with just a few methods to open and read data from an INI file. This API does not write data to an INI file and only detect basic syntax errors in the INI format (described later in this document).

## Supported format

By default names of section and properties are **case insensitive** but this can be changed when declaring the parser.
Usually after a section declaration comes a list of properties and their values, one per line.
The example below shows a basic INI file.

```ini
; This is a basic INI file.

color = #FF32EE        ; This is a global property

[protocol]             ; Protocol section
version=6              ; IPv6
ip =  177.20.150.132   ; IP address
type = "tcp"

[user]
name= "Bob Smith  "    ; Spaces around '=' and character '"' are stripped
email = bob@smith.com  ; And comments (like this) are ignored
active = true          ; Defining a boolean

[constants]
pi = 3.14159           ; Test a floating point number
pos = 2,5              ; The comma and 5 are discarded
```

The API accepts global properties, i.e. properties with no parent section. These are stored under the `ROOT` section. Subsections are not supported. In the example above, `color` is a global property.
The property values may be quoted (see `type` property above) or not ( see `email` property abov).All quotation are remove before getting stored in the database.

Comments are placed after the `;` anywhere on a line after a space (inline comment) or at the beginning of a line (full line comment).

The property and section **names** must be made of a single word (no spaces between words allowed).
```ini
this wont work = true  ; This line will trigger a syntax error
```

In a give section, the property names must be unique. The second occurrence of a duplicate property overrides the first occurrance, thus discarding its initial content.

At this moment, no escape character sequence is supported.

## Interface and code example

For a list the API methods and how to use them, please refer to this [example](example/example.cpp) or the [oficial documentation](docs/index.html).

### Syntax errors

** TODO: explain the situations that cause these messages.**

+ Can't open input file.
+ Property defined but no value assigned to.
+ Something wrong in a property declaration.
+ Invalid property name (more than one word).
+ The requested property-value could not be found in this section.
+ The requested section does not exist.
+ Invalid integer value.
+ Invalid real value.
+ Invalid boolean value.

# How to  add this to your project

You have, at least, two ways to add `TIP` to your project, described here: (1) xxxx, and (2) yyy.

To add `TIP` to your project just add the source file and header to your folder's project and include them in your project as you would with any ther source/header file.
Please, refer to this [cmake file](CMakeLists.txt) to see an example of how to define `TIP` as a library your project will be linked to.

If you want a system wide installation create the Makefiles with the following `cmake` command
```bash
make -G "Unix Makefiles" . -B build -D CMAKE_INSTALL_PREFIX=/where-to-install
```
where `where-to-install` is the location where you wish the installation will be written to (usually `/usr` or `/opt`).

Then start the compilation, which will create a test program and generate the static library
```bash
cmake --build build
```

Optionally, you may run the installation process, which will copy the library to the `lib` folder, and the header to `include` folder, both under the ${CMAKE_INSTALL_PREFIX}.

The installation also also export a `pkg-config` file. This file allows a third-party application to easily import your library.
```bash
cd build
make install
```
