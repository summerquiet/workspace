#include <string>
#include <map>
#include <list>

class Subscriber
{
    virtual void update(std::string message) = 0;
};

class Publisher
{
public:

    Publisher()
    : m_cSubscribers()
    {}

    ~Publisher()
    {}

    void subscribe(std::string topic, Subscriber& subscriber)
    {
        auto subscriberListIt = m_cSubscribers.find(topic);
        if (subscriberListIt == m_cSubscribers.end()) {
            std::list<Subscriber> subscriberList;
            m_cSubscribers[topic] = subscriberList;
            subscriberListIt = m_cSubscribers.find(topic);
        }
        subscriberListIt->push_back(subscriber);
    }

    void unsubscribe(std::string topic, Subscriber& subscriber)
    {
        auto subscriberListIt = m_cSubscribers.find(topic);
        if (subscriberListIt != m_cSubscribers.end()) {
            subscriberListIt.remove(subscriber);
        }
    }

    void publish(std::string topic, std::string message)
    {
        auto subscriberListIt = m_cSubscribers.find(topic);
        if (subscriberListIt != m_cSubscribers.end()) {
            for (auto it = subscriberListIt->second.begin(); it != subscriberListIt->second.end(); ++it)
                it->update(message);
            }
        }
    }

private:

    std::map<std::string, std::list<Subscriber>> m_cSubscribers;
};

class EmailSubscriber : public Subscriber
{
public:
    EmailSubscriber(std::string email)
    {
        m_sEmail = email;
    }

    virtual void update(std::string message)
    {
        printf("Send email to %s : %s\n", m_sEmail.c_str(), message.c_str());
    }

private:
    std::string m_sEmail;
};

class SMSSubscriber : public Subscriber
{
public:
    SMSSubscriber(std::string phoneNumber)
    {
        m_sPhoneNumber = phoneNumber;
    }

    virtual void update(std::string message)
    {
        printf("Send SMS to %s : %s\n", m_sPhoneNumber.c_str(), message.c_str());
    }

private:
    std::string m_sPhoneNumber;
};
