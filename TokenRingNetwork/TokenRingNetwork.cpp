#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

class Computer {
private:
	string ipAddress;
	string buffer;
public:
	Computer(string ip)
		: ipAddress(ip), buffer("")
	{}

	string getIPAddress() const {
		return ipAddress;
	}

	string getBuffer() const {
		return buffer;
	}

	void receiveToken(const string& message) {
		buffer = message;
	}

	void clearBuffer() {
		buffer = "";
	}
};

class Token {
private:
	string sourceIP;
	string destinationIP;
	string message;
	bool isFree;
	bool isDelivered;
public:
	Token() : sourceIP(""), destinationIP(""), message(""), isFree(true), isDelivered(false) {}

	Token(const string& srcIP, const string& destIP, const string& msg)
		: sourceIP(srcIP), destinationIP(destIP), message(msg), isFree(true), isDelivered(false) {}

	bool isTokenFree() const
	{
		return isFree;
	}

	bool isTokenDelivered() const
	{
		return isDelivered;
	}

	void setDelivered()
	{
		isDelivered = true;
	}

	void setSourceIP(const string& srcIP)
	{
		sourceIP = srcIP;
	}

	void setDestinationIP(const string& destIP)
	{
		destinationIP = destIP;
	}

	void setMessage(const string& msg) {
		message = msg;
	}

	void setFree(bool freeStatus) {
		isFree = freeStatus;
	}

	string toString() const {
		stringstream ss;
		ss << "Source IP: " << sourceIP << ", Destination IP: " << destinationIP << ", Message: " << message;
		return ss.str();
	}
};

int main() {
	vector<Computer> network;

	for (int i = 0; i < 10; ++i)
	{
		string ip = to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256);
		network.push_back(Computer(ip));
	}
	srand(time(NULL));

	// Afisare starea fiecarui calculator
	for (int i = 0; i < 10; ++i) {
		cout << "C" << i << "(" << network[i].getIPAddress() << ")";

		cout << endl;
	}

	int currentIndex;
	int initialIndex;
	int previousIndex;

	for (int step = 1; step <= 10; ++step)
	{
		cout << "Step " << step << ":" << endl;
		string sourceIP, destIP;
		do {
			sourceIP = network[rand() % 10].getIPAddress();
			destIP = network[rand() % 10].getIPAddress();
		} while (sourceIP == destIP);

		Token token(sourceIP, destIP, "Test message");


		cout << "Source: " << sourceIP << ", Destination: " << destIP << endl;

		

		for (int i = 0; i < 10; i++) {
			if (network[i].getIPAddress() == sourceIP)
			{
				initialIndex = i;
				currentIndex = i;
			}
		}

		if (step >= 2)
		{
			while (currentIndex != previousIndex)
			{
				cout << "C" << previousIndex << "(" << network[previousIndex].getIPAddress() << ") -> muta jetonul" << endl;
				previousIndex = (previousIndex + 1) % 10;
			}
			cout << "S-a ajuns la startul curent\n";
		}


		for (int i = 0; i < 10; i++) {
			if (network[i].getIPAddress() == sourceIP)
			{
				previousIndex = i;
			}
		}

		while (true)
		{
			if (network[currentIndex].getIPAddress() == destIP)
			{
				network[currentIndex].receiveToken(token.toString());
				token.setDelivered();
				cout << "C" << currentIndex << "(" << network[currentIndex].getIPAddress() << ") -> " << network[currentIndex].getBuffer() << endl;
				while (currentIndex != initialIndex)
				{
					cout << "C" << currentIndex << "(" << network[currentIndex].getIPAddress() << ") -> muta jetonul" << endl;
					currentIndex = (currentIndex + 1) % 10;
				}
				cout << "C" << currentIndex << "(" << network[currentIndex].getIPAddress() << ") -> primeste jetonul inapoi" << endl;
				break;
			}
			else
			{
				cout << "C" << currentIndex << "(" << network[currentIndex].getIPAddress() << ") -> muta jetonul" << endl;
				int nextIndex = (currentIndex + 1) % 10;
				if (nextIndex != currentIndex)
				{
					currentIndex = nextIndex;
				}
			}
		}

	}

	return 0;
}