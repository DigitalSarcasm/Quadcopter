all: test tstpack qread scom

test: test.cpp
	g++ test.cpp -o test -lwiringPi

tstpack: tstpackreader.cpp
	g++ tstpackreader.cpp -o tstpack -lwiringPi

qread: qread.cpp
	g++ qread.cpp base64.cpp -o qread
	
scom: scom.cpp
	g++ scom.cpp rutil.cpp base64.cpp -o scom -lwiringPi