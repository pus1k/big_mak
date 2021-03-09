all: lab1 lab2 lab3 lab4 clear

lab1: build/lab1.o
	g++ -o lab1 build/lab1.o
build/lab1.o: src/lab1.cpp
	g++ -Wall -Werror -o build/lab1.o -c src/lab1.cpp
lab2: build/lab2.o
	g++ -o lab2 build/lab2.o
build/lab2.o: src/lab2.cpp
	g++ -Wall -Werror -o build/lab2.o -c src/lab2.cpp
lab3: build/lab3.o
	g++ -o lab3 build/lab3.o
build/lab3.o: src/lab3.cpp
	g++ -Wall -Werror -o build/lab3.o -c src/lab3.cpp
lab4: build/lab4.o
	g++ -o lab4 build/lab4.o
build/lab4.o: src/lab4.cpp
	g++ -Wall -Werror -o build/lab4.o -c src/lab4.cpp

clear:
	clear
clean:
	rm -rf build/* lab1 lab2 lab3 lab4 
	clear