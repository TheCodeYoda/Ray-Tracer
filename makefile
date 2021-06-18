debug: main.o
	g++ main.o -o target/debug
main.o: src/vec3.hpp src/color.hpp src/main.cpp
	g++ -c src/main.cpp
clean:
	rm main.o target/debug
clean_all:
	rm main.o target/debug Images/image 
