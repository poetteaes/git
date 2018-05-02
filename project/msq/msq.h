# ifndef _SHM_H
# define _SHM_H


# define MAX_MSG_LEN 1024
# define MSQ_KEY 21012

typedef struct MSGQUEUE
{
	long msgType;
	char msgText[MAX_MSG_LEN];
	
}Msg;

#endif