#!/bin/sh

gcc -lGL -lglfw -I"/usr/include" main.c -o main
chmod 755 main
