#include "./../headers/header.hpp"

void    send_msg(t_server *serv, int i, std::string msg, std::string name)
{
    if (name == "noname" || msg == " ")
        return;
    int y = 1;
    while(y < NBR_CLIENTS - 2 && serv->client[y].username != name)
        y++;
    if(y == i)
        return;
    std::string to_send = serv->client[i].username; to_send += " : "; to_send += msg; to_send += "\n";
    if ((send(serv->fds[y].fd, to_send.c_str(), strlen(to_send.c_str()), 0)) == -1)
	{
		std::cerr << "Error : send failed" << std::endl;
		return;
	}
    return;
}

void    general_msg(t_server *serv, int i, char *buff)
{
    std::string to_send = "["; to_send += serv->client[i].channel; to_send += "] ";
    if(serv->client[i].nickname != "none")
        {to_send += serv->client[i].nickname; to_send += " : ";}
    else
        {to_send += serv->client[i].username; to_send += " : ";}
    to_send += buff; to_send += "\n";
    for (int y = 1; y != serv->client_co; y++)
    {
        if (serv->client[i].channel == serv->client[y].channel && i != y)
        {
            if ((send(serv->fds[y].fd, to_send.c_str(), strlen(to_send.c_str()), 0)) == -1)
		        std::cerr << "Error : send failed" << std::endl;
            if (serv->skibidi_bot == true)
                skibidi_on(serv, y);
        }
    }
}