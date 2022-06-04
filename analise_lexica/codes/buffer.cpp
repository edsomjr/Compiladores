#include <iostream>
#include "buffer.h"

using namespace std;

IOBuffer&
IOBuffer::getInstance()
{
    static IOBuffer buffer;
    return  buffer;
}

IOBuffer::IOBuffer() : pos(2*N), last_update(1)
{
    buffer[N] = buffer[2*N + 1] = EOF;
    update();
}

void IOBuffer::update()
{
    ++pos;

    if (buffer[pos] != EOF)
        return;

    if (pos == 2*N + 1)
    {
        pos = 0;

        if (last_update == 1)
        {
            auto size = fread(buffer, sizeof(char), N, stdin);
            
            if (size < N)
                buffer[size] = EOF;

            last_update = 0;
        }
    }
    else if (pos == N)
    {
        if (last_update == 0)
        {
            auto size = fread(buffer + N + 1, sizeof(char), N, stdin);

            if (size < N)
                buffer[N + 1 + size] = EOF;

            last_update = 1;
        }

        ++pos;
    }
}

bool
IOBuffer::eof() const
{
    return buffer[pos] == EOF;
}

int 
IOBuffer::tell() const
{
    return pos;
}

void
IOBuffer::seek(int p)
{
    pos = p;
}

int
IOBuffer::get()
{
    auto c = buffer[pos];
    update();

    return c;
}

void
IOBuffer::unget()
{
    --pos;

    if (pos < 0)
        pos = 2*N;
    else if (pos == N)
        --pos;
}
