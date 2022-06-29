# Introduction

This project provides a C++ **tiny parser for INI files**. If you don't know what INI files are, please check this [wikipedia entry]().

The goal of this project is to provide a parser that detects basic syntax erros and provide a basic API to retrieve information stored in INI format.

# Important Concepts

<!-- + Define what is section and what is a field (property). -->
The basic components in the INI format is the **sections** and **properties**.
Usually a _property_ is defined under a _section_, but global properties (i.e. properties with no parent section) are also supported.


# The PRI API

## Supported format

+ By default names of section and properties are **case insensitive** but this can be changed when declaring the parser.

+ The API accepts global properties, i.e. properties with no parent section). These are stored under the `ROOT` section. Subsections are not supported.

+ Comments: is indicated with the `;` anywhere on a line after a space (inline comment) or at the beginning of a line (full line comment).
```ini
; This is a full line comment
value = 3  ; this is a inline comment
```

+ Explain that the **names** of sections and properties must be made of a single word (no spaces allowed).

+ Property values may be quoted or not.

+ At this moment, no escape character sequence is supported.

+ In a give section, the property names must be unique. The second occurrence of a duplicate property overrides the first occurrance, thus discarding its initial content.

## interface

### Syntax errors

+ Can't open input file.
+ Property defined but no value assigned to.
+ Something wrong in a property declaration.
+ Invalid property name (more than one word).
+ The requested property-value could not be found in this section.
+ The requested section does not exist.
+ Invalid integer value.
+ Invalid real value.
+ Invalid boolean value.

## Code example

# How to  add this to your project


