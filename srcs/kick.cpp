#include "./../headers/header.hpp"

void	kick(t_server *serv, int i, std::string name)
{
	if(serv->client[i].op == false)
	{
		if ((send(serv->fds[i].fd, "Your not operator on this channel\n", strlen("Your not operator on this channel\n"), 0)) == -1)
			std::cerr << "Error : send failed" << std::endl;
		return;
	}
	for (int y = 0; y != NBR_CLIENTS - 1; y++)
	{
		if (serv->client[y].username == name)
		{
			change_count(serv, serv->client[y].channel, "general");
			serv->client[y].channel = "general";
			if ((send(serv->fds[y].fd, "[server] You've been kicked from this channel\n[general]\n", strlen("[server] You've been kicked from this channel\n[general]\n"), 0)) == -1)
				std::cerr << "Error : send failed" << std::endl;
			return;
		}
	}
}