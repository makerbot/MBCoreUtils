

#ifndef EVENT_HH_
#define EVENT_HH_

#include <functional>
#include <map>
#include "mutex.h"
#include "lockguard.h"
#include <memory>

namespace MakerBot {

/*
 * SubscriberPolicy should be templated with callback argument types
 * and should provide an overloaded operator() method
 *
 * Args... should be a list of callback arguments types
 */

	template<template<typename... Args> class SubscriberPolicy, typename... Args>
	class Event {
	public:

		/*
		 * Default constructor.
		 */
		Event() : m_lastHandleId(0) {

		}

		/*
		 * Destructor
		 */
		virtual ~Event() {

		}

		typedef SubscriberPolicy<Args...> SubscriberType;
		typedef std::weak_ptr<SubscriberType> SubscriberPtr;

		/*
		 * Adds a callback to the list of subscribers for an event.
		 */

		virtual int subscribe(SubscriberPtr func) {
			LockGuard<Mutex> lock(&m_mutex);
			m_subscribers.insert(std::pair<int, SubscriberPtr>(++m_lastHandleId, func));
			return m_lastHandleId;
		}

		/*
		 * Removes a callback from the list of subscribers
		 */
		virtual void unsubscribe(int handle) {
			LockGuard<Mutex> lock(&m_mutex);
			m_subscribers.erase(handle);
		}

		virtual void fire(Args... args) {

			std::map<int, SubscriberPtr> subscribers = copySubscribers(); // TODO: REMOVE THIS! DONT COPY!
			for( auto itSubscribers = subscribers.begin(); itSubscribers != subscribers.end(); ++itSubscribers) {
				std::shared_ptr<SubscriberType> callbackPtr = (itSubscribers->second).lock();
				if (callbackPtr){
					(*callbackPtr)(args...);
				} else {
					// subscriber pointer has expired
					unsubscribe(itSubscribers->first);
				}
			}
		}

	private:

		// TODO: PUT ALL SUBSCRIPTION HANLDING ON CONTROLLER LOOP
		// TODO: REMOVE THIS FUNCTION!
		std::map<int, SubscriberPtr> copySubscribers(){
			LockGuard<Mutex> lock(&m_mutex);
			std::map<int, SubscriberPtr> copy(m_subscribers);
			return copy;
		}


		// Subscriber list for the event.
		std::map<int, SubscriberPtr> m_subscribers;
		Mutex m_mutex;

     	// Last handle ID given out to a subscriber.
		int m_lastHandleId;
	};

}


#endif /* EVENT_HH_ */
