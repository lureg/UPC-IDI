all: lab1, lab2, lab3, lab4

lab1:
	g++ -o lab1 lab1.cc -lglut -lGL
lab2:
	g++ -o lab2 lab2.cc -lglut -lGL
lab3:
	g++ -o lab3 lab3.cc -lglut -lGL
lab4:
	g++ -o lab4 lab4.cc -lglut -lGL

clean:
	rm -rf *o lab1 lab2 lab3 lab4
