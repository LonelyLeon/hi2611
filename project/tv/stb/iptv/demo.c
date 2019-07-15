#include "auth.h"

int main(int argc, char * argv[]) 
{
	Authenticator * auth;
	
	htk_init(NULL, NULL);
	auth = OTT_auth_init();

	htk_main();
	return 0;
}
