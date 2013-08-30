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

class Driver
{
  protected:
    PrintDriver* printDriver;
    DisplayDriver* displayDriver;
  public:
    Driver(PrintDriver* pDrvr, DisplayDriver* dDrvr)
    {
      printDriver   = pDrvr;
      displayDriver = dDrvr;
    }
    
    void print()
    {
      printDriver->print();
    }

    void raster()
    {
      displayDriver->raster();
    }
    
    virtual ~Driver() { }
};
 
class LowResDriver: public Driver
{
  public:
    LowResDriver()
    : Driver(new LowResPrtDrvr(), new LowResDispDrvr())
    { }

    ~LowResDriver() { }
};
 
class HighResDriver: public Driver
{
  public:
    HighResDriver()
    : Driver(new HighResPrtDrvr(), new HighResDispDrvr())
    { }

    ~HighResDriver() { }
};

class Application
{
  public:
    Application(Driver* driver)
    {
      driver->print();
      driver->raster();
      delete driver;
    }
};
 
Driver* createCpuSpecificDriver()
{
  int sys;
  cout << endl << "Enter CPU Type(0: Intel, 1: AMD): ";
  cin >> sys;

  if (sys == 0) return new HighResDriver();
  else return new LowResDriver();
}
 
int main(int argc, char** argv)
{
  Application* newApplication = new Application(createCpuSpecificDriver());
  delete newApplication;
  return 0;
}
