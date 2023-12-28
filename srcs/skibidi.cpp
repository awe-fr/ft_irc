#include "./../headers/header.hpp"

void	skibidi_activ(t_server *serv, int i)
{
	if (serv->client[i].op == false)
	{
		if ((send(serv->fds[i].fd, "Your not operator on this channel\n", strlen("Your not operator on this channel\n"), 0)) == -1)
			std::cerr << "Error : send failed" << std::endl;
		return;
	}
	int num;
	for (int y = 0; y != NBR_CLIENTS - 1; y++)
	{
		if (serv->client[i].channel == serv->chan[y].name)
		{
			if (serv->chan[y].skibidi_bot == false)
				serv->chan[y].skibidi_bot = true;
			else
				serv->chan[y].skibidi_bot = false;
			num = y;
			break;
		}
	}
	for (int y = 1; y != NBR_CLIENTS - 1; y++)
    {
        if (serv->client[i].channel == serv->client[y].channel)
        {
			if (serv->chan[num].skibidi_bot == true)
			{
            	if ((send(serv->fds[y].fd, "Skibidi get ready\n", strlen("Skibidi get ready\n"), 0)) == -1)
		        std::cerr << "Error : send failed" << std::endl;
			}
			else
			{
				if ((send(serv->fds[y].fd, "Skibidi fled\n", strlen("Skibidi fled\n"), 0)) == -1)
		        std::cerr << "Error : send failed" << std::endl;
			}
        }
    }
}

void	skibidi_on(t_server *serv, int i)
{
	int r = rand()%3;
	std::string to_send = "["; to_send += serv->client[i].channel; to_send += "]";
	to_send += " skibidi-bot : ";
	if (r == 0)
		to_send += "Skibidi Dop Dop Dop Yes Yes\n";
	else if (r == 1)
		to_send += "BABA BOEYY\n";
	else
		to_send += "Skibidi toilet\n";
	for (int y = 1; y != serv->client_co; y++)
    {
        if (serv->client[i].channel == serv->client[y].channel)
        {
            if ((send(serv->fds[y].fd, to_send.c_str(), strlen(to_send.c_str()), 0)) == -1)
		        std::cerr << "Error : send failed" << std::endl;
        }
    }
}