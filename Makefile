all: lab1 lab2 lab3 lab4 lab5 lab6 lab10 lab11 lab12 clear

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
lab5: build/lab5.o
	g++ -o lab5 build/lab5.o
build/lab5.o: src/lab5.cpp
	g++ -Wall -Werror -o build/lab5.o -c src/lab5.cpp
lab6: build/lab6.o
	g++ -o lab6 build/lab6.o
build/lab6.o: src/lab6.cpp
	g++ -Wall -Werror -o build/lab6.o -c src/lab6.cpp
lab10: build/lab10.o
	g++ -o lab10 build/lab10.o
build/lab10.o: src/lab10.cpp
	g++ -Wall -Werror -o build/lab10.o -c src/lab10.cpp
lab11: build/lab11.o
	g++ -o lab11 build/lab11.o
build/lab11.o: src/lab11.cpp
	g++ -Wall -Werror -o build/lab11.o -c src/lab11.cpp
lab12: build/lab12.o
	g++ -o lab12 build/lab12.o
build/lab12.o: src/lab12.cpp
	g++ -Wall -Werror -o build/lab12.o -c src/lab12.cpp
clear:
	clear
clean:
	rm -rf build/* lab1 lab2 lab3 lab4 lab5 lab6 lab10 lab11 lab12 tet
	clear