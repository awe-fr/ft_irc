#include "./../headers/header.hpp"

int	check_password(t_server *serv, char *buff, int bytesread, int i)
{
	if (serv->client[i].password == false)
	{
		if (strncmp(buff, serv->password.c_str(), bytesread - 1) == 0 && bytesread - 1 > 0)
			serv->client[i].password = true;
		if (serv->client[i].password == true)
			return 1;
		if ((send(serv->fds[i].fd, "Please enter password : ", sizeof("Please enter password : "), 0)) == -1)
		{
			std::cerr << "Error : send failed" << std::endl;
			return 1;
		}
		if (strncmp(buff, serv->password.c_str(), bytesread - 1) == 0 && bytesread - 1 > 0)
		serv->client[i].password = true;
		return 1;
	}
	return 0;
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
            std::cout << "entrer detecter " << i << std::endl;
			std::cout << serv->client[i].name << " : ";
            if (bytesread == -1)
                std::cout << "recv -1" << std::endl;
            else if (bytesread == 0)
            {
                std::cout << "deconnection" << std::endl;
                serv->fds[i].fd = -1;
                serv->fds[i].events = 0;
                serv->client_co--;
            }
            else
            	std::cout << buff << std::endl;
        }
    }
	return 0;
}

int connection_ask(t_server *serv)
{
	if (serv->fds[0].revents & POLLIN)
    {
        serv->client_socket = accept(serv->server_socket, (struct sockaddr*)&serv->client_addr, &serv->client_addr_size);
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