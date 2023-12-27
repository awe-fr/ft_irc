#include "./../headers/header.hpp"

void	setup_client(t_server *serv)
{
	serv->client[serv->client_co - 1].id = serv->id_gen;
	serv->client[serv->client_co - 1].taken = true;
	serv->client[serv->client_co - 1].password = false;
	serv->client[serv->client_co - 1].channel = "check_pass";
	serv->client[serv->client_co - 1].nickname = "none";
	serv->client[serv->client_co - 1].username = "none";
	serv->client[serv->client_co - 1].op = false;
	serv->client[serv->client_co - 1].in_wait = "none";
	serv->client[serv->client_co - 1].full_msg[0] = '\0';
	serv->id_gen++;
}

void	full_setup_client(t_server *serv)
{
	for (int i = 1; i != NBR_CLIENTS - 1; i++)
	{
		serv->client[i].id = i;
		serv->client[i].taken = false;
		serv->client[i].password = false;
		serv->client[i].channel = "check_pass";
		serv->client[i].nickname = "none";
		serv->client[i].username = "none";
		serv->client[i].op = false;
		serv->client[i].in_wait = "none";
		serv->client[i].full_msg[0] = '\0';
	}
}