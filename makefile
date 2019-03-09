all: program1

program1:
	 g++ -o sort.exe sort.cpp -std=c++11 -pthread
