#pragma once
#include <vector>
#include <queue>

template<class T>
class EventQueue
{
public:
	EventQueue();
	~EventQueue();

	std::queue<T> events;
};

template<class T>
class Event
{
	friend EventQueue<T>;
public:

	template<class... Args>
	static void Emit(Args&& ... args);

	static void Emit(T o);


	Event();
	~Event();

private:
	static std::vector<EventQueue<T>*> observers;
};

template <class T>
std::vector<EventQueue<T>*> Event<T>::observers;

#define EVENT(name) struct name : public Event<name>

template <class T>
EventQueue<T>::EventQueue()
{
	Event<T>::observers.push_back(this);
}

template <class T>
EventQueue<T>::~EventQueue()
{
	auto t = std::find(Event<T>::observers.begin(), Event<T>::observers.end(), this);
	Event<T>::observers.erase(t);
}

template <class T>
template <class ... Args>
void Event<T>::Emit(Args&&... args)
{
	for (EventQueue<T>* eq : observers )
	{
		eq->events.emplace(std::forward<Args>(args)...);
	}
}

template <class T>
void Event<T>::Emit(T o)
{
	for(EventQueue<T>* eq : observers)
	{
		eq->events.push(o);
	}
}

template <class T>
Event<T>::Event()
{
}


template<class T>
Event<T>::~Event()
{
}
