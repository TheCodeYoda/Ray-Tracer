debug: main.o
	g++ obj/main.o -o target/debug
main.o: src/vec3.hpp src/color.hpp src/ray.hpp src/sphere.hpp src/main.cpp src/hittable.hpp src/hittable_list.hpp src/constants.hpp src/camera.hpp
	g++ -c src/main.cpp -o obj/main.o
clean:
	rm obj/*.o target/debug
clean_all:
	rm obj/*.o target/debug Images/image 
