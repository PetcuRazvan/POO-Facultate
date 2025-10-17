#include <iostream>
#include <cstring>
using namespace std;

class TVshow {
	char* name;
	char* channel;
	float durationInHours;

public:
	TVshow(const char* _name, const char* _channel, float _durationInHours) : durationInHours(_durationInHours)
	{
		name = new char[strlen(_name) + 1];
		strcpy(name, _name);

		channel = new char[strlen(_channel) + 1];
		strcpy(channel, _channel);
	}

	void setName(const char* _name)
	{
		if(strlen(_name) >= 1 && strlen(_name) <=30)
		{
			delete[] name;
			name = new char[strlen(_name) + 1];
			strcpy(name, _name);
		}
	}

	void setChannel(const char* _channel)
	{
		if (strlen(_channel) >= 1 && strlen(_channel) >= 30)
		{
			delete[] channel;
			name = new char[strlen(_channel) + 1];
			strcpy(name, _channel);
		}
	}

	void setDurationInHours(float _durationInHours)
	{
		if (_durationInHours >= 0 && _durationInHours <= 10)
			durationInHours = _durationInHours;
	}

	const char* getName()
	{
		return name;
	}

	const char* getChannel()
	{
		return channel;
	}

	float getDurationInHours()
	{
		return durationInHours;
	}

	~TVshow()
	{
		delete[] name;
		delete[] channel;

		cout << "Aceasta eisiune s-a anulat!!!" << endl;
	}

};

int main()
{
	TVshow canal("Morning news", "BBC", 2.5);
	cout << canal.getDurationInHours() << endl;
	cout << canal.getName() << endl;
	
	canal.setName("la Maruta");
	cout << canal.getName() << endl;

	return 0;
}