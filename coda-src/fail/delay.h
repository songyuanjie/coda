#ifndef _BLURB_
#define _BLURB_
/*

            Coda: an Experimental Distributed File System
                             Release 4.0

          Copyright (c) 1987-1996 Carnegie Mellon University
                         All Rights Reserved

Permission  to  use, copy, modify and distribute this software and its
documentation is hereby granted,  provided  that  both  the  copyright
notice  and  this  permission  notice  appear  in  all  copies  of the
software, derivative works or  modified  versions,  and  any  portions
thereof, and that both notices appear in supporting documentation, and
that credit is given to Carnegie Mellon University  in  all  documents
and publicity pertaining to direct or indirect use of this code or its
derivatives.

CODA IS AN EXPERIMENTAL SOFTWARE SYSTEM AND IS  KNOWN  TO  HAVE  BUGS,
SOME  OF  WHICH MAY HAVE SERIOUS CONSEQUENCES.  CARNEGIE MELLON ALLOWS
FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.   CARNEGIE  MELLON
DISCLAIMS  ANY  LIABILITY  OF  ANY  KIND  FOR  ANY  DAMAGES WHATSOEVER
RESULTING DIRECTLY OR INDIRECTLY FROM THE USE OF THIS SOFTWARE  OR  OF
ANY DERIVATIVE WORK.

Carnegie  Mellon  encourages  users  of  this  software  to return any
improvements or extensions that  they  make,  and  to  grant  Carnegie
Mellon the rights to redistribute these changes without encumbrance.
*/

static char *rcsid = "$Header: /coda/coda.cs.cmu.edu/project/coda/cvs/coda/coda-src/fail/Attic/delay.h,v 4.1 1997/01/08 21:49:36 rvb Exp $";
#endif /*_BLURB_*/





/* 
 * slow.h -- include file for network delay package
 *           L. Mummert
 */
#define MINDELAY  16   /* minimum delay time, in msec */
 		       /* anything less is not delayed */

#include "cargs.h"

/* Exported Routines */
int Delay_Init C_ARGS(());
int DelayPacket C_ARGS((int speed, long socket, struct sockaddr_in *sap, RPC2_PacketBuffer *pb, int queue));
int FindQueue C_ARGS((unsigned char a, unsigned char b, unsigned char c, unsigned char d));
int MakeQueue C_ARGS((unsigned char a, unsigned char b, unsigned char c, unsigned char d));
     

     
