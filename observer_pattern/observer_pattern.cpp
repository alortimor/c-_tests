#include <vector>
#include <unordered_map>
#include <iostream>
#include <typeindex>
#include <algorithm>
#include <stdexcept>
#include <functional>

class Subject;
class Event { };

enum class NotifyAction { Done, UnRegister};
class Observer {
    public:
        virtual ~Observer() {}
        virtual NotifyAction onNotify(Subject& subject, Event const& event) = 0;
};

class Subject {
    public:
        void registerObserver(Observer& observer) {
            if (std::find(std::begin(observers), std::end(observers), &observer) == std::end(observers)) {
                throw std::runtime_error("registerObserver(): observer already registered");
            }
            observers.push_back(&observer);
        }
        void unregisterObserver(Observer& observer) {
            observers.erase(std::remove(std::begin(observers), std::end(observers), &observer), std::end(observers));
        }
        void notifyObservers(Event const& event) {
            std::vector<Observer*>  deadObservers;
            for(Observer* observer: observers) {
                if (observer->onNotify(*this, event) == NotifyAction::UnRegister) {
                    deadObservers.push_back(observer);
                }
            }

            // Remove the dead observers.
            auto newEnd    = std::end(observers);
            for(Observer* dead:deadObservers) {
                newEnd  = std::remove(std::begin(observers), newEnd, dead);
            }
            observers.erase(newEnd, std::end(observers));
        }
    private:
        std::vector<Observer*>      observers;
};
class EventHandler: public Observer
{
    public:
        NotifyAction onNotify(Subject& subject, Event const& event) override
        {
            auto find = handlers.find(std::type_index(typeid(event)));
            if (find != handlers.end()) {
                find->second(subject, event);
            }

            return NotifyAction::Done;
        }
        template<typename T>
        void registerEventHandler(std::function<void(Subject&, Event const&)> handler)
        {
            handlers[std::type_index(typeid(T))] = handler;
        }

    private:
        std::unordered_map<std::type_index, std::function<void(Subject&, Event const&)>> handlers;
};
class MouseMove: public Event {};
class MouseClick: public Event {};

class MouseHandler: public EventHandler
{
    private:
        void mouseClick(Subject&, Event const&)
        {
            std::cout << "Mouse Clicked\n";
        }
    public:
        MouseHandler()
        {
            // Register a call to a member method
            registerEventHandler<MouseClick>(std::bind(&MouseHandler::mouseClick, this, std::placeholders::_1, std::placeholders::_2));
        }
};
class Mouse: public Subject
{
};
int main()
{
    MouseHandler    mouseEventHandler;
    // Register a call to a lambda
    mouseEventHandler.registerEventHandler<MouseMove>([](Subject&, Event const&){std::cout << "Mouse Moved\n";});

    Mouse           mouse;
    mouse.registerObserver(mouseEventHandler);

}
