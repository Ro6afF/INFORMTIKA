all:
	clang++ main.cpp -o main.exe `pkg-config --libs --cflags sdl2` -lGL -std=gnu++1z -I./include ./lib/*
	DRI_PRIME=0 ./main.exe
