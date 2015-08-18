# Atria

C++ amazing templates and reusable implementations awesomeness.
Extends core language and standard library capabilities and provide
mostly header-only libraries in the spirit of the STL, Boost, Adobe
Source Libraries or Facebook's Folly and Fatal.

The library is written in C++11.  In the spirit of using modern C++
techniques, we will use C++14 and newer features as compilers catch up.

While not yet, we plan to release this library as **open source**.

## Modules

* `atria::prelude` provides basic functional programming tools in the
  spirit of those in Clojure `core` and Haskell's `Prelude`.

* `atria::variant` provides tools for better usability of Boost.Variant
  and potentially other implementations of sum types.

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

## Documentation

There is no published documentation.  One may generate documentation
out of the sources by running:
```
   $ doxygen doxy/doxygen.config
```

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

License
-------

Atria is distributed under the MIT license (see LICENSE).

> Copyright (c) 2014, 2015 Ableton AG, Berlin
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in
> all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
> THE SOFTWARE.
