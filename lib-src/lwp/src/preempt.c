/* BLURB lgpl

                           Coda File System
                              Release 5

          Copyright (c) 1987-1999 Carnegie Mellon University
                  Additional copyrights listed below

This  code  is  distributed "AS IS" without warranty of any kind under
the  terms of the  GNU  Library General Public Licence  Version 2,  as
shown in the file LICENSE. The technical and financial contributors to
Coda are listed in the file CREDITS.

                        Additional copyrights

#*/

/*
                         IBM COPYRIGHT NOTICE

                          Copyright (C) 1986
             International Business Machines Corporation
                         All Rights Reserved

This  file  contains  some  code identical to or derived from the 1986
version of the Andrew File System ("AFS"), which is owned by  the  IBM
Corporation.   This  code is provided "AS IS" and IBM does not warrant
that it is free of infringement of  any  intellectual  rights  of  any
third  party.    IBM  disclaims  liability of any kind for any damages
whatsoever resulting directly or indirectly from use of this  software
or  of  any  derivative work.  Carnegie Mellon University has obtained
permission to  modify,  distribute and sublicense this code,  which is
based on Version 2  of  AFS  and  does  not  contain  the features and
enhancements that are part of  Version 3 of  AFS.  Version 3 of AFS is
commercially   available   and  supported  by   Transarc  Corporation,
Pittsburgh, PA.

*/

#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

#include <lwp/lwp.h>
#include <lwp/preempt.h>
#include "lwp.private.h"

#ifndef __alpha
char PRE_Block = 0;		/* used in lwp.c and process.s */
#else
int  PRE_Block = 0;
#endif

/* run the scheduler unless we are in a critical region */
static void AlarmHandler(int sig)
{
    if (PRE_Block == 0 && lwp_cpptr->level == 0) {
	PRE_BeginCritical();

	LWP_DispatchProcess();
	PRE_EndCritical();
    }
}

int PRE_InitPreempt(struct timeval *slice)
{
    struct itimerval itv;
    struct sigaction vec;

    if (lwp_cpptr == 0) return (LWP_EINIT);
    
    if (slice == 0) {
	itv.it_interval.tv_sec = DEFAULTSLICE;
	itv.it_value.tv_sec = DEFAULTSLICE;
	itv.it_interval.tv_usec = itv.it_value.tv_usec = 0;
    }  else	{
	itv.it_interval = *slice;
	itv.it_value = *slice;
    }

    vec.sa_handler = AlarmHandler;
    sigemptyset(&vec.sa_mask);
    vec.sa_flags = 0;

    if ((sigaction(SIGALRM, &vec, (struct sigaction *)0) == -1) ||
	(setitimer(ITIMER_REAL, &itv, (struct itimerval *) 0) == -1))
	return(LWP_ESYSTEM);

    return(LWP_SUCCESS);
}

int PRE_EndPreempt()
{

    struct itimerval itv;
    struct sigaction vec;

    if (lwp_cpptr == 0) return (LWP_EINIT);
    
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 0;

    vec.sa_handler = SIG_DFL;;
    sigemptyset(&vec.sa_mask);
    vec.sa_flags = 0;

    if ((setitimer(ITIMER_REAL, &itv, (struct itimerval *) 0) == -1) ||
	(sigaction(SIGALRM, &vec, NULL) == -1))
	return(LWP_ESYSTEM);

    return(LWP_SUCCESS);
}

void PRE_PreemptMe()
{
    lwp_cpptr->level = 0;
}

void PRE_Concurrent(int on)
{
}

void PRE_BeginCritical()
{
    lwp_cpptr->level++;
}

void PRE_EndCritical()
{
    lwp_cpptr->level--;
}