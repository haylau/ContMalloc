#include "memory.h"


void cont_alloc(char name, int size, char algo) {
    switch (algo) {
    case FIRSTFIT: {
        falloc();
        break;
    }
    case BESTFIT: {
        balloc();
        break;
    }
    case WORSTFIT: {
        walloc();
        break;
    }
    }
}

void cont_free(char name) {

}

void show(char* memory) {
    printf("%s", memory);
}

char** readScript() {

}

void compact() {

}

int main() {

    bool running = true;
    char** commandBuffer;
    int bufLine;

    char memory[MEMSIZE];

    while (running) {
        char* cmd;
        if (commandBuffer != NULL) {
            // get line
            char** buf[BUFSIZE];
            size_t bufsize = BUFSIZE;
            ssize_t length = getline(&buf, BUFSIZE, stdin);
            if (buf[0] == NULL) continue;
            buf[0][0] = (char)toupper((char)buf[0]);
            cmd = buf;
        }
        else {
            // load from buffer
            if (commandBuffer[bufLine] != NULL) {
                cmd = commandBuffer[bufLine];
                ++bufLine;
            }
            else {
                bufLine = 0;
                continue;
            }
        }
        switch (cmd[0]) {
        case ALLOC: {

            char name, algo;
            int size;

            char* token = strtok(cmd, ' ');
            if (token == NULL) continue;
            name = tolqupper(token[0]);

            token = strtok(NULL, ' ');
            char* end;
            size = strtol(&token, &end, 10);

            token = strtok(NULL, ' ');
            if (token == NULL) continue;
            algo = toupper(token[0]);

            cont_alloc(name, size, algo);

            break;
        }
        case FREE: {

            char name;

            char* token = strtok(cmd, ' ');
            token = strtok(NULL, ' ');
            if (token == NULL) continue;
            name = toupper(token[0]);

            cont_free(name);

            break;
        }
        case SHOW: {
            show(&memory);
            break;
        }
        case READ: {
            commandBuffer = readScript();
            bufLine = 0;
            break;
        }
        case COMPACT: {
            break;
        }
        case EXIT: {
            free(commandBuffer);
            running = false;
            break;
        }
        }

    }

}