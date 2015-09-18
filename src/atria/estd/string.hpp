//
// Copyright (C) 2014, 2015 Ableton AG, Berlin. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

/*!
 * @file
 */

#pragma once

#include <string>

namespace atria {
namespace estd {

inline
namespace literals {
inline
namespace string_literals {

ABL_DISABLE_WARNINGS

inline std::basic_string<char> operator ""_s(
  const char* str, std::size_t len)
{
  return std::basic_string<char>(str, len);
}

inline std::basic_string<wchar_t> operator ""_s(
  const wchar_t* str, std::size_t len)
{
  return std::basic_string<wchar_t>(str, len);
}

inline std::basic_string<char16_t> operator ""_s(
  const char16_t* str, std::size_t len)
{
  return std::basic_string<char16_t>(str, len);
}

inline std::basic_string<char32_t> operator ""_s(
  const char32_t* str, std::size_t len)
{
  return std::basic_string<char32_t>(str, len);
}

ABL_RESTORE_WARNINGS

} // namespace string_literals
} // namespace literals

} // namespace estd
} // namespace atria
