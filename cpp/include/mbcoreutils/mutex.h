#ifndef MB_MUTEX_H_
#define MB_MUTEX_H_

#include <boost/thread.hpp>
#include "ilock.h"

namespace MakerBot {

	class Mutex : public ILock {
	public:

		Mutex() : ILock() {
		}

		virtual ~Mutex() {
		}

		virtual void acquire() {
			m_theMutex.lock();
		}

		virtual void release() {
			m_theMutex.unlock();
		}

		boost::mutex& getUnderlying() {
			return m_theMutex;
		}
	
	private:

		boost::mutex m_theMutex;
	};


}

#endif 