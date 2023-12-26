#include "./../headers/header.hpp"

void	change_pass(t_server *serv, int i, char *buff)
{
	if(serv->client[i].op == false)
	{
		if ((send(serv->fds[i].fd, "Your not operator on this channel\n", strlen("Your not operator on this channel\n"), 0)) == -1)
			std::cerr << "Error : send failed" << std::endl;
		return;
	}
	std::string pwd = get_pwd(buff, serv, i);
	if (pwd == "\n")
		return;
	for (int y = 0; y != NBR_CLIENTS - 1; y++)
	{
		if (serv->chan[y].name == serv->client[i].channel)
		{
			serv->chan[y].key = pwd;
			if ((send(serv->fds[i].fd, "[server] Password changed\n", strlen("[server] Password changed\n"), 0)) == -1)
				std::cerr << "Error : send failed" << std::endl;
			return;
		}
	}
}

std::string	get_pwd(char *buff, t_server *serv, int i)
{
	char tmp[50] = {0}; tmp[0] = '\0';
    std::string top;
    int z = 0; int y = 0;
    while(buff[z] != '\0'&& buff[z] != ' ')
        z++;
    z++;
    while(buff[z] != '\0' && y < 30)
        tmp[y++] = buff[z++];
    if (y >= 30)
    {
        if ((send(serv->fds[i].fd, "Password too long\n", sizeof("Password too long\n"), 0)) == -1)
		    std::cerr << "Error : send failed" << std::endl;
        top = "\n";
		return top;
    }
    if (tmp[0] != '\0')
        top = tmp;
    else
        top = "\n";
    return top;
}

int	check_password(t_server *serv, char *buff, int bytesread, int i)
{
	if (serv->client[i].password == true)
		return 0;
	if (strncmp(buff, serv->password.c_str(), bytesread - 1) == 0 && bytesread - 1 > 0)
		serv->client[i].password = true;
	if (serv->client[i].password == true)
	{
		if ((send(serv->fds[i].fd, "Please enter username : ", sizeof("Please enter username : "), 0)) == -1)
			std::cerr << "Error : send failed" << std::endl;
		return 1;
	}
	if ((send(serv->fds[i].fd, "Please enter password : ", sizeof("Please enter password : "), 0)) == -1)
		std::cerr << "Error : send failed" << std::endl;
	return 1;
}