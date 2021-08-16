#include "../hpp/Player_mrx.hpp"

const tlk::Connection& tlk::Player_mrx::getSelectionForMrx(const Connections& options) 
{
    int selection;
    
    do {    
        selection = 0;
        std::cout << "From the current position you have the following options: " << std::endl;
        for (Connection c : options)
            std::cout << "[" << selection++ << "] " << c << std::endl;
        
        std::cout << "You have the Following Tickets: " << std::endl;
        std::cout << this->tickets;
        std::cout << "Please select using the number infront of the connection: " << std::endl;
        std::cout << "Selection: ";
        std::cin >> selection;

    } while(selection < 0 || selection >= options.size());

    return options[selection];
}
const tlk::Connection& tlk::Player_mrx::getSelectionForSly(const Connections& options) 
{
    throw std::runtime_error("A Player in MRXs Role shouldn't select moves like a Sly unit! wrong Method called for move selection on Player_mrx");
}

tlk::Ticket tlk::Player_mrx::getTicketForMrx(tlk::ConnectionType usedTransportation)
{
    Ticket used = TicketStack::getTicketFor(usedTransportation);

    if (tickets.ticketCount(used) == 0 
    && tickets.ticketCount(BLACK_Ti) > 0)
    {
        std::cout << "Using Black Ticket to travel as it's the only option!" << std::endl;
        return BLACK_Ti;
    }

    if (!tickets.isAdvancedTicketAvailable())
    {
        std::cout << "Using ticket for: " << used << std::endl;
        return used;
    }
        
    std::cout << "You would use a Ticked for " << used << std::endl;
    char selection = '_';

    std::cout << "Do you instead want to use: " << std::endl;
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