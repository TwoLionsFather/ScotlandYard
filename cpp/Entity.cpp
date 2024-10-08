//
// Created by tlk on 08.10.24.
//
#include "../hpp/Entity.hpp"

double tlk::Entity::scoreCon(const Connection &c)
{
    std::cout << "Entity::scoreCon: scoring " << c << " with random score" << std::endl;
    return ((double) random())/rand();
}

const tlk::Move tlk::Entity::move(const tlk::Connections &options)
{
    if (tlk::LOG_LEVEL >= tlk::HIGH)
        std::cout << "Entity::move getSelection" << std::endl;

    tlk::Move pair(getSelection(options), tlk::NO_TICKET);

    if (tlk::LOG_LEVEL >= tlk::HIGH)
        std::cout << "Entity::move getTicket" << std::endl;

    pair.second = getTicket(pair.first.type);
    tickets.useTicket(pair.second);
    return pair;
}

void tlk::Entity::addTicket(const tlk::Ticket &type)
{
    if (isMrx())
        tickets.addTicket(type);
}

bool tlk::Entity::isMrx() const
{
    return team == tlk::MRX;
}

bool tlk::Entity::hasTicketFor(tlk::ConnectionType type) const
{
    return tickets.hasTicketFor(type);
}

const tlk::Connection &tlk::Entity::getHighestScoring(const tlk::Connections &options)
{
    if (tlk::LOG_LEVEL >= tlk::HIGH)
        std::cout << "Moving Entity::getHighestScoring init with connection " << options[0] << std::endl;


    const Connection* best = &options[0];

    if (tlk::LOG_LEVEL >= tlk::HIGH)
        std::cout << "Moving Entity::getHighestScoring scoring connection " << *best << std::endl;

    double highScore = scoreCon(*best);

    for (const Connection& con : options)
    {
        double score = scoreCon(con);
        if (highScore < score)
        {
            best = &con;
            highScore = score;
        }
    }

    return *best;
}

tlk::Entity::Entity(tlk::Team t): team(t), tickets(TicketStack(t == tlk::MRX)) { }

tlk::Entity::Entity(tlk::Team t, tlk::TicketStack tickets): team(t), tickets(tickets) { }

tlk::Entity::~Entity() { }

tlk::Entity::Entity() : team(tlk::SLY), tickets(TicketStack(false)) { }

tlk::Ticket tlk::Entity::getTicket(tlk::ConnectionType usedTransportation)  {
    return TicketStack::getTicketFor(usedTransportation);
}

const tlk::Connection &tlk::Entity::getSelection(const tlk::Connections &options) {
    return getHighestScoring(options);
}
