include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

###################
# tests target 
###################
enable_testing()

add_executable(
        tests
        helpers/test-helpers.c
        helpers/assertion-helpers.cc
        playground_test.cc
        strategies/no-duplicates_test.cc
        strategies/naked-pair_test.cc
        strategies/naked-single_test.cc
        strategies/hidden-single_test.cc
        unit/unit_test.cc
)
target_include_directories(tests PUBLIC
        helpers
        )
target_link_libraries(
        tests
        GTest::gtest_main
        applibs
)

include(GoogleTest)
gtest_discover_tests(tests)
