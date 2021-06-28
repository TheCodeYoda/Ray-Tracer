debug: main.o
	g++ -O3 -g obj/main.o -o target/debug
main.o:
	g++ -c -O3 src/main.cpp -o obj/main.o
clean:
	rm obj/*.o target/debug
clean_all:
	rm obj/*.o target/debug Images/* 
