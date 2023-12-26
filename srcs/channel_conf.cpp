#include "./../headers/header.hpp"

void	setup_channel(t_server *serv, std::string name)
{
	for (int i = 1; i != NBR_CLIENTS - 1; i++)
	{
		if (serv->chan[i].here == 0)
		{
			serv->chan[i].name = name;
			serv->chan[i].topic = " ";
			serv->chan[i].key = " ";
			serv->chan[i].limit = 0;
			serv->chan[i].invite = false;
			serv->chan[i].topic_perm = true;
			break;
		}
	}
}

void	full_setup_channel(t_server *serv)
{
	serv->chan[0].here = 0;
	serv->chan[0].name = "general";
	serv->chan[0].topic = "Default channel of this server";
	serv->chan[0].key = " ";
	serv->chan[0].limit = 0;
	serv->chan[0].invite = false;
	serv->chan[0].topic_perm = true;
	for (int i = 1; i != NBR_CLIENTS - 1; i++)
	{
		serv->chan[i].here = 0;
		serv->chan[i].name = " ";
		serv->chan[i].topic = " ";
		serv->chan[i].key = " ";
		serv->chan[i].limit = 0;
		serv->chan[i].invite = false;
		serv->chan[i].topic_perm = true;
	}
}