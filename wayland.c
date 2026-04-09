#define _GNU_SOURCE
#include <fcntl.h>
#include <linux/memfd.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/un.h>
#include <unistd.h>

// ---- syscall wrappers ----
static int sys_socket(int domain, int type, int protocol) {
  return syscall(SYS_socket, domain, type, protocol);
}

static int sys_connect(int fd, const struct sockaddr *addr, socklen_t len) {
  return syscall(SYS_connect, fd, addr, len);
}

static int sys_memfd_create(const char *name, unsigned int flags) {
  return syscall(SYS_memfd_create, name, flags);
}

static int sys_ftruncate(int fd, off_t size) {
  return syscall(SYS_ftruncate, fd, size);
}

static void *sys_mmap(void *addr, size_t length, int prot, int flags, int fd,
                      off_t offset) {
  return (void *)syscall(SYS_mmap, addr, length, prot, flags, fd, offset);
}

// ---- main ----
int main() {
  // 1. socket
  int sock = sys_socket(AF_UNIX, SOCK_STREAM, 0);
  if (sock < 0)
    return 1;
  printf("created socket = %d.\n", sock);

  // 2. build Wayland socket path
  const char *runtime = getenv("XDG_RUNTIME_DIR");
  if (!runtime)
    return 1;

  printf("got env\n");

  char path[108] = {0};
  snprintf(path, sizeof(path), "%s/wayland-1", runtime);

  struct sockaddr_un addr = {0};
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
  printf("path: %s, size:%d\n", addr.sun_path, sizeof(addr));
  // 3. connect
  int connected = sys_connect(3, (struct sockaddr *)&addr, 110);
  if (connected < 0)
    return 1;
  printf("connected = %d\n", connected);

  // 4. create memfd
  int memfd = sys_memfd_create("buffer", 0);
  if (memfd < 0)
    return 1;
  printf("created memfd.\n");

  int width = 320;
  int height = 240;
  int stride = width * 4;
  int size = stride * height;

  // 5. resize
  if (sys_ftruncate(memfd, size) < 0)
    return 1;
  printf("sys_ftruncated.");
  // 6. mmap framebuffer
  uint32_t *pixels =
      sys_mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, 0);

  if ((long)pixels < 0)
    return 1;
  printf("mmaped > pixels");
  // 7. draw (solid color)
  for (int i = 0; i < width * height; i++) {
    pixels[i] = 0xFF00FF00; // ARGB (green)
  }

  printf("DONE");

  // ---- stop here for now ----
  // At this point:
  // ✔ connected to Wayland
  // ✔ framebuffer ready
  // ❌ not yet sent protocol messages

  // pause(); // keep process alive

  return 0;
}
