cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SafeCast")

add_library(SafeCast INTERFACE "safe_cast.hpp")
set_property(TARGET SafeCast PROPERTY CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(SafeCastTest safe_cast_test.cxx)
target_link_libraries(SafeCastTest PRIVATE SafeCast GTest::gtest_main)
gtest_discover_tests(SafeCastTest)

target_compile_options(SafeCastTest PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

