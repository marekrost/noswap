#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int run_as(int uid, int gid, const char *cmd, const char *argv[], const char *env[]) {
  int child = fork();
  if(child == 0) {
    setgid(gid);
    setuid(uid);
    execvpe(cmd, argv, env);
  } else {
    if(child > 0)
      waitpid(child);
    else {
      // Error: fork() failed!
    }
  }
}

static void usage(int use_err = 0) {
  fprintf(use_err ? stderr : stdout,
    "Usage: noswap [OPTION]..."
    "Set memory locking ulimits and run executable."
  );
}

int main(int argc, const char *argv[]) {

  int             c;
  const char    * short_opt = "hf:";
  struct option   long_opt[] = {
    {"help",          no_argument,       NULL, 'h'},
    {"file",          required_argument, NULL, 'f'},
    {NULL,            0,                 NULL, 0  }
  };

  while((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
    switch(c) {
      case -1:       /* no more arguments */
      case 0:        /* long options toggles */
        break;
      case 'f':
        printf("you entered \"%s\"\n", optarg);
        break;
      case 'h':
        usage();
        return 0;
      case ':':
      case '?':
        fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
        return(-2);
      default:
        fprintf(stderr, "%s: invalid option -- %c\n", argv[0], c);
        fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
        return(-2);
    };
  };

  // TODO: Check limits and alter according to request

  // TODO: Properly configure user ENV
  char *env[3];
  env[0] = "HOME=/home/caroline";
  env[1] = "DISPLAY=:0";
  env[2] = 0;

  // TODO: Properly run
  run_as(100, 1000, argv[1], argv, env);

  return 0;
}
