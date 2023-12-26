#include "./../headers/header.hpp"

void    give_op(t_server *serv, int i, std::string name)
{
    if (serv->client[i].op == false)
    {
        if ((send(serv->fds[i].fd, "Your not operator on this channel\n", strlen("Your not operator on this channel\n"), 0)) == -1)
			std::cerr << "Error : send failed" << std::endl;
        return;
    }
    for (int y = 0; y != NBR_CLIENTS - 1; y++)
    {
        if (serv->client[y].username == name && serv->client[y].channel == serv->client[i].channel)
        {
            if ((send(serv->fds[y].fd, "[server] Now you are operator of this channel\n", strlen("[server] Now you are operator of this channel\n"), 0)) == -1)
			    std::cerr << "Error : send failed" << std::endl;
            serv->client[y].op = true;
            return;
        }
    }
}