#include "./../headers/header.hpp"

void	skibidi_activ(t_server *serv)
{
	if (serv->skibidi_bot == false)
		serv->skibidi_bot = true;
	else
		serv->skibidi_bot = false;
}

void	skibidi_on(t_server *serv, int i)
{
	if ((send(serv->fds[i].fd, "test\n", strlen("test\n"), 0)) == -1)
		std::cerr << "Error : send failed" << std::endl;
}