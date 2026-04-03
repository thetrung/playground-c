Default: build clean

build: glb_loader draw_grid

glb_loader: glb_loader.c
	# gcc glb_loader.c -S -masm=intel
	gcc glb_loader.c -o glb_loader -lraylib
	./glb_loader

draw_grid: draw_grid.c
	gcc draw_grid.c -o draw_grid -lraylib
	./draw_grid

clean:
	rm -rf \
	glb_loader glb_loader.o glb_loader.s \
	draw_grid draw_grid.o

