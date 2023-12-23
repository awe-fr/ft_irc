#include "./../headers/header.hpp"

std::string extract_msg(char *buff, t_server *serv, int i)
{
    char tmp[1024] = {0}; tmp[0] = '\0';
    std::string msg;
    int z = 0; int y = 0;
    while(buff[z] != '\0' && buff[z] != '#' && z < 1000)
        z++;
    z++;
    while(buff[z] != '\0' && buff[z] != ' ' && z < 1000)
        z++;
    while(buff[z] != '\0' && buff[z] == ' ' && z < 1000)
        z++;
    while(buff[z] != '\0' && z < 1000)
        tmp[y++] = buff[z++]; 
    if (z >= 1000)
    {
        if ((send(serv->fds[i].fd, "Message too long\n", sizeof("Message too long\n"), 0)) == -1)
		    std::cerr << "Error : send failed" << std::endl;
        msg = " ";
		return msg;
    }
    if (tmp[0] != '\0')
        msg = tmp;
    else
        msg = " ";
    std::cout << msg << "|" << tmp << "|" << buff << std::endl;
    return msg;
}

std::string find_username(char *buff, t_server *serv, int i)
{
    char tmp[50] = {0}; tmp[0] = '\0';
    std::string name;
    int z = 0; int y = 0;
    while(buff[z] != ' ')
        z++;
    z++;
    while(buff[z] != '\0' && buff[z] != '#' && y < 40)
        tmp[y++] = buff[z++];
    while(buff[z] != '\0' && buff[z] != ' ' && y < 40)
        tmp[y++] = buff[z++];
    if (y >= 40)
    {
        if ((send(serv->fds[i].fd, "This username can't possibly exist\n", sizeof("This username can't possibly exist\n"), 0)) == -1)
		    std::cerr << "Error : send failed" << std::endl;
        name = "noname";
		return name;
    }
    if (tmp[0] != '\0')
        name = tmp;
    else
        name = "noname";
    return name;
}