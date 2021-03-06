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
                           none currently

#*/




#ifdef __cplusplus
extern "C" {
#endif __cplusplus

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <errno.h>
#include "coda_string.h"
#include <unistd.h>
#include <stdlib.h>

#ifdef __cplusplus
}
#endif __cplusplus

#include "venusioctl.h"
#include "vice.h"

struct GetFid {
    ViceFid fid;
    ViceVersionVector vv;
    char realm[MAXHOSTNAMELEN+1];
};


void main(int argc, char **argv)
{
    GetFid out;
    memset(&out, 0, sizeof(struct GetFid));

    struct ViceIoctl vi;
    vi.in = 0;
    vi.in_size = 0;
    vi.out = (char *)&out;
    vi.out_size = sizeof(struct GetFid);

    if (pioctl(argv[1], VIOC_GETFID, &vi, 0) != 0) {
	perror("pioctl:GETFID");
	exit(-1);
    }

    printf("FID = (%s@%s)\n", FID_(&out.fid), out.realm);
    printf("\tVV = {[");
    for (int i = 0; i < VSG_MEMBERS; i++)
	printf(" %d", (&(out.vv.Versions.Site0))[i]);
    printf(" ] [ %#x %d ] [ %#x ]}\n",
	     out.vv.StoreId.Host, out.vv.StoreId.Uniquifier, out.vv.Flags);

    exit(0);
}
