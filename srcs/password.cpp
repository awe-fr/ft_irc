#include "./../headers/header.hpp"

int	check_password(t_server *serv, char *buff, int bytesread, int i)
{
	if (serv->client[i].password == false)
	{
		if (strncmp(buff, serv->password.c_str(), bytesread - 1) == 0 && bytesread - 1 > 0)
        	serv->client[i].password = true;
		if (serv->client[i].password == true)
        {
            if ((send(serv->fds[i].fd, "Please enter username : ", sizeof("Please enter username : "), 0)) == -1)
		    {
			    std::cerr << "Error : send failed" << std::endl;
			    return 1;
		    }
			return 1;
        }
		if ((send(serv->fds[i].fd, "Please enter password : ", sizeof("Please enter password : "), 0)) == -1)
		{
			std::cerr << "Error : send failed" << std::endl;
			return 1;
		}
		return 1;
	}
	return 0;
}