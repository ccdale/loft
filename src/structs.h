/*
 * vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4 foldmethod=marker:
 *
 * src/client/structs.h
 *
 * C.C.Allison
 * chris.allison@hotmail.com
 *
 * Started: Friday 28 December 2012, 22:09:13
 * Version: 0.00
 * Revision: $Id: structs.h 53 2013-02-18 22:43:38Z chris.charles.allison@gmail.com $
 * Last Modified: Sunday 12 April 2015, 22:10:01
 */

#ifndef CCA_STRUCTS_H
#define CCA_STRUCTS_H

struct FollowedFile
{
    char *filename;
    char *linebuffer;
    // char *summary;
    // char *hsummary;
    char *searchfor;
    regex_t *creg;
    char *dateformat;
    long fpos;
    long linenumber;
    long bufsize;
    long currentfilesize;
    long lastfilesize;
    int summarize;
    int summarysize;
    int whystopped;
    int sleeptime;
    int minstamp;
    int maxstamp;
    int linelength;
    time_t linetime;
};

struct LogFile
{
    char *filename;
    int filenum;
    long filesize;
    long numlines;
    int minstamp;
    int maxstamp;
    int type; /* text=1, gzip=2, zip=3 */
    struct LogFile *next;
};

#endif
