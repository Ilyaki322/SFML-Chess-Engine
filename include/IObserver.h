#pragma once

#include "Utilities.h"
class IObservable;


/*
* This class represents an observer object in code.
* itupdates events that have taken place
* and updates observable on adding a new observer
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