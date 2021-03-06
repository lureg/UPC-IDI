all: lab1, lab2, lab3, lab4

lab1:
	g++ -o lab1 lab1.cc -lglut -lGL
lab2: lab2.o
	g++ -o lab2 lab2.o model.o -lGLU -lglut -lGL
lab2.o:	lab2.cc
	g++ -c lab2.cc
lab3:
	g++ -o lab3 lab3.cc -lglut -lGL
lab4:
	g++ -o lab4 lab4.cc -lglut -lGL

clean:
	rm -rf *o lab1 lab2 lab3 lab4
