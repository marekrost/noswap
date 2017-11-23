#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

static void wrerr(const char *p) {
  if (p) {
    const char *q = p + strlen(p);
    ssize_t     n;

    while (p < q) {
      n = write(STDERR_FILENO, p, (size_t)(q - p));
      if (n > 0)
        p += n;
      else
        if (n != -1 || errno != EINTR)
          return;
    }
  }
}

static void init(void) __attribute__((constructor));
static void init(void) {
  int saved_errno = errno;

  if (mlockall(MCL_CURRENT | MCL_FUTURE) == -1) {
    const char *errmsg = strerror(errno);
    wrerr("Cannot lock all memory: ");
    wrerr(errmsg);
    wrerr(".\n");
    exit(127);
  } else
    wrerr("All memory locked.\n");
  errno = saved_errno;
}
