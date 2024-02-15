
class Block {

    public:
        static const float vertices[];
        static const unsigned int indices[];

        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        void render(unsigned int program);

        Block();
        ~Block();
};


