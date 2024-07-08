#ifndef __NEONATE_H_
#define __NEONATE_H_
void disableRawMode(struct termios *orig_termios); 
int neonate(int time_arg);
void enableRawMode(struct termios *orig_termios);
void die(const char *s);
#endif