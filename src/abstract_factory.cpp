/* ResFactory example -- */
 
#include<iostream>
using namespace std;
 
class DisplayDriver
{
  public:
    virtual void raster() = 0;
    virtual ~DisplayDriver() { }
};
 
class LowResDispDrvr: public DisplayDriver
{
  public:
    void raster()
    {
      cout << "I'm a LowResDispDrvr\n";
    }
};
 
class HighResDispDrvr: public DisplayDriver
{
  public:
    void raster()
    {
      cout << "I'm a HighResDispDrvr\n";
    }
};

class PrintDriver
{
  public:
    virtual void print() = 0;
    virtual ~PrintDriver() { }
};

class LowResPrtDrvr: public PrintDriver
{
  public:
    void print()
    {
      cout << "I'm a LowResPrtDrvr\n";
    }
};

class HighResPrtDrvr: public PrintDriver
{
  public:
    void print()
    {
      cout << "I'm a HighResPrtDrvr\n";
    }
};

class ResFactory
{
  public:
    virtual DisplayDriver* createDispDrvr() = 0;
    virtual PrintDriver* createPrtDrvr() = 0;
    virtual ~ResFactory() { }
};
 
class LowResFact: public ResFactory
{
  public:
    DisplayDriver* createDispDrvr()
    {
      return new LowResDispDrvr();
    }

    PrintDriver* createPrtDrvr()
    {
      return new LowResPrtDrvr();
    }
 
    ~LowResFact() { }
};
 
class HighResFact: public ResFactory
{
  public:
    DisplayDriver* createDispDrvr()
    {
      return new HighResDispDrvr();
    }

    PrintDriver* createPrtDrvr()
    {
      return new HighResPrtDrvr();
    }
 
    ~HighResFact() { }
};
 
class Application
{
  public:
    Application(ResFactory* factory)
    {
      DisplayDriver* dispDriver = factory->createDispDrvr();
      PrintDriver* prtDriver = factory->createPrtDrvr();
      dispDriver->raster();
      prtDriver->print();
      delete dispDriver;
      delete prtDriver;
      delete factory;
    }
};
 
ResFactory* createCpuSpecificFactory()
{
  int sys;
  cout << endl << "Enter CPU Type(0 - Intel, 1 - AMD): ";
  cin >> sys;

  if (sys == 0) return new HighResFact();
  else return new LowResFact();
}
 
int main(int argc, char** argv)
{
  Application* newApplication = new Application(createCpuSpecificFactory());
  delete newApplication;
  return 0;
}
