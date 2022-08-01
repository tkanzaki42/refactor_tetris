#include "hastoupdate.h"

extern struct timeval before_now, now;
extern suseconds_t timer;

int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}
