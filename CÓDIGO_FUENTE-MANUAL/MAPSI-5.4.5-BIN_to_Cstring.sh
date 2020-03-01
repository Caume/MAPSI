#! /bin/sh
# script de shell para convertir datos binarios en 
# cadena hexadecimal de C
hexdump -e '200/1 "|x%02x" "\n"' $1 | sed -e 's/|/\\/g' -e 's/\\x  //g'

