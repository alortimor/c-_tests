#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/signals2.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>
#include <boost/any.hpp>

// Forward declarations
class Spaceship;
typedef boost::shared_ptr<Spaceship> SpaceshipPtr;
typedef boost::weak_ptr<Spaceship> SpaceshipWPtr;

class EventManager;
typedef boost::shared_ptr<EventManager> EventManagerPtr;

// ******************************************************************
// EVENT DEFINITIONS
// ******************************************************************
struct TakeoffEvent { static const std::string name ; };
const std::string TakeoffEvent::name = "takeoff" ;

struct LandingEvent { static const std::string name ; };
const std::string LandingEvent::name = "landing" ;

struct CrashEvent {
    static const std::string name ;
    CrashEvent(const std::string & s) : sound(s) {}
    std::string sound ;
};

const std::string CrashEvent::name = "crash" ;

struct MutinyEvent {
    static const std::string name ;

    MutinyEvent(bool s, int n) : successful(s), numDead(n) {}

    bool successful ;
    int numDead ;
};

const std::string MutinyEvent::name = "mutiny" ;


// ******************************************************************
// ******************************************************************

class EventManager {
public:
    // Notify listeners of all recent events
    void FlushAllQueuedEvents()
    {
        NotificationVec vecNotifications;

        // Open a protected scope to modify the notification list
        {
            // One thread at a time
            boost::recursive_mutex::scoped_lock lock( m_notificationProtection );

            // Copy the notification vector to our local list and clear it at the same time
            std::swap( vecNotifications, m_vecQueuedNotifications );
        }

        // Now loop over the notification callbacks and call each one.
        // Since we're looping over the copy we just made, new events won't affect us.
        BOOST_FOREACH( const NamedNotification & nameAndFn, vecNotifications ) {
            // Debug output
            std::cout << "Flushing " << nameAndFn.first << std::endl ;

            try {
                // call the listener(s)
                nameAndFn.second() ;
            }
            catch ( const boost::bad_any_cast & ) {
                std::cout << "*** BUG DETECTED! Invalid any_cast. ***" << std::endl ;
            }
        }
    }

    // Callback signature
    typedef void EventNotificationFnSignature();
    typedef boost::function<EventNotificationFnSignature> EventNotificationFn;

    //! Queue an event with the event manager
    void QueueEvent( const std::string & name, const EventNotificationFn & nameAndEvent ) {
        // One thread at a time.
        boost::recursive_mutex::scoped_lock lock(  m_notificationProtection );
        m_vecQueuedNotifications.push_back( NamedNotification(name, nameAndEvent) );
    }

private:
    // Queue of events
    typedef std::pair<std::string, EventNotificationFn> NamedNotification ;
    typedef std::vector<NamedNotification> NotificationVec ;
    NotificationVec m_vecQueuedNotifications;

    // This mutex is used to ensure one-at-a-time access to the list of notifications
    boost::recursive_mutex m_notificationProtection ;
};

class EventProducer {
public:
    EventProducer( const EventManagerPtr & pEventManager ) : m_pEventManager(pEventManager) {}

    typedef void SignalSignature(const boost::any &) ;
    typedef boost::function<SignalSignature> HandlerFn ;

    boost::signals2::connection subscribe( const std::string & eventName, const HandlerFn & fn ) {
        // Create this signal if it doesn't exist yet
        if ( m_mapSignals.find(eventName) == m_mapSignals.end() )
        {
            m_mapSignals[eventName].reset( new EventSignal ) ;
        }
        return m_mapSignals[eventName]->connect(fn) ;
    }

