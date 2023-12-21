#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

#define NBR_CLIENTS 10

typedef struct s_client {
	int id;
	bool taken;
	bool password;
	std::string channel;
	std::string name;
}	t_client;

typedef struct s_server {
	int client_co;
	int server_socket;
	int client_socket;
	std::string password;
	sockaddr_in server_addr;
	sockaddr_in client_addr;
	socklen_t client_addr_size;
	pollfd fds[NBR_CLIENTS];
	t_client client[NBR_CLIENTS + 1];
}	t_server;


// server config
int	server_configuration(t_server *serv, char *port, char *pwd);
int	server_socket_conf(t_server *serv);
int	server_addr_conf(t_server *serv, char *port);
int	server_fd_conf(t_server *serv);

// client config
void	full_setup_client(t_server *serv);
void	setup_client(t_server *serv);

// poll loop
int poll_loop(t_server *serv);
int info_recv(t_server *serv);
int connection_ask(t_server *serv);

// info check
int	check_password(t_server *serv, char *buff, int bytesread, int i);
