#include "./../headers/header.hpp"

int getlimit(char *buff, t_server *serv, int i)
{
	char tmp[10] = {0}; tmp[0] = '\0';
	int z = 0; int y = 0;
	int val = 0;
	while(buff[z] != ' ' && buff[z] != '\0')
		z++;
	if (buff[z] == '\0')
		return -2;
	z++;
	while(buff[z] != '\0' && y <= 5)
	{
		if (buff[z] < '0' || buff[z] > '9')
		{
			if ((send(serv->fds[i].fd, "Bad input\n", strlen("Bad input\n"), 0)) == -1)
				std::cerr << "Error : send failed" << std::endl;
			return -1;
		}
		tmp[y++] = buff[z++];
	}
	if (y > 0)
		val = atoi(tmp);
	else
		val = -2;
	if (val > 100)
	{
		if ((send(serv->fds[i].fd, "Limit too high\n", strlen("Limit too high\n"), 0)) == -1)
			std::cerr << "Error : send failed" << std::endl;
		return -1;
	}
	return val;
}

void	limit(t_server *serv, int i, char *buff)
{
	std::string to_send = "[server] This channel limit is ";
	int lim = getlimit(buff, serv, i);
	int pres = 0;
	char *tp = ft_itoa(lim);
	for (int t = 0; t != NBR_CLIENTS -1; t++)
	{
		if (serv->client[i].channel == serv->chan[t].name)
		{
			pres = t;
			break;
		}
	}
	if (lim == -1)
		{free(tp); return;}
	else if (lim == -2 && serv->chan[pres].limit == 0)
	{
		to_send = "[server] This channel don't have any limit\n";
		if ((send(serv->fds[i].fd, to_send.c_str(), strlen(to_send.c_str()), 0)) == -1)
			std::cerr << "Error : send failed" << std::endl;
		free(tp);
		return;
	}
	else if (lim == -2)
	{
		free(tp) ; tp = ft_itoa(serv->chan[pres].limit);
		to_send += tp; to_send += "\n";
		if ((send(serv->fds[i].fd, to_send.c_str(), strlen(to_send.c_str()), 0)) == -1)
			std::cerr << "Error : send failed" << std::endl;
		free(tp);
		return;
	}
	else if (serv->client[i].op == false) 
	{
		if ((send(serv->fds[i].fd, "Your not operator on this channel\n", strlen("Your not operator on this channel\n"), 0)) == -1)
			std::cerr << "Error : send failed" << std::endl;
		free(tp);
		return;
	}
	serv->chan[pres].limit = lim;
	to_send = "[server] Now this channel limit is "; to_send += tp; to_send += "\n";
	if ((send(serv->fds[i].fd, to_send.c_str(), strlen(to_send.c_str()), 0)) == -1)
		std::cerr << "Error : send failed" << std::endl;
	free(tp);
}