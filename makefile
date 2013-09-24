all: build
	make -C build

build:
	mkdir build && cd build && cmake ..

clean:
	rm -rf build/
