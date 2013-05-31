#ifndef MB_CONDITIONVARIABLE_H_
#define MB_CONDITIONVARIABLE_H_

#include <boost/thread/condition_variable.hpp>

namespace MakerBot {

	class ConditionVariable {
	public:

		ConditionVariable() {
		}

		virtual ~ConditionVariable() {
		}

		void notifyAll() {
			m_condVar.notify_all();
		}

		void notify() {
			m_condVar.notify_one();
		}

		void wait(MakerBot::Mutex* lock) {
			lock->release();
			m_condVar.wait(boost::unique_lock<boost::mutex>(lock->getUnderlying()));
		}

	private:

		boost::condition_variable m_condVar;

	};
}
#endif