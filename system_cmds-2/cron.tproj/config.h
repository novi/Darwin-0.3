/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * "Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.0 (the 'License').  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License."
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/* Copyright 1988,1990,1993,1994 by Paul Vixie
 * All rights reserved
 *
 * Distribute freely, except: don't remove my name from the source or
 * documentation (don't take credit for my work), mark your changes (don't
 * get me blamed for your possible bugs), don't alter or remove this
 * notice.  May be sold if buildable source is provided to buyer.  No
 * warrantee of any kind, express or implied, is included with this
 * software; use at your own risk, responsibility for damages (if any) to
 * anyone resulting from the use of this software rests entirely with the
 * user.
 *
 * Send bug reports, bug fixes, enhancements, requests, flames, etc., and
 * I'll try to keep a version up to date.  I can be reached as follows:
 * Paul Vixie          <paul@vix.com>          uunet!decwrl!vixie!paul
 */

/* config.h - configurables for Vixie Cron
 *
 * $Id: config.h,v 1.1.1.1.56.2 1999/03/16 17:53:17 wsanchez Exp $
 */

#if !defined(_PATH_SENDMAIL)
# define _PATH_SENDMAIL "/usr/lib/sendmail"
#endif /*SENDMAIL*/

/*
 * these are site-dependent
 */

#ifndef DEBUGGING
#define DEBUGGING 1	/* 1 or 0 -- do you want debugging code built in? */
#endif

			/*
			 * choose one of these MAILCMD commands.  I use
			 * /bin/mail for speed; it makes biff bark but doesn't
			 * do aliasing.  /usr/lib/sendmail does aliasing but is
			 * a hog for short messages.  aliasing is not needed
			 * if you make use of the MAILTO= feature in crontabs.
			 * (hint: MAILTO= was added for this reason).
			 */

#define MAILCMD _PATH_SENDMAIL					/*-*/
#define MAILARGS "%s -FCronDaemon -odi -oem -or0s %s"		/*-*/
			/* -Fx	 = set full-name of sender
			 * -odi	 = Option Deliverymode Interactive
			 * -oem	 = Option Errors Mailedtosender
			 * -or0s = Option Readtimeout -- don't time out
			 */

/* #define MAILCMD "/bin/mail"			/*-*/
/* #define MAILARGS "%s -d  %s"			/*-*/
			/* -d = undocumented but common flag: deliver locally?
			 */

/* #define MAILCMD "/usr/mmdf/bin/submit"	/*-*/
/* #define MAILARGS "%s -mlrxto %s"		/*-*/

/* #define MAIL_DATE				/*-*/
			/* should we include an ersatz Date: header in
			 * generated mail?  if you are using sendmail
			 * for MAILCMD, it is better to let sendmail
			 * generate the Date: header.
			 */

			/* if ALLOW_FILE and DENY_FILE are not defined or are
			 * defined but neither exists, should crontab(1) be
			 * usable only by root?
			 */
/*#define ALLOW_ONLY_ROOT			/*-*/

			/* if you want to use syslog(3) instead of appending
			 * to CRONDIR/LOG_FILE (/var/cron/log, e.g.), define
			 * SYSLOG here.  Note that quite a bit of logging
			 * info is written, and that you probably don't want
			 * to use this on 4.2bsd since everything goes in
			 * /usr/spool/mqueue/syslog.  On 4.[34]bsd you can
			 * tell /etc/syslog.conf to send cron's logging to
			 * a separate file.
			 *
			 * Note that if this and LOG_FILE in "pathnames.h"
			 * are both defined, then logging will go to both
			 * places.
			 */
#define SYSLOG	 			/*-*/
