#include "ObserverPattern/IObservable.h"

void IObservable::add(IObserver& obs)
{
	m_observers.push_back(&obs);
}

void IObservable::remove(IObserver& obs)
{
	m_observers.erase(std::find(m_observers.begin(), m_observers.end(), &obs));
}
