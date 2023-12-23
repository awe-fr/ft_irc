#include "./../headers/header.hpp"

std::string	extract_nick(char *buff, t_server *serv, int i)
{
	char tmp[40] = {0}; tmp[0] = '\0';
    std::string name;
    int z = 0; int y = 0;
    while(buff[z] != ' ')
        z++;
    z++;
    while(buff[z] != '\0' && y < 30)
        tmp[y++] = buff[z++];
    if (y >= 30)
    {
        if ((send(serv->fds[i].fd, "This nickname is too long\n", sizeof("This nickname is too long\n"), 0)) == -1)
		    std::cerr << "Error : send failed" << std::endl;
        name = " ";
		return name;
    }
    if (tmp[0] != '\0')
        name = tmp;
    else
        name = " ";
    return name;
}

void	change_nickname(t_server *serv, int i, std::string name)
{
	if(name == " ")
		return;
	serv->client[i].nickname = name;
	return;
}