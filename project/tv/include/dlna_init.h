#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include "dlna.h"
#include "player_api.h"

dlna_t *  DLNA_Init (HI_DLNA_MODE mode, PlayerControl * pc);
int DLNA_Run(dlna_t * dlna);
void DLNA_Uninit(dlna_t * dlna);
void DLNA_Set_friendly_name(char * name);
void DLNA_Set_interface(char * name);
void DLNA_Set_model_name(char * name);

char * UpnpGetServerIpAddress (dlna_t *dlna);
void add_channel_list(dlna_t * dlna, int ch_num, char * ch_name, char * url);
void free_channel_list(dlna_t * dlna);
