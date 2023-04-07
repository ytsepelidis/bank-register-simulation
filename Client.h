#ifndef CLIENT_H
#define CLIENT_H

class Client
{
private:
	static int s_incClientID;
	int clientID;

public:
	Client();
	~Client();

	void set_clientID(int clientID);
	int get_clientID() const;
};

#endif // !CLIENT_H