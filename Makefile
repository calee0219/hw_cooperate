all:hw2

hw2:
	g++ -O2 -std=c++11 hw2.cpp -o hw2
run:
	./hw2
clean:
	rm -f hw2
