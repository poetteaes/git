/********************************
 * redis opration test
 * created time: 2018-01-01
 * created by poetteaes
 *******************************/

# include "hiredis.h"
# include <stdlib.h>
# include <string.h>

# define EX_TIME 3600
# define NOT_FOUND -1403

redisContext *redis_connect(char *ip, unsigned int port, char *passwd);
void redis_disconnect(redisContext *c);
void redis_disconnect(redisContext *c);
int redis_insert(redisContext *c, char *key, char *value, int ex);
int redis_delete(redisContext *c, char *key);
int redis_select(redisContext *c, char *key, char *value);
int redis_update(redisContext *c, char *key, char *value, int ex);

int main(void)
{
	int ret;
	char ip[] = "127.0.0.1";
	unsigned int port = 6379;
	redisContext *c = NULL;
	char key[128] = {0};
	char value[128] ={0};
	
	memcpy(key, "key1", 4);
	memcpy(value, "value1", 6);
	
	/*connect*/
	c = redis_connect(ip, port, NULL);
	if(c == NULL || c->err!=0)
	{
		printf("Error: redis_connect() error!\n");
		if(c != NULL )
			redis_disconnect(c);
		return -1;
	}
	else
	{
		printf("redis connected.\n\n");
	}
	
	
	/*insert*/
	ret = redis_insert(c, key, value, EX_TIME);
	if(ret < 0)
	{
		printf("Error: redis_insert() error!\n\n");
		/*redis_disconnect(c);
		return -1;*/
	}
	else
	{
		printf("\nredis_insert() success.\n");
	}
	

	/*update*/
	ret = redis_update(c, key, "value1update", EX_TIME);
	if(ret !=0 && ret!=NOT_FOUND)
	{
		printf("\nError: redis_update() error!\n");
		/*redis_disconnect(c);
		return -1;*/
	}
	else if(ret==NOT_FOUND)
	{
		printf("key is not found!\n");
	}
	else
	{
		printf("\nredis_update() success.\n\n");
	}

	
	/*select*/
	ret = redis_select(c, key, value);
	if(ret < 0 && ret!=NOT_FOUND)
	{
		printf("\nError: redis_select() error!\n");
		/*redis_disconnect(c);
		return -1;*/
	}
	else if(ret==NOT_FOUND)
	{
		printf("key is not found!\n");
	}
	else
	{
		printf("\nredis_select() success.\n");
		printf("value[%s]\n\n",value);
	}
	

	/*delete*/
	ret = redis_delete(c, key);
	if(ret < 0 && ret!=NOT_FOUND)
	{
		printf("\nError: redis_delete() error!\n");
		/*redis_disconnect(c);
		return -1;*/
	}
	else if(ret==NOT_FOUND)
	{
		printf("key is not found!\n");
	}
	else
	{
		printf("\nredis_delete() success.\n");
	}

	
	/*disconnect*/
	redis_disconnect(c);
	printf("\nredis disconnected.\n");
	
	return 0;
}