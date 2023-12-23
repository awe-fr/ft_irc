#include "./../headers/header.hpp"

void	setup_channel(t_server *serv, int i, std::string name)
{
	if (name == " ")
	{
		if ((send(serv->fds[i].fd, "Bad name\n", sizeof("Bad name\n"), 0)) == -1)
		{
			std::cerr << "Error : send failed" << std::endl;
			return;
		}
	}
	for (int i = 1; i != NBR_CLIENTS - 1; i++)
	{
		if (serv->chan[i].here == 0)
		{
			serv->chan[i].here++;
			serv->chan[i].name = name;
			serv->chan[i].topic = " ";
			serv->chan[i].key = " ";
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
	for (int i = 1; i != NBR_CLIENTS - 1; i++)
	{
		serv->chan[i].here = 0;
		serv->chan[i].name = " ";
		serv->chan[i].topic = " ";
		serv->chan[i].key = " ";
	}
}