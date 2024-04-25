
#ifndef _INPUT
#define _INPUT

class Input {
    private:
    public:
        bool keys[255] = { 0 };

        void press(unsigned int key);
        void release(unsigned int key);
};

#endif
