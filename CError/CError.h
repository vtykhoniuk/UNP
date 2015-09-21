#ifndef CERROR_H
#define CERROR_H

#ifndef CERROR_MAXLINE
#define CERROR_MAXLINE  1024
#endif // CERROR_MAXLINE

// SYSTEM CALL ERRORS

/* Fatal error related to system call
   Print and terminate */

void err_sys(const char* fmt, ...);

/* Non fatal error related to system call
   Print error message and return */

void err_ret(const char* fmt, ...);



// APPLICATION ERRORS

/* Fatal error unrelated to system call
   Print and terminate */

void err_quit(const char* fmt, ...);

/* Non fatal error unrelated to system call
   Print error message and return */

void err_msg(const char* fmt, ...);

#endif // CERROR_H
