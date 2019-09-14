Ropj
====

The goal of this package is to provide the ability to import Origin(R) OPJ
files. The only function, `read.opj(file)`, uses [liborigin] to parse the file
and build a list of its contents. No write support is planned, since it's
absent in [liborigin].

Submodules
----------

If you want to clone this repo, don't forget the `--recursive` flag. Otherwise,
use `git submodule update --init --recursive` after you cloned it.

[liborigin]: https://sourceforge.net/projects/liborigin/
