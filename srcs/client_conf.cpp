#include "./../headers/header.hpp"

void	setup_client(t_server *serv)
{
	serv->client[serv->client_co - 1].id = serv->client_co - 1;
	serv->client[serv->client_co - 1].taken = true;
	serv->client[serv->client_co - 1].password = false;
	serv->client[serv->client_co - 1].channel = "check_pass";
	serv->client[serv->client_co - 1].name = "none";
}

void	full_setup_client(t_server *serv)
{
	for (int i = 1; i != NBR_CLIENTS - 1; i++)
	{
		serv->client[i].id = i;
		serv->client[i].taken = false;
		serv->client[i].password = false;
		serv->client[i].channel = "check_pass";
		serv->client[i].name = "none";
	}
}