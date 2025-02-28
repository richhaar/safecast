# SafeCast

SafeCast is a C++ library that provides a safe way to cast between different numeric types, preventing overflow and underflow errors. It's designed to be easy to use and integrate into existing projects, offering a lightweight alternative to boost::numeric_cast.

## Features

* Header-only library for easy integration.
* Supports casting between signed and unsigned integers of different sizes.
* Throws exceptions for overflow and underflow conditions.
* Compile-time checks to ensure type safety.
* No external dependencies.


## Installation

To use SafeCast in your project, simply copy the `safe_cast.hpp` file into your project directory and include it in your source files.

```cpp
#include "safe_cast.hpp"

// Safe casts that will succeed
auto const a = sc::safe_cast<int>(0ULL);
auto const b = sc::safe_cast<uint32_t>(int64_t{100});
auto const c = sc::safe_cast<int>(120ULL);

// Casts that will throw exceptions
try {
    auto const d = sc::safe_cast<int8_t>(std::numeric_limits<int16_t>::min());
} catch (std::underflow_error const& ex) {
    std::cerr << ex.what() << std::endl; // "Underflow casting from short (value: -32768) to signed char."
}

try {
    auto const e = sc::safe_cast<uint32_t>(std::numeric_limits<int64_t>::max());
} catch (std::overflow_error const& ex) {
    std::cerr <<  ex.what() << std::endl; // "Overflow casting from __int64 (value: 9223372036854775807) to unsigned int."
}
```

## Requirements

* C++ 20

## Licence

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.

## Acknowledgements

This project was inspired by the [boost::numeric_cast](https://www.boost.org/doc/libs/1_87_0/libs/numeric/conversion/doc/html/boost_numericconversion/improved_numeric_cast__.html) library, which provides similar functionality for casting between numeric types. SafeCast is designed to be a lightweight alternative that is easier to integrate into existing projects.

## Authors

* Richard Haar
