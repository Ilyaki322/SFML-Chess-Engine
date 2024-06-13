#include "IObserver.h"

IObserver::IObserver(IObservable& subject)
	: m_subject(subject)
{
	m_subject.add(*this);
}

IObserver::~IObserver()
{
	m_subject.remove(*this);
}
