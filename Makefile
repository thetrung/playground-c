default: build

build: tiny_vm sdl3

tiny_vm: tiny_vm.c 
	gcc tiny_vm.c -o tiny_vm

sdl3: sdl3.c
	gcc sdl3.c -o sdl3 -lSDL3

clean:
	rm -rf \
		tiny_vm tiny_vm.o \
		sdl3 sdl3.o 

