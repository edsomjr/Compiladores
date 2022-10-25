#ifndef BUFFER_H
#define BUFFER_H

const int N { 4 };

class IOBuffer {
public:
    static IOBuffer& getInstance();

    bool eof() const;
    int tell() const;
    void seek(int pos);

    int get();
    void unget();

private:
    IOBuffer();

    int pos, last_update;
    char buffer[2*N + 2];

    void update();
};

#endif
