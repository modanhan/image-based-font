all: *.cpp
	g++ *.cpp -std=c++14 -lGL -lglfw -lGraphicsMagick++ -I/usr/include/GraphicsMagick

run: all
	./a.out
