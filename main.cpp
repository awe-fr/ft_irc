#include "./headers/header.hpp"

void    signalhandel(int signal)
{
    std::cout << signal << std::endl;
}

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Wrong arguments, please use './ircserv <port> <password>'" << std::endl;
		return 1;
	}
    if (strlen(av[2]) < 1)
    {
        std::cerr << "Please entre a valid password" << std::endl;
        return 1;
    }
    srand(time(NULL));
    t_server serv;
    if (server_configuration(&serv, av[1], av[2 ]) == 1)
        return 1;
    full_setup_client(&serv);
    full_setup_channel(&serv);
    signal(SIGINT, signalhandel);
    std::cout << "Waiting connection..." << std::endl;
    if (poll_loop(&serv) == 1)
    {
        close(serv.server_socket);
        return 1;
    }
    close(serv.server_socket);
    return 0;
}