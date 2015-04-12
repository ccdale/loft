/*
 * vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4 foldmethod=marker:
 *
 * loft.c
 *
 * C.C.Allison
 * chris.allison@hotmail.com
 *
 * Started: Saturday 11 April 2015, 06:39:24
 * Version: 0.00
 * Last Modified: Sunday 12 April 2015, 22:15:05
 *
 *
 * Copyright (c) 2015 Chris Allison chris.allison@hotmail.com
 *
 * This file is part of loft.
 * 
 * loft is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * loft is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with loft.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "loft.h"

void catchsignal(int sig)/* {{{1 */
{
    stopfollowing=1;
    DBG("in sig handler");
    // signal(sig,catchsignal);
} /* }}} */
void daemonize()/* {{{1 */
{
    int i,lfp;
    char str[MAX_MSG_LEN];
    int junk;

    if(getppid()==1) return; /* already a daemon */
    DBG("Forking");
    i=fork();
    if (i<0) 
    {
        CCAE(1,"fork failed. Exiting");
    }
    if (i>0) 
    {
        DBG("parent exiting after fork");
        exit(0);
    } /* parent exits */
    /* child (daemon) continues */
    DBG("fork success. Child process continues.");
    setsid(); /* obtain a new process group */
    DBG("closing file descriptors");
    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    DBG("redirecting standard i/o to /dev/null");
    i=open("/dev/null",O_RDWR); dup(i); dup(i); /* handle standard I/O */
    DBG("setting umask to 027");
    umask(027); /* set newly created file permissions */
    DBGL("cd'ing to %s",CCA_HOME);
    chdir(CCA_HOME); /* change running directory */
    DBG("Creating lock file");
    lfp=open(CCA_LOCK_FILE,O_RDWR|O_CREAT,0640);
    if (lfp<0) {
        CCAE(1,"Failed to create lock file, exiting.");
    } /* can not open */
    if (lockf(lfp,F_TLOCK,0)<0) {
        CCAE(1,"Cannot lock, another instance running? qitting");
    } /* can not lock */
    DBG("File locked.");
    /* first instance continues */
    sprintf(str,"%d",getpid());
    write(lfp,str,strlen(str)); /* record pid to lockfile */
    DBG("pid written to lock file");
    DBG("setting signal handlers");
    siga->sa_handler=SIG_IGN;
    if((junk=sigaction(SIGCHLD,siga,NULL))!=0){
        CCAE(1,"cannot ignore signal SIGCHLD");
    }
    siga->sa_handler=SIG_IGN;
    if((junk=sigaction(SIGTSTP,siga,NULL))!=0){
        CCAE(1,"cannot ignore signal SIGTSTP");
    }
    siga->sa_handler=SIG_IGN;
    if((junk=sigaction(SIGTTOU,siga,NULL))!=0){
        CCAE(1,"cannot ignore signal SIGTTOU");
    }
    siga->sa_handler=SIG_IGN;
    if((junk=sigaction(SIGTTIN,siga,NULL))!=0){
        CCAE(1,"cannot ignore signal SIGTTIN");
    }
    siga->sa_handler=catchsignal;
    if((junk=sigaction(SIGHUP,siga,NULL))!=0){
        CCAE(1,"cannot set handler for SIGHUP");
    }
    siga->sa_handler=catchsignal;
    if((junk=sigaction(SIGTERM,siga,NULL))!=0){
        CCAE(1,"cannot set handler for SIGTERM");
    }
    siga->sa_handler=catchsignal;
    if((junk=sigaction(SIGINT,siga,NULL))!=0){
        CCAE(1,"cannot set handler for SIGINT");
    }
    siga->sa_handler=catchsignal;
    if((junk=sigaction(SIGUSR1,siga,NULL))!=0){
        CCAE(1,"cannot set handler for SIGUSR1");
    }
    DBG("%s daemonized",PROGNAME);
}/* }}} */
void setDefaultConfig(void)/*{{{*/
{
    char *tk;
    char *tv;

    tk=strdup("daemonize");
    tv=strdup(CCA_DEFAULT_DAEMONIZE);
    updateConfig(tk,tv);
    tk=strdup("configfile");
    tv=strdup(CCA_DEFAULT_CONFIGFILE);
    updateConfig(tk,tv);
    tk=strdup("buffersize");
    tv=strdup(CCA_DEFAULT_BUFFERSIZE);
    updateConfig(tk,tv);
    tk=strdup("sleeptime");
    tv=strdup(CCA_DEFAULT_SLEEPTIME);
    updateConfig(tk,tv);
    tk=strdup("fpos");
    tv=strdup(CCA_DEFAULT_FPOS);
    updateConfig(tk,tv);
    tk=strdup("timeformat");
    tv=strdup(CCA_DEFAULT_TIME_FORMAT);
    updateConfig(tk,tv);
    tk=strdup("filebin");
    tv=strdup(CCA_DEFAULT_FILEBIN);
    updateConfig(tk,tv);
    tk=strdup("filebinargs");
    tv=strdup(CCA_DEFAULT_FILEBINARGS);
    updateConfig(tk,tv);
    tk=strdup("gunzipbin");
    tv=strdup(CCA_DEFAULT_GUNZIPBIN);
    updateConfig(tk,tv);
    tk=strdup("gunzipbinargs");
    tv=strdup(CCA_DEFAULT_GUNZIPBINARGS);
    updateConfig(tk,tv);
    tk=strdup("unzipbin");
    tv=strdup(CCA_DEFAULT_UNZIPBIN);
    updateConfig(tk,tv);
    tk=strdup("unzipbinargs");
    tv=strdup(CCA_DEFAULT_UNZIPBINARGS);
    updateConfig(tk,tv);
    tk=strdup("rotatedlogfileext");
    tv=strdup(CCA_DEFAULT_RLFEXT);
    updateConfig(tk,tv);
}/*}}}*/
int main(int argc,char **argv)/*{{{*/
{
    int ret=0;
    char *conffile;
    /* Define the allowable command line options, collecting them in argtable[] */
    struct arg_file *conf = arg_file0("c","conf-file","/etc/loft.conf","configuration file");
    struct arg_lit *help = arg_lit0("h","help","print this help and exit");
    struct arg_lit *vers = arg_lit0("v","version","print version information and exit");
    struct arg_end *end  = arg_end(20);
    void *argtable[] = {conf,help,vers,end};
    int exitcode=0;
    int nerrors;
    /* check the argtable[] entries were correctly allocated */
    if(arg_nullcheck(argtable) == 0){
        /* set default config filename */
        conf->filename[0]=PROGCONF;
        /* parse the command line */
        nerrors = arg_parse(argc,argv,argtable);

        /* check for help before error processing */
        if(help->count > 0){
            /* print the help/usage statement and exit */
            printf("Usage: %s",PROGNAME);
            arg_print_syntax(stdout,argtable,"\n");
            printf("Start the %s log file follower\n\n",PROGNAME);
            arg_print_glossary(stdout,argtable,"  %-20s %s\n");
            /* free up memory used for argument processing */
            arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
            printf("\nreport bugs to %s\n",PROGEMAIL);
            return 0;
        }
        /* check for version request before error checking */
        if(vers->count > 0){
            /* free up memory used for argument processing */
            arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
            /* print the requested information and exit */
            printf("%s %s\n",PROGNAME,PROGVERSION);
            printf("%s\n%s",PROGCOPYRIGHT,PROGLICENSE);
            return 0;
        }
        /* check for errors in command line arguments */
        if(nerrors > 0){
            /* display the errors in the arg_end struct */
            arg_print_errors(stdout,end,PROGNAME);
            printf("Try '%s --help' for more information.\n",PROGNAME);
            /* free up memory used for argument processing */
            arg_freetable(argtable,sizeof(argtable)/sizeof(argtable[0]));
            return 1;
        }

        /* command line processing completed */
}/*}}}*/
