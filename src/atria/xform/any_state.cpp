// Copyright: 2015, Ableton AG, Berlin. All rights reserved.

#include <atria/xform/any_state.hpp>

namespace atria {
namespace xform {

any_state::holder_base::~holder_base() = default;
any_state::null_holder::~null_holder() = default;

any_state::null_holder any_state::null_holder_;

} // namespace xform
} // namespace atria
