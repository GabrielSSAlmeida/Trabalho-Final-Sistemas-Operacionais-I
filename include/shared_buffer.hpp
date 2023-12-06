#ifndef SHARED_BUFFER
#define SHARED_BUFFER

#include <semaphore.h>

template <typename T> class SharedBuffer{
    public: 
        SharedBuffer() {
            sem_init(&canRead, 0, 0);
            sem_init(&canWrite, 0, 0);
        }

        SharedBuffer(T content) {
            this->content = content;
            sem_init(&canRead, 0, 0);
            sem_init(&canWrite, 0, 0);
        }

        T read() {
            allowWrite();
            sem_wait(&canRead);
            return content;
        }

        void write(T content) {
            sem_wait(&canWrite);
            this->content = content;
            allowRead();
        }
    
    private:
        sem_t canRead;
        sem_t canWrite;
        T content;

        void allowRead() {
            sem_post(&canRead);
        }

        void allowWrite() {
            sem_post(&canWrite);
        }
};

#endif
