#include "Functions.h"
#include "Client.h"

int Client::s_incClientID = 0;

Client::Client()
{
	clientID = s_incClientID;

	std::cout << "Created client with clientID: " << clientID << "\n";

	s_incClientID += 1;
}

Client::~Client()
{

}

void Client::set_clientID(int clientID)
{
	this->clientID = clientID;
}

int Client::get_clientID() const
{
	return clientID;
}