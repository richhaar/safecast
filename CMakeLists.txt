cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SafeCast")

add_library(SafeCast INTERFACE src/safe_cast.hpp)
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

add_executable(SafeCastTest src/safe_cast_test.cxx)
set_property(TARGET SafeCastTest PROPERTY CXX_STANDARD 20)
target_link_libraries(SafeCastTest PRIVATE SafeCast GTest::gtest_main)
gtest_discover_tests(SafeCastTest)

# Up warning levels, many recommendations taken from:
# https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md
if(MSVC)
  target_compile_options(SafeCastTest PRIVATE
      /W4
      /external:W1 # Lower warning levels for external code
      /w14242 # 'identfier': conversion from 'type1' to 'type1', possible loss of data
      /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
      /w14263 # 'function': member function does not override any base class virtual member function
      /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
      /w14287 # 'operator': unsigned/negative constant mismatch
      /w14296 # 'operator': expression is always 'boolean_value'
      /w14305 # 'conversion': truncation from 'type1' to 'type2'
      /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
      /w14545 # expression before comma evaluates to a function which is missing an argument list
      /w14546 # function call before comma missing argument list
      /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
      /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
      /w14555 # expression has no effect; expected expression with side-effect
      /w14619 # pragma warning: there is no warning number 'number'
      /w14640 # Enable warning on thread unsafe static member initialization
      /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
      /w14905 # wide string literal cast to 'LPSTR'
      /w14906 # string literal cast to 'LPWSTR'
      /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
      /w44365 # '=': conversion from 'type1' to 'type2', signed/unsigned mismatch
      /w44388 # 'token' : signed/unsigned mismatch
      /w44389 # 'equality-operator' : signed/unsigned mismatch
      /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside the for-loop scope
      $<$<BOOL:${CMAKE_COMPILE_WARNING_AS_ERROR}>:/WX>
  )
else()
  target_compile_options(SafeCastTest PRIVATE
      -Wall
      -Wextra
      -Wpedantic               # Warn if non standard C++ is used
      -Wshadow                 # Warn on overshadowing variables
      -Wold-style-cast         # Warn if using C style casts
      -Wnon-virtual-dtor       # Warn if a class with virtual functions has a non-virtual destructor.
      -Wcast-align             # Warn whenever a pointer is cast such that the required alignment of the target is increased.
      -Wunused                 # Warn on unused variables 
      -Woverloaded-virtual     # Warn if you overload (not override) a virtual function
      -Wconversion             # Warn on type conversations that may lose data
      -Wsign-conversion        # Warn on sign conversions
      -Wmisleading-indentation # Warn if indendation implies blocks where blocks don't exist
      -Wduplicated-cond        # Warn if if/else chain has duplicated conditions
      -Wduplicated-branches    # Warn if if/else branches have duplicated code
      -Wlogical-op             # Warn about logical operations being used where bitwise were probably wanted
      -Wnull-dereference       # Warn if null deference is detected
      -Wuseless-cast           # Warn if a cast is performed to the same type
      -Wdouble-promotion       # Warn if a float is implicitly promtoed to double
      -Wformat=2               # Warn on security issues around functions that format output e.g. printf
      $<$<BOOL:${CMAKE_COMPILE_WARNING_AS_ERROR}>:-Werror>
  )
endif()

