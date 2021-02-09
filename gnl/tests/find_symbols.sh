#!/bin/sh
read -p 'Input .c file name :-> ' FILE_NAME;
grep -E '^(static\s+)?\w{3,8}\s+\*{0,3}\w+\s?\(.*\)' $FILE_NAME;