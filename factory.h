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
    virtual void push(Package);
    virtual bool empty();
    virtual bool size();
    virtual Package[] view();
};

class IPackageQueue : IPackageDepot
{
    virtual void push(Package);
    virtual Package pop();
    virtual bool empty();
    virtual bool size();
    virtual Package[] view();
    virtual QueueType getQueueType();
};

class IReportNotifier
{
    virtual bool shouldGenerateReport(Time);
};

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

class PackageSender
{
    RecieverPreferences recieverPreferences;
    std::vector<Package> sendingBuffer;

public:
    void PackageSender(ElementID);
    RecieverPreferences getReceiverPreferences();
    void setReceiverPreferences(RecieverPreferences);
    void sendPackage();
    std::vector<Package> getSendingBuffer();
};
