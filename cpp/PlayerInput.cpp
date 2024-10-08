//
// Created by tlk on 08.10.24.
//
#include "../hpp/PlayerInput.hpp"

[[maybe_unused]] const tlk::Ticket
tlk::PlayerInput::consoleSelectTicket(const tlk::ConnectionType &type, const tlk::TicketStack &tickets)
{
    Ticket used = TicketStack::getTicketFor(type);

    if (!tickets.isAdvancedTicketAvailable())
    {
        std::cout << "Using ticket for: " << used << std::endl;
        return used;
    }

    if (tickets.ticketCount(used) == 0
        && tickets.ticketCount(BLACK_Ti) > 0)
    {
        std::cout << "Using Black Ticket to travel as it's the only option!" << std::endl;
        return BLACK_Ti;
    }

    // std::cout << "You would use a Ticked for " << used << std::endl;
    char selection = '_';

    std::cout << "Do you want to use: " << std::endl;
    if (tickets.ticketCount(tlk::DOUBLE_Ti) > 0)
        std::cout << "[d] one of " << tickets.ticketCount(tlk::DOUBLE_Ti) << " double Move tickets?" << std::endl;

    if (tickets.ticketCount(tlk::BLACK_Ti) > 0)
        std::cout << "[b] one of " << tickets.ticketCount(tlk::BLACK_Ti) << " black tickets?" << std::endl;

    std::cout << "Selection: ";
    std::cin >> selection;

    switch (selection)
    {
        case 'd':
            if (tickets.ticketCount(tlk::DOUBLE_Ti) > 0) return tlk::DOUBLE_Ti;

            std::cout << "No double tickets were available so default is used!" << std::endl;
            break;

        case 'b':
            if (tickets.ticketCount(tlk::BLACK_Ti) > 0) return tlk::BLACK_Ti;

            std::cout << "No black tickets were availabe so default is used!" << std::endl;

        default:
            std::cout << "No valid selection made, using " << used << "!" << std::endl;
            break;
    }

    return used;
}

[[maybe_unused]] const tlk::Connection &
tlk::PlayerInput::consoleSelectMoveFromOptions(const tlk::Connections &options, const tlk::TicketStack &tickets)
{
    int selection;

    do {
        selection = 0;
        std::cout << "From the current position you have the following options: " << std::endl;
        for (const Connection& c : options)
            std::cout << "[" << selection++ << "] " << c << std::endl;

        // std::cout << "You have the Following Tickets: " << std::endl;
        std::cout << tickets;
        std::cout << "Please select using the number in front of the connection" << std::endl;
        std::cout << "Selection: ";
        std::cin >> selection;

    } while(selection < 0 || selection >= options.size());

    return options[selection];
}
