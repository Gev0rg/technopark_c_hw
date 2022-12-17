#!/bin/sh
append_newline () {
    if [ -z "$(tail -c 1 "$1")" ]; then
        :
    else
        echo >> "$1"
    fi
}
print_lint_header() {
    echo "\n***** ${1} *****"
}
print_lint_header "CLANG-FORMAT"
THIS_PATH="."
THIS_DIR="$(dirname "$THIS_PATH")"
FILE_LIST_INCLUDE="$(find "$THIS_DIR/include" | grep -E ".*(\.cpp|\.h|\.hpp|\.hh)$")"
FILE_LIST_TESTS="$(find "$THIS_DIR/tests" | grep -E ".*(\.cpp|\.h|\.hpp|\.hh)$")"
echo "Files found to format: \n\"\"\"\n${FILE_LIST_INCLUDE}\n\"\"\"\n${FILE_LIST_TESTS}\n\"\"\"\n"
# Run clang-format
print_lint_header "START FORMATTING"
clang-format --verbose -i --style=file ${FILE_LIST_INCLUDE}
clang-format --verbose -i --style=file ${FILE_LIST_TESTS}
for f in ${FILE_LIST_INCLUDE}
do append_newline $f 
done
for f in ${FILE_LIST_TESTS}
do append_newline $f 
done
print_lint_header "SUCCESS"