#include "./../headers/header.hpp"

void    join(t_server *serv, int i, std::string chan_name)
{
	for (int y = 0; y != NBR_CLIENTS - 1; y++)
	{
		if (chan_name == serv->chan[y].name)
		{
			if (serv->chan[y].key != " ")
			{
				if ((send(serv->fds[i].fd, "Please enter the password : ", strlen("Please enter the password : "), 0)) == -1)
		        	std::cerr << "Error : send failed" << std::endl;
				serv->client[i].in_wait = "password "; serv->client[i].in_wait += serv->chan[y].name;
				return;
			}
			if (serv->chan[y].invite == true)
			{
				if ((send(serv->fds[i].fd, "This channel is only on invitation\n", strlen("This channel is only on invitation\n"), 0)) == -1)
		        	std::cerr << "Error : send failed" << std::endl;
				return;
			}
			if (serv->chan[y].limit <= serv->chan[y].here && serv->chan[y].limit != 0)
			{
				if ((send(serv->fds[i].fd, "This channel is full\n", strlen("This channel is full\n"), 0)) == -1)
		        	std::cerr << "Error : send failed" << std::endl;
				return;
			}
			if (serv->chan[y].here == 0 && serv->chan[y].name != "general")
			{
				if ((send(serv->fds[i].fd, "This channel dosen't exist\n", strlen("This channel dosen't exist\n"), 0)) == -1)
		        	std::cerr << "Error : send failed" << std::endl;
				return;
			}
			std::string chan_print = "["; chan_print += serv->chan[y].name; chan_print += "]\n";
			if ((send(serv->fds[i].fd, chan_print.c_str(), strlen(chan_print.c_str()), 0)) == -1)
		        	std::cerr << "Error : send failed" << std::endl;
			change_count(serv, serv->client[i].channel, chan_name);
			serv->client[i].channel = chan_name;
			if (serv->client[i].op == true)
				serv->client[i].op = false;
			return;
		}
	}
	if ((send(serv->fds[i].fd, "This channel dosen't exist\n", strlen("This channel dosen't exist\n"), 0)) == -1)
		std::cerr << "Error : send failed" << std::endl;
}

void	check_pass_chan(t_server *serv, int i, char *buff)
{
	std::string want_to = get_channel_name((char *)serv->client[i].in_wait.c_str(), serv, i);
	std::string pass = buff;
	for (int y = 0; y != NBR_CLIENTS - 1; y++)
	{
		if (want_to == serv->chan[y].name)
		{
			std::string chan_print = "["; chan_print += serv->chan[y].name; chan_print += "]\n";
			if (pass == serv->chan[y].key)
			{
				if ((send(serv->fds[i].fd, chan_print.c_str(), strlen(chan_print.c_str()), 0)) == -1)
		        	std::cerr << "Error : send failed" << std::endl;
				change_count(serv, serv->client[i].channel, want_to);
				serv->client[i].channel = serv->chan[y].name;
				break;
			}
		}
	}
	serv->client[i].in_wait = "none";
}

void	ok_to_join(t_server *serv, int i, char *buff)
{
	if(buff[0] != 'y')
	{
		serv->client[i].in_wait = "none";
		return;
	}
	std::string want_to = get_channel_name((char *)serv->client[i].in_wait.c_str(), serv, i);
	std::string chan_print = "["; chan_print += want_to; chan_print += "]\n";
	for (int y = 0; y != NBR_CLIENTS - 1; y++)
	{
		if (serv->chan[y].name == want_to)
		{
			if ((send(serv->fds[i].fd, chan_print.c_str(), strlen(chan_print.c_str()), 0)) == -1)
		        std::cerr << "Error : send failed" << std::endl;
			change_count(serv, serv->client[i].channel, want_to);
			serv->client[i].channel = serv->chan[y].name;
			break;
		}
	}
	serv->client[i].in_wait = "none";
}