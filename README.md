<!-- vim: set tw=78 ft=markdown -->
# loft
log file follower.

This utility enables the following of log files (as in tail -f) with the output
going to a user defined destination. 

It was written to cope with applications that write their own log files
without using syslog. It is difficult to use remote logging with such
applications, hence this utility.  It will follow your log file(s) and inject
them into syslog (either locally or remotely).

Be aware that if you send the logs to the local syslog then you will be
creating 2 copies of each log file locally, even if syslog is setup to send
logs off remotely.
