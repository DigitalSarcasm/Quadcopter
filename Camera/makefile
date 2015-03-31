all: test tstpack qread

test: test.cpp
	g++ test.cpp -o test -lwiringPi

tstpack: tstpackreader.cpp
	g++ tstpackreader.cpp -o tstpack -lwiringPi

qread: qread.cpp
	g++ qread.cpp base64.cpp -o qread