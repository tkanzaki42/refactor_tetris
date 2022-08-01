#include "hastoupdate.h"

extern struct timeval before_now, now;

int hasToUpdate(const suseconds_t *timer){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > *timer;
}
