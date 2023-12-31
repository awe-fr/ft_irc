#include "./../headers/header.hpp"

void    disconnect(t_server *serv, int i)
{
    std::string to_send = serv->client[i].username; to_send += " disconnect\n";
    std::cout << "disconnect" << std::endl;
    for (int y = 1; y != NBR_CLIENTS - 1; y++)
    {
        if (serv->client[i].channel == serv->chan[y].name)
        {
            serv->chan[y].here--;
            break;
        }
    }
    for (int y = 1; y != NBR_CLIENTS - 1; y++)
    {
        if (serv->client[i].channel == serv->client[y].channel)
        {
            if ((send(serv->fds[y].fd, to_send.c_str(), strlen(to_send.c_str()), 0)) == -1)
		        std::cerr << "Error : send failed" << std::endl;
        }
    }
    while(i < NBR_CLIENTS - 2 && serv->fds[i + 1].fd != -1)
    {
        serv->fds[i].fd = serv->fds[i + 1].fd; 
        serv->fds[i + 1].fd = -1;
        serv->client[i] = serv->client[i + 1];
        i++;
    }
    close(serv->fds[i].fd);
    serv->fds[i].fd = -1;
    serv->fds[i].events = 0;
    serv->client[i].taken = false;
    serv->client_co--;
}

void    choose(t_server *serv, int i, char *buff)
{
    if (strlen(buff) >= 1 && strlen(buff) <= 1024)
    {
        if (serv->client[i].in_wait != "none")
        {
            if (strncmp(serv->client[i].in_wait.c_str(), "password ", 9) == 0)
                check_pass_chan(serv, i, buff);
            if (strncmp(serv->client[i].in_wait.c_str(), "invite ", 7) == 0)
                ok_to_join(serv, i, buff);
            serv->client[i].full_msg[0] = '\0';
            return;
        }
        if(strncmp(buff, "!", 1) == 0)
        {
            if(strncmp(buff, "!mp ", 4) == 0)
                send_msg(serv, i, extract_msg(buff, serv, i), find_username(buff, serv, i));
            else if (strncmp(buff, "!rename ", 8) == 0)
                change_nickname(serv, i, extract_nick(buff, serv, i));
            else if (strncmp(buff, "!topic", 6) == 0)
                topic_asked(serv, i, get_new_topic(buff, serv, i));
            else if (strncmp(buff, "!create ", 8) == 0)
                create_channel(serv, i, get_channel_name(buff, serv, i));
            else if (strncmp(buff, "!join ", 6) == 0)
                join(serv, i, get_channel_name(buff, serv, i));
            else if (strncmp(buff, "!kick ", 6) == 0)
                kick(serv, i, find_username(buff, serv, i));
            else if (strncmp(buff, "!invite ", 8) == 0)
                invite(serv, i, find_username(buff, serv, i));
            else if (strncmp(buff, "!MODE-l", 7) == 0)
                limit(serv, i, buff);
            else if (strncmp(buff, "!MODE-t", 7) == 0)
                topic_restriction(serv, i);
            else if (strncmp(buff, "!MODE-i", 7) == 0)
                change_invite(serv, i);
            else if (strncmp(buff, "!MODE-k", 7) == 0)
                change_pass(serv, i, buff);
            else if (strncmp(buff, "!MODE-o", 7) == 0)
                give_op(serv, i, find_username(buff, serv, i));
            else if (strncmp(buff, "!SKIBIDI", 8) == 0)
                skibidi_activ(serv, i);
            else if (strncmp(buff, "!help", 5) == 0)
                help(serv, i);
            else
            {
                if ((send(serv->fds[i].fd, "Command not found, !help\n", strlen("Command not found, !help\n"), 0)) == -1)
		            std::cerr << "Error : send failed" << std::endl;
            }
            serv->client[i].full_msg[0] = '\0';
            return;
        }
		std::cout << serv->client[i].username << " : ";
        std::cout << buff << std::endl;
        general_msg(serv, i, buff);
        serv->client[i].full_msg[0] = '\0';
    }
    else if (strlen(buff) > 1024)
    {
        if ((send(serv->fds[i].fd, "Character limit is 1024\n", strlen("Character limit is 1024\n"), 0)) == -1)
		    std::cerr << "Error : send failed" << std::endl;
        serv->client[i].full_msg[0] = '\0';
    }
}

int info_recv(t_server *serv)
{
	for (int i = 1; i < serv->client_co; i++)
	{
        if (serv->fds[i].revents & POLLIN)
		{
            char buff[2048] = {0};
            int bytesread = recv(serv->fds[i].fd, buff, sizeof(buff), 0);
			if (check_password(serv, buff, bytesread, i) == 1)
				return 0;
            if (serv->client[i].username == "none")
            {
				if (setusername(serv, i, buff) == 1)
                    return 1;
                else
                    return 0;
            }
            std::cout << "entrer detecter " << i << bytesread << std::endl;
            if (bytesread == -1)
                std::cout << "recv -1" << std::endl;
            else if (bytesread == 0)
            {
                disconnect(serv, i);
                return 0;
            }
            else
            {
                if (serv->client[i].full_msg[0] != '\0')
                    serv->client[i].full_msg += buff;
                else 
                    serv->client[i].full_msg = buff;
                if (serv->client[i].full_msg[strlen(serv->client[i].full_msg.c_str()) - 1] != 10)
                    return 0;
                serv->client[i].full_msg[strlen(serv->client[i].full_msg.c_str()) - 1] = '\0';
                choose(serv, i, (char *)serv->client[i].full_msg.c_str());
            }
        }
    }
	return 0;
}

int connection_ask(t_server *serv)
{
	if (serv->fds[0].revents & POLLIN)
    {
        serv->client_socket = accept(serv->server_socket, (struct sockaddr*)&serv->client_addr, &serv->client_addr_size);
        if (serv->client_co >= NBR_CLIENTS - 2)
        {
            std::cerr << "Max capacity reach" << std::endl;
            return 1;
        }
        if (serv->client_socket > 0)
		{
            std::cout << "connection" << std::endl;
            for (int i = 1; i < serv->client_co + 1; i++)
            {
                if(serv->fds[i].fd == -1)
				{
                    serv->fds[i].fd = serv->client_socket;
                    serv->fds[i].events = POLLIN;
                    serv->client_co++;
					setup_client(serv);
					if ((send(serv->fds[i].fd, "Please enter password : ", sizeof("Please enter password : "), 0)) == -1)
					{
						std::cerr << "Error : send failed" << std::endl;
						return 1;
					}
                    break;
				}
            }
        }
        if (serv->client_socket == -1)
            std::cerr << "Error : connection not accepted" << std::endl;
    }
	return 0;
}

int poll_loop(t_server *serv)
{
	while (1) {
        int pollResult = poll(serv->fds, serv->client_co, -1); 
        if (pollResult == -1)
        {
            std::cerr << "Error : poll -1" << std::endl;
            return 1;
        }
        else if (pollResult > 0)
        {
			if ((info_recv(serv)) == 1)
				return 1;
			if ((connection_ask(serv)) == 1)
				return 1;
        }
    }
	return 0;
}