    template <typename _Event>
    void trigger(const _Event & event)
    {
        // Do we have a signal for this (if not, then we have no listeners)
        EventSignalMap::iterator iterFind = m_mapSignals.find(event.name) ;
        if ( iterFind != m_mapSignals.end() )
        {
            EventSignal & signal = *iterFind->second ;

            // Wrap the event in a boost::any
            boost::any wrappedEvent = event ;

            m_pEventManager->QueueEvent( event.name, boost::bind( boost::ref(signal), wrappedEvent ) ) ;
        }
    }

protected:
    typedef boost::signals2::signal<SignalSignature> EventSignal ;
    typedef boost::shared_ptr<EventSignal> EventSignalPtr ;
    typedef std::map<std::string, EventSignalPtr> EventSignalMap ;
    EventSignalMap m_mapSignals ;

    EventManagerPtr m_pEventManager ;
};

typedef boost::shared_ptr<EventProducer> EventProducerPtr ;

class Spaceship : public EventProducer
{
public:

    Spaceship(const std::string & name, const EventManagerPtr & pEventManager)
        : EventProducer(pEventManager)
        , m_name(name)
    {
    }

    std::string & name()
    {
        return m_name ;
    }

private:

    std::string m_name;
};

class Listener {
public:
  Listener( const std::set<SpaceshipPtr> & ships ) {
    // For every ship, subscribe to all of the events we're interested in.
    BOOST_FOREACH( const SpaceshipPtr & pSpaceship, ships ) {
      m_ships.insert( pSpaceship );

      // Bind up a weak_ptr in the handler calls (using a shared_ptr would cause a memory leak)
      SpaceshipWPtr wpSpaceship(pSpaceship);

      // Register event callback functions with the spaceship so he can notify us.
      // Bind a pointer to the particular spaceship so we know who originated the event.
      m_allConnections[pSpaceship].push_back( pSpaceship->subscribe( CrashEvent::name, boost::bind( &Listener::HandleCrashEvent, this, wpSpaceship, _1 ) ) );

      m_allConnections[pSpaceship].push_back( pSpaceship->subscribe( MutinyEvent::name, boost::bind( &Listener::HandleMutinyEvent, this, wpSpaceship, _1 ) ) );

      m_allConnections[pSpaceship].push_back( pSpaceship->subscribe( TakeoffEvent::name, boost::bind( &Listener::HandleTakeoffEvent, this, wpSpaceship, _1 ) ) );

      m_allConnections[pSpaceship].push_back( pSpaceship->subscribe( LandingEvent::name, boost::bind( &Listener::HandleLandingEvent, this, wpSpaceship, _1 ) ) );

      // Uncomment this next line to see what happens if you try to connect a handler to the wrong event.
      // (Connecting "landing" event to "crash" handler.)
      // m_allConnections[pSpaceship].push_back( pSpaceship->subscribe( LandingEvent::name, boost::bind( &Listener::HandleCrashEvent, this, wpSpaceship, _1 ) ) );
    }
}

    ~Listener() {
        // Disconnect from any signals we still have
        BOOST_FOREACH( const SpaceshipPtr pShip, m_ships ) {
            BOOST_FOREACH( boost::signals2::connection & conn, m_allConnections[pShip] ) { conn.disconnect(); }
        }
    }

private:
    typedef std::vector<boost::signals2::connection> ConnectionVec;
    std::map<SpaceshipPtr, ConnectionVec> m_allConnections;
    std::set<SpaceshipPtr> m_ships;

    void HandleTakeoffEvent( SpaceshipWPtr wpSpaceship, const boost::any & wrappedEvent ) {
        // Obtain a shared ptr from the weak ptr
        SpaceshipPtr pSpaceship = wpSpaceship.lock();
        std::cout << "Takeoff event on " << pSpaceship->name() << '\n';
    }

    void HandleLandingEvent( SpaceshipWPtr wpSpaceship, const boost::any & wrappedEvent ) {
        // Obtain a shared ptr from the weak ptr
        SpaceshipPtr pSpaceship = wpSpaceship.lock();
        std::cout << "Landing event on " << pSpaceship->name() << '\n';
    }

