#include "./../headers/header.hpp"

void	change_invite(t_server *serv, int i)
{
	if(serv->client[i].op == false)
	{
		if ((send(serv->fds[i].fd, "Your not operator on this channel\n", strlen("Your not operator on this channel\n"), 0)) == -1)
			std::cerr << "Error : send failed" << std::endl;
		return;
	}
	for (int y = 0; y != NBR_CLIENTS - 1; y++)
	{
		if (serv->chan[y].name == serv->client[i].channel)
		{
			if (serv->chan[y].invite == true){serv->chan[y].invite = false;}
			else if (serv->chan[y].invite == false){serv->chan[y].invite = true;}
			if ((send(serv->fds[i].fd, "[server] Topic invite only changed\n", strlen("[server] Topic invite only changed\n"), 0)) == -1)
				std::cerr << "Error : send failed" << std::endl;
			return;
		}
	}
}

void	invite(t_server *serv, int i, std::string name)
{
	std::string chan_inv = " ";
	for (int n = 0; n != NBR_CLIENTS - 1; n++)
	{
		if (serv->client[i].channel == serv->chan[n].name)
		{
			chan_inv = serv->chan[n].name;
			break;
		}
	}
	for (int y = 0; y != NBR_CLIENTS - 1; y++)
	{
		if (serv->client[y].username == name)
		{
			if ((send(serv->fds[y].fd, "[server] You have been invited to join a channel\n[y] or [n]\n", strlen("[server] You have been invited to join a channel\n[y] or [n]\n"), 0)) == -1)
				std::cerr << "Error : send failed" << std::endl;
			serv->client[y].in_wait = "invite "; serv->client[y].in_wait += chan_inv;
			break;
		}
	}
}