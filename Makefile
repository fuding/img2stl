decompressor: main.cpp deCompress.cpp
	clang++-libc++ -std=c++14 -o decompressor main.cpp deCompress.cpp -I.
