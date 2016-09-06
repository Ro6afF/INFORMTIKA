#include "gfw/event.hpp"
#include <set>
#include <queue>
#include <stdexcept>
#include <iostream>

namespace gfw{

namespace{
	struct PrioCmp{
		GFW__INLINE bool operator()(Event *a, Event *b) const noexcept{
			if(a->priority()!=b->priority()) return a->priority()<b->priority();
			return a<b;
		}
	};
	struct TimerCmp{
		GFW__INLINE bool operator()(Timer *a, Timer *b) const noexcept{
			if(a->time()!=b->time()) return a->time()<b->time();
			return a<b;
		}
	};
}

constexpr Timer::Clock::time_point Timer::never;
static std::set<Event*, PrioCmp> events_pending;
static std::set<Timer*, TimerCmp> timers;

void Event::priority(int prio){
	bool pending=events_pending.erase(this);
	_priority=prio;
	if(pending) events_pending.insert(this);
}
int Event::priority(){
	return _priority;
}
Event::Event(int prio):_priority(prio){}
Event::~Event(){
	cancel();
}
void Event::cancel(){
	events_pending.erase(this);
}
bool Event::pending(){
	return events_pending.count(this);
}

Timer::Timer(Clock::time_point at, int prio):Event(prio),_armed(false),_time(never){
	arm(at);
}
Timer::~Timer(){
	disarm();
}
void Timer::arm(Clock::time_point at){
	disarm();
	_time=at;
	if(at!=never){
		timers.insert(this);
		_armed=true;
	}
}
void Timer::disarm(){
	if(_armed){
		_armed=false;
		if(!timers.erase(this)){
			cancel();
		}
	}
}
bool Timer::armed(){
	return _armed;
}
Timer::Clock::time_point Timer::time(){
	return _time;
}

int Event::_process(){
	auto now=Timer::Clock::now();
	while(!timers.empty()){
		auto it=timers.begin();
		if((*it)->time() > now){
			break;
		}
		events_pending.insert(*it);
		timers.erase(it);
	}

	if(!events_pending.empty()){
		auto it=events_pending.begin();
		auto ev=*it;
		events_pending.erase(it);
		ev->callback();
		if(!events_pending.empty()) return 0;
	}

	int maxr=1000;
	if(timers.empty()) return maxr;
	auto r=std::chrono::duration_cast<std::chrono::nanoseconds>((*timers.begin())->time()-Timer::Clock::now()).count();
	if(r<0) r=0;
	r/=1000000;
	r++;
	if(r>maxr) r=maxr;
	return r;
}

}
