#ifndef __EVENT_LOOP_HPP__
#define __EVENT_LOOP_HPP__

#include <sys/poll.h>
#include <unistd.h>
#include <vector>

class EventLoop {
  public:
    static void addClient(int clientFD);
    static void removeClient(int clientIndex);

    static bool isEventSet(int index, short event);
    static void setEvent(int index, short event);

    static size_t getSize(void);
    static int getFd(int index);

  private:
    static std::vector<struct pollfd> _pollfds;

    EventLoop();
    EventLoop(const EventLoop&);
    EventLoop& operator=(const EventLoop&);
};

#endif // __EVENT_LOOP_HPP__
