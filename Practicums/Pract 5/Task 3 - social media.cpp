#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t CONTENT_LENGTH = 1000;
struct Message
{
private:
	char content[CONTENT_LENGTH] = { 0 };
	bool isRead = false;
	char* sender = nullptr;
	char* receiver = nullptr;
public:
	Message() = default;
	Message(const char* content)
	{
		setContent(content);
	}
	Message(const Message& other)
	{
		this->copyFrom(other);
	}
	~Message()
	{
		delete[] sender;
		delete[] receiver;
	}
	const char* getContent() const
	{
		return content;
	}
	void setContent(const char* content)
	{
		if (!content)
		{
			return;
		}

		if (strlen(content) > CONTENT_LENGTH - 1)
		{
			return;
		}
		strcpy(this->content, content);
	}
	const char* getSender() const
	{
		return sender;
	}
	void setSender(const char* sender)
	{
		if (!sender)
		{
			return;
		}
		delete[] this->sender;
		this->sender = new char[strlen(sender) + 1];
		strcpy(this->sender, sender);
	}
	const char* getReceiver() const
	{
		return receiver;
	}
	void setReceiver(const char* receiver)
	{
		if (!receiver)
		{
			return;
		}
		delete[] this->receiver;
		this->receiver = new char[strlen(receiver) + 1];
		strcpy(this->receiver, receiver);
	}
	bool getIsRead() const
	{
		return isRead;
	}
	void setAsRead()
	{
		this->isRead = true;
	}
	void copyFrom(const Message& other)
	{
		strcpy(this->content, other.content);
		this->setSender(other.sender);
		this->setReceiver(other.receiver);	
		this->isRead = other.isRead;
	}
};
struct MessageCollection
{
private:
	Message* messages = nullptr;
	size_t count = 0;
	size_t capacity = 0;
	void grow()
	{
		if (capacity == 0)
		{
			capacity = 1;
		}

		Message* temp = new Message[capacity *= 2];
		for (size_t i = 0; i < count; i++)
		{
			temp[i].copyFrom(messages[i]);
		}
		delete[] messages;
		messages = temp;
	}
public:
	const Message* getMessages() const
	{
		return messages;
	}
	size_t getCount() const
	{
		return count;
	}
	MessageCollection() = default;
	MessageCollection(size_t capacity)
	{
		this->capacity = capacity;
		messages = new Message[capacity];
	}
	MessageCollection(const MessageCollection& other)
	{
		this->copyFrom(other);
	}
	~MessageCollection()
	{
		delete[] messages;
	}
	void addMessage(const Message& message)
	{
		if (count + 1 > capacity)
		{
			grow();
		}
		messages[count++].copyFrom(message);
	}
	void copyFrom(const MessageCollection& other)
	{
		this->count = other.count;
		this->capacity = other.capacity;

		delete[] this->messages;
		this->messages = new Message[other.capacity];
		for (size_t i = 0; i < other.count; i++)
		{
			messages[i].copyFrom(other.messages[i]);
		}
	}
};
struct User
{
private:
	char* username = nullptr;
	char* password = nullptr;
	MessageCollection sentMessages;
	MessageCollection receivedMessages;
public:
	User() : User("", "", {}, {})
	{
		
	}
	User(const char* username, const char* password, const MessageCollection& sentMessages, const MessageCollection& receivedMessages)
	{
		this->setUsername(username);
		this->setPassword(password);
		this->sentMessages.copyFrom(sentMessages);
		this->receivedMessages.copyFrom(receivedMessages);
	}
	User(const User& other)
	{
		this->copyFrom(other);
	}
	void sendMessageTo(User& receiver, Message& message)
	{
		message.setSender(this->getUsername());
		message.setReceiver(receiver.getUsername());
		this->sentMessages.addMessage(message);
		receiver.receivedMessages.addMessage(message);
	}
	const char* getUsername() const
	{
		return username;
	}
	void setUsername(const char* username)
	{
		if (!username)
		{
			return;
		}
		delete[] this->username;
		this->username = new char[strlen(username) + 1];
		strcpy(this->username, username);
	}
	const char* getPassword() const
	{
		return password;
	}
	void setPassword(const char* password)
	{
		if (!password)
		{
			return;
		}
		delete[] this->password;
		this->password = new char[strlen(password) + 1];
		strcpy(this->password, password);
	}
	const MessageCollection& getSentMessages() const
	{
		return sentMessages;
	}
	const MessageCollection& getReceivedMessages() const
	{
		return receivedMessages;
	}
	void copyFrom(const User& other)
	{
		this->setUsername(other.username);
		this->setPassword(other.password);
		this->sentMessages.copyFrom(other.sentMessages);
		this->receivedMessages.copyFrom(other.receivedMessages);
	}
};
struct UserCollection
{
private:
	User* users = nullptr;
	size_t count = 0;
	size_t capacity = 1;
	void grow()
	{
		User* temp = new User[capacity *= 2];
		for (size_t i = 0; i < count; i++)
		{
			temp[i].copyFrom(users[i]);
		}
		delete[] users;
		users = temp;
	}
public:
	const User* getUsers() const
	{
		return users;
	}
	size_t getCount() const
	{
		return count;
	}
	UserCollection() = default;
	UserCollection(size_t capacity)
	{
		this->capacity = capacity;
		users = new User[capacity];
	}
	UserCollection(const UserCollection& other)
	{
		this->copyFrom(other);
	}
	~UserCollection()
	{
		delete[] users;
	}
	User* first(int index)
	{
		if (index < 0 || index >= count)
		{
			return nullptr;
		}
		return &users[index];
	}
	bool addUser(const User& user)
	{
		if (containsUser(user, false))
		{
			return false;
		}

		if (count + 1 > capacity)
		{
			grow();
		}
		users[count++].copyFrom(user);
		return true;
	}
	void copyFrom(const UserCollection& other)
	{
		this->count = other.count;
		this->capacity = other.capacity;

		delete[] this->users;
		this->users = new User[other.capacity];
		for (size_t i = 0; i < other.count; i++)
		{
			users[i].copyFrom(other.users[i]);
		}
	}
	bool containsUser(const User& user, bool includePass)
	{
		for (size_t i = 0; i < this->count; i++)
		{
			if (strcmp(user.getUsername(), this->users[i].getUsername()) == 0 && (!includePass || strcmp(user.getPassword(), this->users[i].getPassword()) == 0))
			{
				return true;
			}
		}
		return false;
	}
	bool containsUser(const char* username, const char* password)
	{
		if (!username || !password)
		{
			return false;
		}
		return indexof(username, password) != -1;
	}
	int indexof(const char* username, const char* password)
	{
		if (!username)
		{
			return -1;
		}
		for (size_t i = 0; i < this->count; i++)
		{
			if (strcmp(username, this->users[i].getUsername()) == 0 && (!password || strcmp(password, this->users[i].getPassword()) == 0))
			{
				return i;
			}
		}
		return -1;
	}
};
struct SocialMedia
{
private:
	char* name = nullptr;
	UserCollection users;
	void sendMessage(User* sender, User* receiver, const char* message)
	{
		if (!sender || !receiver)
		{
			return;
		}
		if (!users.containsUser(*sender, false) || !users.containsUser(*receiver, false))
		{
			return;
		}
		Message convMessage(message);
		sender->sendMessageTo(*receiver, convMessage);
	}
public:
	SocialMedia() : SocialMedia("", {})
	{

	}
	SocialMedia(const char* name, const UserCollection& users)
	{
		this->setName(name);
		this->users.copyFrom(users);
	}
	SocialMedia(const SocialMedia& other)
	{
		this->copyFrom(other);
	}
	~SocialMedia()
	{
		delete[] name;
	}
	const char* getName() const
	{
		return name;
	}
	void setName(const char* name)
	{
		if (!name)
		{
			return;
		}
		delete[] this->name;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	const UserCollection& getUsers() const
	{
		return users;
	}
	bool registerUser(const char* username, const char* password)
	{
		return users.addUser({ username, password, {}, {} });
	}
	bool login(const char* username, const char* password)
	{
		return users.containsUser(username, password);
	}
	void sendMessage(const char* sender,const char* receiver, const char* message)
	{
		if (!sender || !receiver || !message)
		{
			return;
		}

		if (strcmp(sender, receiver) == 0)
		{
			return;
		}
		int senderIndex = users.indexof(sender, nullptr);
		int receiverIndex = users.indexof(receiver, nullptr);
		if (senderIndex == -1 || receiverIndex == -1)
		{
			return;
		}
		this->sendMessage(users.first(senderIndex), users.first(receiverIndex), message);
	}
	void copyFrom(const SocialMedia& other)
	{
		this->setName(other.name);
		this->users.copyFrom(other.users);
	}
};
int main()
{
	UserCollection users(5);
	users.addUser({"user1", "user1pass", {}, {}});
	users.addUser({"user2", "user2pass", {}, {}});
	users.addUser({"user3", "user3pass", {}, {}});
	users.addUser({"user4", "user4pass", {}, {}});
	users.addUser({"user5", "user5pass", {}, {}});
	SocialMedia instagram("Instagram", users);

	std::cout << instagram.registerUser("newUser", "newUserPass") << std::endl;
	std::cout << instagram.registerUser("newUser", "newUserPass") << std::endl; //shouldn't add
	instagram.sendMessage("user1", "newUser", "hey!");
	instagram.sendMessage("newUser", "user1", "hey back!");
	instagram.sendMessage("newUser", "newUser", "not gonna work"); // shoudln't send
	std::cout << instagram.login("user1", "wrongpass") << std::endl; // wrong login credentials
	std::cout << instagram.login("user1", "user1pass") << std::endl;
}