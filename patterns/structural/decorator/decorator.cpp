#include <iostream>
#include <memory>
#include <string>

// Component
class Notifier {
 public:
    virtual ~Notifier() = default;
    virtual void send(const std::string& message) = 0;
};

// Concrete Component
class ConcreteNotifier : public Notifier {
 public:
    void send(const std::string& message) override {
        std::cout << "[Concrete Notifier] Sending: " << message << std::endl;
    }
};

// Base Decorator
// - Implements Notifier
// - Holds a wrapped Notifier
class BaseDecorator : public Notifier {
 public:
    // Default Constructor (Constructor without parameters)
    // BaseDecorator() = default;
    
    // Convenience constructor using initialisation list
    BaseDecorator(std::shared_ptr<Notifier> notifier) 
        : wrappee(std::move(notifier)) {}
    
    // Convenience constructor not using initialisation list
    // BaseDecorator(std::shared_ptr<Notifier> notifier) {
    //     wrappee = std::move(notifier);
    // }

    // Default behavior: just forward to the wrappee
    void send(const std::string& message) override {
        wrappee->send(message);
    }
 private:
    std::shared_ptr<Notifier> wrappee;
};

class SMSDecorator : public BaseDecorator {
 public:
    SMSDecorator(std::shared_ptr<Notifier> notifier) 
        : BaseDecorator(std::move(notifier)) {}

    // If we don't use initialization lists, you need to explicitly 
    // call the default constructor for BaseDecorator 
    // inside the SMSDecorator constructor, like BaseDecorator(std::move(notifier))
    // 
    // However, we shouldn't create a default constructor for BaseDecorator, 
    // because we won't be creating a BaseDecorator without a wrappee
    // (This diminishes the whole reason why we shouldn't)
    // 
    // Although BaseDecorator(std::move(notifier)) looks like 'default constructing',
    // it's in fact not.
    //
    // Remember to:
    // - Always use the initialization list to call a base class constructor.
    // (Example Code in Notion 20250310) 
    // 
    // SMSDecorator(std::shared_ptr<Notifier> notifier) {
    //     BaseDecorator(std::move(notifier));
    // }

    void send(const std::string& message) override {
        // 1) Call the original notifier
        BaseDecorator::send(message);
        // 2) Then add SMS
        sendSMS(message);
    }
 private:
    void sendSMS(const std::string& message) {
        std::cout << "[SMS] Sending: " << message << std::endl;
    }
};

class FacebookDecorator : public BaseDecorator {
 public:
    FacebookDecorator(std::shared_ptr<Notifier> notifier) : BaseDecorator(std::move(notifier)) {}

    void send(const std::string& message) override {
        BaseDecorator::send(message);
        sendFacebook(message);
    }
 private:
    void sendFacebook(const std::string& message) {
        std::cout << "[Facebook] Sending: " << message << std::endl;
    }
};

class SlackDecorator : public BaseDecorator {
 public:
    SlackDecorator(std::shared_ptr<Notifier> notifier) : BaseDecorator(std::move(notifier)) {}

    void send(const std::string& message) override {
        BaseDecorator::send(message);
        sendSlack(message);
    }
 private:
    void sendSlack(const std::string& message) {
        std::cout << "[Slack] Sending: " << message << std::endl;
    }
};

int main() {
    auto baseNotifier = std::make_shared<ConcreteNotifier>();
    baseNotifier->send("Base Notifier");
    std::cout << baseNotifier.use_count() << std::endl;
    std::cout << std::endl;

    auto smsNotifier = std::make_shared<SMSDecorator>(baseNotifier);
    smsNotifier->send("SMS Notifier");
    std::cout << smsNotifier.use_count() << std::endl;
    std::cout << std::endl;
    
    auto facebookNotifier = std::make_shared<FacebookDecorator>(smsNotifier);
    facebookNotifier->send("Facebook Notifier");
    std::cout << facebookNotifier.use_count() << std::endl;
    std::cout << std::endl;

    auto slackNotifier = std::make_shared<SlackDecorator>(facebookNotifier);
    slackNotifier->send("Slack Notifier");
    std::cout << slackNotifier.use_count() << std::endl;
    std::cout << std::endl;

    // This doesn't work because decoratedNotifier is a SMSDecorator class, and cannot be converted to a FacebookDecorator nor a SlackDecorator.
    // auto decoratedNotifier = std::make_shared<SMSDecorator>(baseNotifier);
    // decoratedNotifier = std::make_shared<FacebookDecorator>(decoratedNotifier);
    // decoratedNotifier = std::make_shared<SlackDecorator>(decoratedNotifier);

    // Denoting this as auto makes it type of std::shared_ptr<SMSDecorator>, not something we want.
    std::shared_ptr<Notifier> decoratedNotifier = std::make_shared<SMSDecorator>(baseNotifier);
    decoratedNotifier = std::make_shared<FacebookDecorator>(decoratedNotifier);
    decoratedNotifier = std::make_shared<SlackDecorator>(decoratedNotifier);

    decoratedNotifier->send("Hello from the Decorator Pattern!");

}
