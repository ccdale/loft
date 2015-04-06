/*
 * vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4 foldmethod=marker:
 *
 * defs.h
 *
 * C.C.Allison
 * chris.allison@hotmail.com
 *
 * Started: Monday  6 April 2015, 09:24:04
 * Version: 0.00
 * Last Modified: Monday  6 April 2015, 09:27:59
 */

#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <regex.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <libgen.h>
#include <errno.h>
#include <limits.h>

/* for directory stuff */
#include <sys/types.h>
#include <dirent.h>

#define CCA_HOME "/"
#define CCA_LOCK_FILE "/var/run/loft.pid"
#define MAX_MSG_LEN 4096

#define CCA_DEFAULT_CONFIGFILE "/etc/loft.conf"
#define CCA_DEFAULT_BUFFERSIZE "2048000"
#define CCA_DEFAULT_SLEEPTIME "1"
#define CCA_DEFAULT_FPOS "0"
#define CCA_DEFAULT_FILEBIN "/usr/bin/file"
#define CCA_DEFAULT_FILEBINARGS "-ib"
#define CCA_DEFAULT_GUNZIPBIN "/bin/gunzip"
#define CCA_DEFAULT_GUNZIPBINARGS "-c"
#define CCA_DEFAULT_UNZIPBIN "/usr/bin/unzip"
#define CCA_DEFAULT_UNZIPBINARGS "-p"
