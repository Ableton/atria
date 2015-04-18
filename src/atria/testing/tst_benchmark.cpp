// Copyright: 2014, Ableton AG, Berlin. All rights reserved.

#include <atria/testing/benchmark.hpp>
#include <vector>

namespace atria {
namespace testing {

template <typename T>
void unoptimize(const T&)
{
}

template void unoptimize<int> (const int&);
template void unoptimize<std::vector<int> > (const std::vector<int>&);

} // namespace testing
} // namespace atria
