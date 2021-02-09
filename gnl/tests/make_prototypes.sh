#!/bin/sh
./find_symbols.sh | sed -e 's/$/;/g'