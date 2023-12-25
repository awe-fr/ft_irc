#include "./../headers/header.hpp"

void    disconnect(t_server *serv, int i)
{
    std::cout << "deconnection" << std::endl;
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

int info_recv(t_server *serv)
{
	for (int i = 1; i < serv->client_co; i++)
	{
        if (serv->fds[i].revents & POLLIN)
		{
            char buff[1024] = {0};
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
            std::cout << "entrer detecter " << i << std::endl;
            if (bytesread == -1)
                std::cout << "recv -1" << std::endl;
            else if (bytesread == 0)
            {
                disconnect(serv, i);
                return 0;
            }
            else
            {
                buff[strlen(buff) - 1] = '\0';
                if (strlen(buff) >= 1)
                {
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
                        return 0;
                    }
                    if (serv->client[i].in_wait != "none")
                    {
                        if (strncmp(buff, "password ", 9) == 0)
                            check_pass_chan(serv, i, buff);
                        // if (strncmp(buff, "invite ", 7) == 0)
                        //     ok_to_join(serv, i, buff);
                    }
			        std::cout << serv->client[i].username << " : ";
            	    std::cout << buff << std::endl;
                    general_msg(serv, i, buff);
                }
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