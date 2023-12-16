#include "./headers/header.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Wrong arguments, please use './ircserv <port> <password>'" << std::endl;
		return 1;
	}
	int i = 0;
	while(av[i] && av[i][0] != 't')
		i++;
}
