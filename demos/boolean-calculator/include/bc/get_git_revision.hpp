#pragma once

#include <string>

namespace bc {

constexpr std::string_view get_git_revision() {
#ifdef GIT_REVISION_
    constexpr std::string_view git_revision = EMP_STRINGIFY(GIT_REVISION_);
#else
    constexpr std::string_view git_revision = "NO_GIT";
#endif
  return git_revision;
}

}
