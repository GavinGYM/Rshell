#!/bin/sh

INPUTS=("ls -a" "echo hello" "mkdir test" "echo world" "git status")

for input in "${INPUTS[@]}"
do
    echo "../rshell ${input}"
    output=$(../rshell ${input})
	result=$(${input})
    echo "Output: \"${output}\""
    echo "Result: \"${result}\""
    if [ "${output}" = "${result}" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
done
