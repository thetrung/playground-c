default: build

build: tiny_vm sdl3 xcb

tiny_vm: tiny_vm.c 
	gcc tiny_vm.c -o tiny_vm

sdl3: sdl3.c
	gcc sdl3.c -o sdl3 -lSDL3

xcb: xcb.c
	gcc xcb.c -o xcb -lxcb

clean:
	rm -rf \
		tiny_vm tiny_vm.o \
		sdl3 sdl3.o 			\
		xcb xcb.o

