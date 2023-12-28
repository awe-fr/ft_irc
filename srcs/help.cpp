#include "./../headers/header.hpp"

void	help(t_server *serv, int i)
{
	std::string prompt;
	prompt = "    -help (give you all the command)\n";
	prompt += "    -mp <username> <msg> (send a private message)\n";
	prompt += "    -rename <nickname> (change your nickname)\n";
	prompt += "    -topic (<new topic>) (see or change the topic)\n";
	prompt += "    -create <channel name> (create a new channel)\n";
	prompt += "    -join <channel name> (join a channel)\n";
	prompt += "    -kick <username> (kick someone from the channel)\n";
	prompt += "    -invite <username> (invite a user in your channel)\n";
	prompt += "    -MODE-l <new limit> (change limit of your channel, 0 = unlimited)\n";
	prompt += "    -MODE-t (change topic restriction)\n";
	prompt += "    -MODE-i (change invite only parameter)\n";
	prompt += "    -MODE-k <new password> (set a password for the channel, \" \" = no password)\n";
	prompt += "    -MODE-o <username> (give operator right to someone)\n";
	prompt += "    -SKIBIDI (:0)\n";
	if ((send(serv->fds[i].fd, prompt.c_str(), strlen(prompt.c_str()), 0)) == -1)
		std::cerr << "Error : send failed" << std::endl;
}