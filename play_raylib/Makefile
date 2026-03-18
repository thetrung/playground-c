Default: build run clean

build:
	gcc glb_loader.c -S -masm=intel
	gcc glb_loader.c -o glb_loader -lraylib

run:
	./glb_loader

clean:
	rm -rf glb_loader glb_loader.o glb_loader.s
