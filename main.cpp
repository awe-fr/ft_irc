#include "./headers/header.hpp"

int main(int ac, char **av)
{
	if (ac != 1)
	{
		std::cout << "Wrong arguments, please use './ircserv <port> <password>'" << std::endl;
		// return 1;
	}
	int i = 0;
	while(av[i] && av[i][0] != 't')
		i++;
	int serverSocket[NBR_CLIENTS]; 
    for (int s = 0; s < NBR_CLIENTS; s++)
    {
        serverSocket[s] = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket[s] == -1) {
            std::cerr << "Erreur lors de la création du socket" << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Configuration de l'adresse du serveur
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Écoute sur toutes les interfaces réseau
    serverAddress.sin_port = htons(3000); // Utilisez le port de votre choix

    // Liaison du socket à l'adresse et au port
    if (bind(serverSocket[0], (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Erreur lors de la liaison du socket à l'adresse et au port" << std::endl;
        for(int s = 0; s < NBR_CLIENTS; s++)
            close(serverSocket[s]);
        return EXIT_FAILURE;
    }

    // Attente des connexions entrantes
    if (listen(serverSocket[0], 10) == -1) {
        std::cerr << "Erreur lors de l'attente des connexions entrantes" << std::endl;
        for(int s = 0; s < NBR_CLIENTS; s++)
            close(serverSocket[s]);
        return EXIT_FAILURE;
    }

    struct pollfd fds[NBR_CLIENTS];
    for (int s = 0; s < NBR_CLIENTS; s++)
        {fds[s].fd = serverSocket[s];
        fds[s].events = POLLIN;}

    std::cout << "Attente des connexions entrantes..." << std::endl;

    // Boucle principale pour accepter les connexions
    int clientSocket = 0;
    int clientco = 0;
    while (1) {
        sockaddr_in clientAddress;
        socklen_t clientAddrSize = sizeof(clientAddress);
        int pollResult = poll(fds, clientco + 1, -1); 
        if (pollResult == -1)
        {
            std::cout << "poll -1" << std::endl;
            return 1;
        }
        else if (pollResult > 0)
        {
            for (int i = 1; i < 1; i++)
                if (fds[i].revents & POLLIN)
                    std::cout << "entrer detecter " << i << std::endl;

            if (fds[0].revents & POLLIN)
            {
                std::cout << "demande port 0" << std::endl;
                clientSocket = accept(serverSocket[0], (struct sockaddr*)&clientAddress, &clientAddrSize);
                if (clientSocket > 0){
                    std::cout << "connection" << std::endl;
                   //return 1;
                }
                if (clientSocket == -1)
                    std::cerr << "Erreur lors de l'acceptation de la connexion entrante" << std::endl;
            }
            else
                std::cout << "teps" << clientSocket << std::endl;
        }

        // // Accepter la connexion entrante
        // int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrSize);
        // if (clientSocket == -1) {
        //     std::cerr << "Erreur lors de l'acceptation de la connexion entrante" << std::endl;
        //     continue; // Ignorer et continuer à attendre la prochaine connexion
        // }

        // Fermer le socket client après le traitement
        std::cout << "set";
        //close(clientSocket);
    }

    // Fermer le socket du serveur (ce qui ne sera jamais atteint dans cet exemple)
    for(int s = 0; s < NBR_CLIENTS; s++)
        close(serverSocket[s]);

    return EXIT_SUCCESS;
}