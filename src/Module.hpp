class Module {
public:
    virtual void run() = 0;
};

class LogModule: public Module {
private:
    double * x;
public:
    LogModule();
    LogModule(double x);
    ~LogModule();

    void run();
};
