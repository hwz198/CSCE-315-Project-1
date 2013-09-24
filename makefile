all: build
	make -C build

build:
	mkdir build && cd build && CXX=g++ cmake ..

clean:
	rm -rf build/
