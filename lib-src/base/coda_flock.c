/* BLURB gpl

                           Coda File System
                              Release 6

          Copyright (c) 1987-2003 Carnegie Mellon University
                  Additional copyrights listed below

This  code  is  distributed "AS IS" without warranty of any kind under
the terms of the GNU General Public Licence Version 2, as shown in the
file  LICENSE.  The  technical and financial  contributors to Coda are
listed in the file CREDITS.

                        Additional copyrights

#*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <unistd.h>
#include <errno.h>

#ifdef HAVE_FCNTL_LOCKING
#include <fcntl.h>
#include <string.h>
#else /* HAVE_FLOCK_LOCKING */
#include <sys/file.h>
#endif

int myflock(int fd, int type, int block) {
#ifdef HAVE_FCNTL_LOCKING
    struct flock lock;
    int rc;
    
    memset((char *) &lock, 0, sizeof(struct flock));
    lock.l_type = type;
    while ((rc = fcntl(fd, block, &lock)) < 0
    	   && block == F_SETLKW
    	   && errno == EINTR)		/* interrupted */
    	sleep(1);
    return rc;

#else /* HAVE_FLOCK_LOCKING */
    return flock(fd, type | block);
#endif
}
