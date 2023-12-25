#include "./../headers/header.hpp"

std::string get_channel_name(char *buff, t_server *serv, int i)
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
        if ((send(serv->fds[i].fd, "This channel name is too long\n", sizeof("This channel name is too long\n"), 0)) == -1)
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

void    create_channel(t_server *serv, int i, std::string ch_name)
{
    if (ch_name == " ")
        return;
    for(int y = 0; y != NBR_CLIENTS - 1; y++)
    {
        if (serv->chan[y].name == ch_name && serv->chan[y].here >= 1)
        {
            std::cout << serv->chan[y].here << std::endl;
            if ((send(serv->fds[i].fd, "This channel already exist\n", sizeof("This channel already exist\n"), 0)) == -1)
		        std::cerr << "Error : send failed" << std::endl;
            return;
        }
    }
    setup_channel(serv, ch_name);
    change_count(serv, serv->client[i].channel, ch_name);
    serv->client[i].channel = ch_name;
    serv->client[i].op = true;
    std::string to_print = "["; to_print += ch_name; to_print += "]\n";
    if ((send(serv->fds[i].fd, to_print.c_str(), strlen(to_print.c_str()), 0)) == -1)
		std::cerr << "Error : send failed" << std::endl;
}