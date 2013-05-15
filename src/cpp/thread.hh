/*
 * Thread.hh
 *
 *  Created on: Apr 16, 2013
 *      Author: paul
 *
 *  Contains full definition of the class MakerBot::Thread
 */

#ifndef THREAD_HH_
#define THREAD_HH_

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include "irunnable.hh"

namespace MakerBot {

	/*
	 * Light wrapper for the creation of, starting, stopping and joining of a thread.
	 * Insulates applications from the type of threading library being used.
	 * Thread logic and entry point are provided via an IRunnable object.
	 */
	class Thread {
	public:

		/*
		 * Constructor.  Takes a pointer to an IRunnable object.
		 */
		explicit Thread(IRunnable* runnable)
			: m_runnable(runnable) {

		}

		/*
		 * Starts the thread.
		 */
		void start() {
			m_thread = boost::thread(&IRunnable::operator(), m_runnable);
		}

		/*
		 * Stops the thread.
		 */
		void stop() {
			m_runnable->terminate();
		}

		/*
		 * Stops and joins on the thread.
		 */
		void join() {
			stop();
			m_thread.join();
		}

	private:

		// Runnable object.  Provides thread entry point and logic.
		IRunnable* m_runnable;

		// Thread object.  Today, it is a boost thread.
		boost::thread m_thread;
	};


}



#endif /* THREAD_HH_ */
