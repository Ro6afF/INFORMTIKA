#pragma once
#include "gfw/math.hpp"

#include <chrono>

#include <SDL.h>

namespace gfw{

class Event{
	int _priority;
	public:
		void priority(int prio);
		int priority();
		bool pending();
		void cancel();

		Event(int priority=0);
		virtual ~Event();
		virtual void callback()=0;

		static int _process();
};

class Timer: Event{
	friend class Event;
	public:
		using Clock=std::chrono::steady_clock;
		static constexpr Clock::time_point never=Clock::time_point::max();
	private:
		bool _armed;
		Clock::time_point _time;
	public:
		void arm(Clock::time_point at);
		Clock::time_point time();
		void disarm();
		bool armed();

		Timer(Clock::time_point, int priority=0);
		~Timer();
};

}
