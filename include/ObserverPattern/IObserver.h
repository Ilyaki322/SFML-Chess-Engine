#pragma once
#include "Utilities.h"

class IObservable;

/*
* This class represents an observer to an observable.
* It registers itself to the observable in order to recives 
* wanted notifications from it.
*/
class IObserver
{
public:
	IObserver(IObservable& subject);
	virtual ~IObserver();

	virtual void eventUpdate(sf::Event& event, Color color) = 0;

private:

	IObservable& m_subject;
};