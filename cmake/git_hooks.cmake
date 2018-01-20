# Create symlink for clang-format pre-commit hook
execute_process(
        COMMAND "${CMAKE_COMMAND}" "-E" "create_symlink" "${CMAKE_CURRENT_SOURCE_DIR}/.hooks/pre-commit-clang-format" "${CMAKE_CURRENT_SOURCE_DIR}/.git/hooks/pre-commit"
        OUTPUT_VARIABLE OUTPUT
        RESULT_VARIABLE clang_format_symlink_result
)
if(clang_format_symlink_result EQUAL 0)
    message(STATUS "Created clang-format pre-commit hook.")
else()
    message(WARNING "Failed to install clang-format pre-commit hook.")
endif()
