#include "./../headers/header.hpp"

int	server_socket_conf(t_server *serv)
{
	if ((serv->server_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) == -1) 
    {
        std::cerr << "Error : socket creation failed" << std::endl;
        return 1;
    }
    int opt = 1;
    if ((setsockopt(serv->server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) == -1 )
    {
        std::cerr << "Error : port already used" << std::endl;
        return 1;
    }
	return 0;
}

int	server_addr_conf(t_server *serv, char *port)
{
	serv->server_addr.sin_family = AF_INET;
    serv->server_addr.sin_addr.s_addr = INADDR_ANY;
    serv->server_addr.sin_port = htons(atoi(port));
    if (bind(serv->server_socket, (struct sockaddr*)&serv->server_addr, sizeof(serv->server_addr)) == -1)
    {
        std::cerr << "Error : binding failed" << std::endl;
        close(serv->server_socket);
        return 1;
    }
	return 0;
}

int	server_fd_conf(t_server *serv)
{
	if (listen(serv->server_socket, 10) == -1)
    {
        std::cerr << "Error : bad waiting connection" << std::endl;
        close(serv->server_socket);
        return 1;
    }
    serv->fds[0].fd = serv->server_socket;
    serv->fds[0].events = POLLIN;
    for (int s = 1; s < NBR_CLIENTS; s++){
        serv->fds[s].fd = -1;}
	return 0;
}

int	server_configuration(t_server *serv, char *port, char *pwd)
{
    if ((server_socket_conf(serv)) == 1)
		return 1;
    if ((server_addr_conf(serv, port)) == 1)
		return 1;
    if ((server_fd_conf(serv)) == 1)
		return 1;
	serv->client_co = 1;
    serv->id_gen = 1;
	serv->password = pwd;
    serv->client_addr_size = sizeof(serv->client_addr);
    serv->skibidi_bot = false;
    return 0;
}