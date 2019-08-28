# gio-qt: Qt wrapper library of Gio

## Description

This is a Qt wrapper library for Gio (or say it's a glib/glibmm wrapper mainly focused on [GIO](https://gitlab.gnome.org/GNOME/glibmm/tree/master/gio) module). This library is designed to be exception-free and avoid Qt application developer do direct access to glib/glibmm (so they can use Gio in a more Qt way).

## Build
#
### Build depts:

 - cmake `>= 3.12.4`
 - pkg-config (to find and use giomm module)
 - Qt5Core `>= 5.6.3`
 - Qt5Test (if you would like to build tests)
 - giomm-2.4
 - doxygen (to build documentations)

If you are using an older system which are using a lower cmake version and attempt to build this library, please turn off the `BUILD_DOCS` option.

### Build manually

``` shell
$ cd /path/to/your/source/code
$ mkdir build
$ cd build
$ cmake ../
$ make
$ sudo make install
```

It will installed to `/usr/local/lib` by default. You may also need to do a `sudo ldconfig /usr/local/lib` after install.

## Questions and Answers

### Should I use?

<!-- TODO: Update README after 1.0.0 released -->

Before this library release it's first stable tag (1.0.0) the answer is mostly **no** since the API may change at any time, and since this library is mainly for Deepin product for now so only the APIs we need will be implemented at first.

If you are writing a non-Qt application, please consider using [glibmm](https://gitlab.gnome.org/GNOME/glibmm). If you are writing Qt application and really wanna use this library, consider wait its API stable release or create a fork and start hacking!

### What about generate Qt binding using GObject Introspection

As you can see `gio-qt` currently is a hand-crafted Qt/C++ bindings for GIO. Using [GObject Introspection (gir)](https://wiki.gnome.org/Projects/GObjectIntrospection) to generate code could be a really good idea but we currently doesn't have very enough time to look into it.

It's definitely worth to look into `gir` to generate Qt binding and actually there was some cool guys working on this idea (see [GObject Consume](https://wiki.gnome.org/action/show/Projects/GObjectIntrospection/GObjectConsume)) and worth to check it out. Due to the project time limit so we are not going to use it currently, but we encourage you contirbute on that project if you are familiar to `gir`.

## Documentation

For Deepin there will be a `libgio-qt-doc` package, if you are building it manually with `BUILD_DOCS` option enabled, there will be a docs folder inside your build folder, and there will be a doxygen generated html folder and also a `gio-qt.qch` for QtCreator.

## License

GPLv3
