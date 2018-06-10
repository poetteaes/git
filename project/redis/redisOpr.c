/********************************
 * redis opration
 * created time: 2018-01-01
 * created by poetteaes
 *******************************/

# include "hiredis.h"
# include <stdlib.h>
# include <string.h>

# define NOT_FOUND -1403

/********************************
 * redis connect
 * return a pointer if success; 
 * return NULL if failed
 *******************************/
redisContext *redis_connect(char *ip, unsigned int port, char *passwd)
{
	redisContext *c = NULL;
	redisReply *replay = NULL;
	
	/*connect*/
	c = redisConnect(ip, port);
	if(c==NULL)
	{
		printf("Error: redisConnect() error!\n");
		return NULL;
	}
	if(c->err != 0) 
	{
		printf("Error: %s\n", c->errstr);
		redisFree(c);
    }
	
	/*auth if passwd is not NULL*/
	if(passwd != NULL)
	{
		replay  = (redisReply *)redisCommand(c, "AUTH %s", passwd);
		if( replay == NULL)
		{
			printf("Error: AUTH error!\n");
			redisFree(c);
			printf("redisFree\n");
		    return NULL;
		}
		if( !(replay->type==REDIS_REPLY_STATUS && memcmp(replay->str, "OK", 2)==0) )
		{
			printf("Error: AUTH error!\n");
			freeReplyObject(replay);
			redisFree(c);
			printf("redisFree\n");
		    return NULL;
		}
	}
	
	return c; /*connect success*/
}

/********************************
 * redis select
 * return length of value if success; 
 * return NOT_FOUND if not found
 * return -1 if failed
 *******************************/
int redis_select(redisContext *c, char *key, char *value)
{
	 redisReply *reply = NULL;
	 
	 if(value == NULL)
	 {
		 printf("Error: Invalid output argument!\n");
		 return -1;
	 }
	 
	 reply  = (redisReply *)redisCommand(c, "GET %s", key);
     if( reply == NULL)
	 {
		 printf("Error: GET error!\n");
		 return -1;
	 }
	 
	 if(reply->type != REDIS_REPLY_STRING && reply->type!=REDIS_REPLY_NIL)
     {
     	printf("Error: GET error!\n");
     	freeReplyObject(reply);
        return -1;
     }
	 if(reply->type==REDIS_REPLY_NIL)
	 {
		 printf("Not found\n");
		 freeReplyObject(reply);
		 return NOT_FOUND;
	 }
	 
	 memcpy(value, reply->str, reply->len);
	 freeReplyObject(reply);
	 return (reply->len);
}

/********************************
 * redis insert
 * return 0 if success; 
 * return -1 if failed
 *******************************/
int redis_insert(redisContext *c, char *key, char *value, int ex)
{
	redisReply *reply = NULL;
	
	if(ex<0)
	{
		printf("Error: Invalid input argument ex[%d]", ex);
		return -1;
	}
	
	/*test if the key has been existed*/
	reply = (redisReply *)redisCommand(c, "GET %s", key);
	if( reply == NULL)
	{
	 printf("Error: GET error!\n");
	 return -1;
	}
	if(reply->type != REDIS_REPLY_STRING && reply->type!=REDIS_REPLY_NIL)
    {
    	printf("Error: GET error!\n");
    	freeReplyObject(reply);
        return -1;
    }
	
	if(reply->type==REDIS_REPLY_STRING)
	{
		printf("Error: The key has existed.\n");
		freeReplyObject(reply);
		return -1;
	}
	freeReplyObject(reply);
	
	
	/*insert*/
	reply = NULL;
	if(ex !=0 )
	{
		reply = (redisReply *)redisCommand(c, "SET %s %s EX %d", key, value, ex);	
	}
	else
	{
		reply = (redisReply *)redisCommand(c, "SET %s %s", key, value); /*without ex*/
	}
	
	if( reply == NULL)
	{
	  printf("Error: SET error!\n");
	  return -1;
	}
	if( !(reply->type==REDIS_REPLY_STATUS && memcmp(reply->str, "OK", 2)==0) )
    {
    	printf("Error: SET error!\n");
    	freeReplyObject(reply);
        return -1;
    }
	
	
	freeReplyObject(reply);
	return 0;
}

/********************************
 * redis delete
 * return 0 if success; 
 * return NOT_FOUND if not found
 * return -1 if failed
 *******************************/
int redis_delete(redisContext *c, char *key)
{
	redisReply *reply = NULL;
	
	reply = (redisReply *)redisCommand(c, "DEL %s", key);
	if(reply==NULL || reply->type!=REDIS_REPLY_INTEGER)
	{
		printf("Error: The key doesn't exist.\n");
		freeReplyObject(reply);
		return -1;
	}
	
	freeReplyObject(reply);
	
	if(reply->integer==0)
		return NOT_FOUND;
	else
		return (reply->integer - 1); 
	
}

/********************************
 * redis delete
 * return 0 if success; 
 * return NOT_FOUND if not found
 * return -1 if failed
 *******************************/
int redis_update(redisContext *c, char *key, char *value, int ex)
{
	redisReply *reply = NULL;
	
	if(ex<0)
	{
		printf("Error: Invalid input argument ex[%d]", ex);
		return -1;
	}
	
	/*test if the key has been existed*/
	reply = (redisReply *)redisCommand(c, "GET %s", key);
	if( reply == NULL)
	{
	 printf("Error: GET error!\n");
	 return -1;
	}
	if(reply->type != REDIS_REPLY_STRING && reply->type!=REDIS_REPLY_NIL)
    {
    	printf("Error: GET error!\n");
    	freeReplyObject(reply);
        return -1;
    }
	
	if(reply->type==REDIS_REPLY_NIL)
	{
		printf("The key doesn't exist.\n");
		freeReplyObject(reply);
		return NOT_FOUND;
	}
	freeReplyObject(reply);
	
	/*update*/
	reply = NULL;
	if(ex !=0 )
	{
		reply = (redisReply *)redisCommand(c, "SET %s %s EX %d", key, value, ex);	
	}
	else
	{
		reply = (redisReply *)redisCommand(c, "SET %s %s", key, value); /*without ex*/
	}
	
	if( reply == NULL)
	{
	  printf("Error: SET error!\n");
	  return -1;
	}
	if( !(reply->type==REDIS_REPLY_STATUS && memcmp(reply->str, "OK", 2)==0) )
    {
    	printf("Error: SET error!\n");
    	freeReplyObject(reply);
        return -1;
    }
	
	
	freeReplyObject(reply);
	return 0;
}

/*redis disconnect*/
void redis_disconnect(redisContext *c)
{
	redisFree(c);
}