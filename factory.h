#include <iostream>

typedef int ElementID;
typedef int Time;
typedef int TimeOffset;

enum RecieverType {WORKER, STOREHOUSE};
enum QueueType {LIFO, FIFO};

class Package
{
    ElementID id;
    ElementID packageCounter;

public:
    Package();
    Package(ElementID);
    inline ElementID getID(void) {return id};
};

//INTERFEJSY
class IPackageReciever
{
public:
    virtual void recievePackage(Package);
    virtual Package[] viewDepot();
    virtual RecieverType getRecieverType();
    virtual ElementID getID();
};

class IPackageDepot
{
public:
    virtual void push(Package);
    virtual bool empty();
    virtual bool size();
    virtual Package[] view();
};

class IPackageQueue : IPackageDepot
{
public:
    virtual Package pop();
    virtual QueueType getQueueType();
};

class IReportNotifier
{
public:
    virtual bool shouldGenerateReport(Time);
};

// KLASY ABSTRAKCYJNE
class PackageSender
{
    RecieverPreferences recieverPreferences;
    std::vector<Package> sendingBuffer;

public:
    PackageSender(ElementID);
    RecieverPreferences getReceiverPreferences();
    void setReceiverPreferences(RecieverPreferences);
    virtual void sendPackage() = 0;
    std::vector<Package> getSendingBuffer();
};

class PackageDequeue
{
    std::deque<Package> dequeue;
public:
    void push(Package);
    Package pop(void);
    Package[] view(void);
    virtual QueueType getQueueType() = 0;
    bool isEmpty();
    bool size();
};

// KLASY
class RecieverPreferences
{
    std::map<IPackageReciever*, double> probabilities;

public:
    std::map<IPackageReciever*, double> getProbabilities();
    void setProbabilities(std::map<IPackageReciever*, double>);
    void addReciever(IPackageReciever*);
    void addRecieverWithProbability(IPackageReciever*, double);
    void removeReciever(IPackageReciever*);
    IPackageReciever* drawReciever();
    pair<IPackageReciever*, double>[] view();
};

class PackageQueueLIFO : PackageDequeue
{
public:
    QueueType getQueueType();
};

class PackageQueueFIFO : PackageDequeue
{
public:
    QueueType getQueueType();
};

class IntervalReportNotifier : IReportNotifier
{
    TimeOffset interval;
public:
    IntervalReportNotifier(TimeOffset);
    bool shouldGenerateReport();
};

class SpecififTurnsReportNotifier : IReportNotifier
{
    std::set<Time> turns;
public:
    SpecififTurnsReportNotifier(std::set<Time>);
    bool shouldGenerateReport();
};
