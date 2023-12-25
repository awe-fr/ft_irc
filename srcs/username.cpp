#include "./../headers/header.hpp"

int setusername(t_server *serv, int i, char *buff)
{
    if (strlen(buff) - 1 >= 21)
    {
        if ((send(serv->fds[i].fd, "username too long\nPlease enter username : ", sizeof("username too long\nPlease enter username : "), 0)) == -1)
	    {
		    std::cerr << "Error : send failed" << std::endl;
		    return 1;
	    }
        return 0;
    }
    buff[strlen(buff) - 1] = '\0';
    serv->client[i].username = buff;
    serv->client[i].username += "#";
    char *tmp = ft_itoa(serv->client[i].id);
    serv->client[i].username += tmp;
    free(tmp);
    if ((send(serv->fds[i].fd, "now your username is : ", sizeof("now your username is : "), 0)) == -1)
	{
		std::cerr << "Error : send failed" << std::endl;
		return 1;
	}
    if ((send(serv->fds[i].fd, serv->client[i].username.c_str(), strlen(serv->client[i].username.c_str()), 0)) == -1)
	{
		std::cerr << "Error : send failed" << std::endl;
		return 1;
	}
    if ((send(serv->fds[i].fd, "\n", sizeof("\n"), 0)) == -1)
	{
		std::cerr << "Error : send failed" << std::endl;
		return 1;
	}
    if ((send(serv->fds[i].fd, "[general]\n", sizeof("[general]\n"), 0)) == -1)
	{
		std::cerr << "Error : send failed" << std::endl;
		return 1;
	}
    serv->client[i].channel = "general";
    return 0;
}