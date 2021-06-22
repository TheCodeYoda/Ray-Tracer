debug: main.o
	g++ main.o -o target/debug
main.o: src/vec3.hpp src/color.hpp src/ray.hpp src/sphere.hpp src/main.cpp src/hittable.hpp src/hittable_list.hpp src/constants.hpp
	g++ -c src/main.cpp
clean:
	rm main.o target/debug
clean_all:
	rm main.o target/debug Images/image 
