#pragma once
//#include "IObservable.h"
#include "Utilities.h"
class IObservable;
class IObserver
{
public:
	IObserver(IObservable& subject);
	virtual ~IObserver();

	virtual void eventUpdate(sf::Event& event, Color color) = 0;

private:

	IObservable& m_subject;
};