    void HandleCrashEvent(SpaceshipWPtr wpSpaceship, const boost::any & wrappedEvent ) {
        // Extract the crash event from the boost::any
        CrashEvent crash = boost::any_cast<CrashEvent>(wrappedEvent) ;

        // Obtain a shared ptr from the weak ptr
        SpaceshipPtr pSpaceship = wpSpaceship.lock();

        std::cout << pSpaceship->name() << " crashed with sound: " << crash.sound << '\n';

        // That ship is dead.  Delete it from the list of ships we track.
        m_ships.erase(pSpaceship);

        // Also, make sure we don't get any more events from it
        BOOST_FOREACH( boost::signals2::connection & conn, m_allConnections[pSpaceship] ) {
            conn.disconnect();
        }

        m_allConnections.erase(pSpaceship);
    }

    void HandleMutinyEvent(SpaceshipWPtr wpSpaceship, const boost::any & wrappedEvent ) {
        // Extract the mutiny event from the boost::any
        MutinyEvent mutiny = boost::any_cast<MutinyEvent>(wrappedEvent) ;

        SpaceshipPtr pSpaceship = wpSpaceship.lock();
        std::cout << (mutiny.successful ? "Successful" : "Unsuccessful" ) ;
        std::cout << " mutiny on " << pSpaceship->name() << "! (" << mutiny.numDead << " dead crew members)\n";
    }
};

int main() {
    // Instantiate an event manager
    EventManagerPtr pEventManager( new EventManager );

    // Create some ships to play with
    int numShips = 5;
    std::vector<SpaceshipPtr> vecShips;
    for (int shipIndex = 0; shipIndex < numShips; ++shipIndex) {
        std::string name = "Ship #" + boost::lexical_cast<std::string>(shipIndex);
        SpaceshipPtr pSpaceship( new Spaceship(name, pEventManager) );
        vecShips.push_back(pSpaceship);
    }

    // Create the controller with our ships
    std::set<SpaceshipPtr> setShips( vecShips.begin(), vecShips.end() );
    Listener controller(setShips);

    // Quick-and-dirty "simulation"
    // We'll cause various events to happen to the ships in the simulation,
    // And periodically flush the events by triggering the event manager

    std::cout << "BEGIN Orbit #1" << std::endl;
    vecShips[0]->trigger( TakeoffEvent() );
    vecShips[0]->trigger( CrashEvent("Kaboom!") );
    vecShips[1]->trigger( TakeoffEvent() );
    vecShips[1]->trigger( CrashEvent("Blam!") );
    vecShips[2]->trigger( TakeoffEvent() );
    vecShips[2]->trigger( MutinyEvent(false, 7) );
    std::cout << "END Orbit #1\n" << std::endl;

    pEventManager->FlushAllQueuedEvents();
    std::cout << "\n" ;

    std::cout << "BEGIN Orbit #2" << std::endl;
    vecShips[3]->trigger( TakeoffEvent() );
    vecShips[3]->trigger( MutinyEvent(true, 2) );
    vecShips[4]->trigger( TakeoffEvent() );
    vecShips[4]->trigger( CrashEvent("Splat!") );
    std::cout << "END Orbit #2\n" << std::endl;

    pEventManager->FlushAllQueuedEvents();
    std::cout << "\n" ;

    std::cout << "BEGIN Orbit #3" << std::endl;
    vecShips[2]->trigger( MutinyEvent(false, 15) );
    vecShips[2]->trigger( MutinyEvent(true, 20) );
    vecShips[2]->trigger( LandingEvent() );
    vecShips[3]->trigger( CrashEvent("Fizzle.") );
    vecShips[3]->trigger( MutinyEvent(true, 0) ); //< Should not cause output, since this ship has already crashed!
    std::cout << "END Orbit #3\n" << std::endl;

    pEventManager->FlushAllQueuedEvents();
    std::cout << "\n" ;

    return 0;
}


