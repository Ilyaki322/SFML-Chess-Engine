#pragma once
#include "IObserver.h"
#include "SFML/Graphics.hpp"

#include <vector>

class IObservable
{
public:
	IObservable() {};
	virtual ~IObservable() {};

	void add(IObserver& obs);
	void remove(IObserver& obs);

private:
	virtual void notify(sf::Event& event) = 0;

protected:

	std::vector<IObserver*> m_observers;
};