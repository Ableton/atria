# Atria

C++ amazing templates and reusable implementations awesomeness.
Extends core language and standard library capabilities and provide
mostly header-only libraries in the spirit of the STL, Boost, Adobe
Source Libraries or Facebook's Folly and Fatal.

For now, the library is C++11 compatible, but will try to move to
C++14 and upper as compilers catch up.

While not yet, we plan to release this library as **open source**.

## Modules

* `atria::variant` provides tools for better usability of

* `atria::meta` provides several metaprogramming tools, including some
  Booost.MPL adaptors and concept checking facilities.

* `atria::estd` provides C++11 compatible implementations of some
  C++14 and beyond standard library components.

* `atria::xform` provides an efficient C++ implementation of
  transducers, a concept introduced in [Clojure by Rich
  Hickie](http://blog.cognitect.com/blog/2014/8/6/transducers-are-coming)

* `atria::funken` provides a *experimental* library for writing epocal
  and functional data-models.

* `atria::testing` provides testing tools like spies for modern C++
  development.

## Requires

Ableton repositories:

  - [build-system](https://github.com/AbletonAppDev/build-system)
  - [boost-stripped](https://github.com/AbletonAppDev/boost-stripped)

3rd party dependencies:

  - googletest (can be found here: https://chromium.googlesource.com/external/googletest)

## Maintainers

  - Juan Pedro Bolívar Puente (jbo-ableton)
  - Brent Shields (brs-ableton)
  - Tobias Hahn (toh-ableton)
