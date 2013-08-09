/*
 * Copyright (c) 2013 Kjetil Matheussen
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 */


#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

#include "m_libpd.h"

#include "libpd_so.c"
#include "m_libpd_autogenerated.h"


static void write_libpd_so_to_tempfile(char *template){
  int file = mkostemp(template, S_IRUSR | S_IXUSR);
  write(file, libs_libpd_so, sizeof(libs_libpd_so));
  close(file);
}

pd_t *libpds_create(bool use_gui, const char *libdir){
  pd_t *pd = calloc(1, sizeof(pd_t));

  struct timeval my_timeval;
  gettimeofday(&my_timeval, NULL);

  char filename[1024];
  sprintf(filename, "/tmp/%llu_%llu_%d_XXXXXX", (unsigned long long)my_timeval.tv_sec, (unsigned long long)my_timeval.tv_usec, rand());
  write_libpd_so_to_tempfile(filename);

  pd->handle = dlopen(filename, RTLD_NOW | RTLD_LOCAL );  
  load_symbols(pd);

  unlink(filename);
  
  if (pd->libpd_init(use_gui, libdir)==false) {
    dlclose(pd->handle);
    free(pd);
    return NULL;
  }

  return pd;
}

void libpds_delete(pd_t *pd) {
  pd->libpd_cleanup();
  dlclose(pd->handle);
  free(pd);
}

