#include "memory.h"

void cont_alloc(char* memory, char name, int size, char algo) {
    switch (algo) {
    case FIRSTFIT: {
        falloc(memory, name, size);
        break;
    }
    case BESTFIT: {
        balloc(memory, name, size);
        break;
    }
    case WORSTFIT: {
        walloc(memory, name, size);
        break;
    }
    }
}

void falloc(char* memory, char name, int size) {
    int ptr = 0;
    bool hole = false;
    for (int i = 0; i < MEMSIZE; ++i) {
        if (!hole && memory[i] == EMPTY) {
            // found beginning of hole
            hole = true;
            ptr = i;
        }
        else if (hole && memory[i] == EMPTY && (i - ptr + 1) == size) {
            // found hole that fits
            for (int j = 0; j < size; ++j) {
                memory[j + ptr] = name;
            }
            return;
        }
        else if (hole && !(memory[i] == EMPTY)) {
            // found end of hole before alloc
            hole = false;
        }
    }
}
void balloc(char* memory, char name, int size) {
    int ptr = 0;
    int best_idx = -1;
    int best_size = __INT32_MAX__;
    bool hole = false;
    for (int i = 0; i < MEMSIZE; ++i) {
        if (!hole && memory[i] == EMPTY) {
            // found beginning of hole
            hole = true;
            ptr = i;
        }
        else if (hole && (memory[i] != EMPTY || i == (MEMSIZE - 1))) {
            // found end of hole before alloc
            hole = false;
            if ((i - ptr) > size && (i - ptr) < best_size)
            {
                best_idx = ptr;
                best_size = i - ptr;
            }
        }
    }
    if (best_idx == -1) {
        printf("Out of memory exception, tried to alloc %d\n", size);
        return;
    }
    for (int j = 0; j < size; ++j) {
        memory[j + best_idx] = name;
    }
}
void walloc(char* memory, char name, int size) {

}

void cont_free(char* memory, char name) {
    for (int i = 0; i < MEMSIZE; ++i) {
        if (memory[i] == name) memory[i] = EMPTY;
    }
}

void compact() {

}

void readScript(char*** commandBuffer, int* bufSize, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    // Read lines from the file and print them
    char line[BUFSIZE];
    while (fgets(line, BUFSIZE, file) != NULL) {
        char* input = strdup(&line);
        parseLines(commandBuffer, bufSize, input);
    }

    // Close the file
    fclose(file);
}

void show(char* memory) {
    for (int i = 0; i < MEMSIZE; ++i) {
        printf("%c", memory[i]);
    }
    printf("\n");
}

void parseLines(char*** commandBuffer, int* bufSize, char* input) {
    // tokenize user cmd
    const char delim[2] = " ";
    commandBuffer[*bufSize] = (char**)malloc(BUFSIZE * sizeof(char*));
    int j = 0;
    char* token = strtok(input, delim);

    // grab rest of input tokens
    while (token != NULL) {
        // don't add tokens of ' '
        if (strcmp(token, delim) != 0) {
            int token_length = strcspn(token, "\n");
            token[token_length] = '\0';
            commandBuffer[*bufSize][j] = token;
            ++j;
        }
        // grab token
        token = strtok(NULL, delim);
    }
    ++(*(bufSize));
}

int main() {

    bool running = true;
    char*** commandBuffer = (char***)calloc(MAXCMDS, sizeof(char**));
    char** cmd;
    int bufIdx = 0;
    int bufSize = 0;
    char* memory = (char*)malloc(MEMSIZE * sizeof(char));
    for (int i = 0; i < MEMSIZE; ++i) {
        memory[i] = EMPTY;
    }

    while (running) {
        if (commandBuffer[bufIdx] == NULL) {
            // no commands in buffer; pull from stdin
            printf("mem>");
            if (bufIdx != 0) {
                // reset buffer
                free(commandBuffer);
                commandBuffer = (char***)malloc(MAXCMDS * sizeof(char**));
                bufIdx = 0;
                bufSize = 0;
            }
            // get line
            size_t len = BUFSIZE;
            ssize_t lineSize = 0; // length of string
            char* input = (char*)malloc(len);
            lineSize = getline(&input, &len, stdin);
            if (lineSize > 0) {
                (input)[lineSize - 1] = '\0';
            }
            parseLines(commandBuffer, &bufSize, input);
        }
        else {
            printf("mem>");
            int i = 0;
            while (commandBuffer[bufIdx][i] != NULL) {
                printf("%s ", commandBuffer[bufIdx][i]);
                ++i;
            }
            printf("\n");
        }
        // fetch command
        cmd = commandBuffer[bufIdx];
        switch (toupper(cmd[0][0])) {
        case ALLOC: {
            if (cmd[1] == NULL || cmd[1] == NULL || cmd[2] == NULL) {
                // invalid command
                printf("invalid command: %s %s %s %s", cmd[0], cmd[1], cmd[2], cmd[3]);
            }
            cont_alloc(memory, cmd[1][0], (int)strtol(cmd[2], NULL, 10), cmd[3][0]);
            break;
        }
        case FREE: {
            if (cmd[1] == NULL) {
                // invalid command
                printf("invalid command: %s %s", cmd[0], cmd[1]);
            }
            cont_free(memory, cmd[1][0]);
            break;
        }
        case SHOW: {
            show(memory);
            break;
        }
        case READ: {
            if (cmd[1] == NULL) {
                // invalid command
                printf("invalid command: %s %s", cmd[0], cmd[1]);
            }
            readScript(commandBuffer, &bufSize, cmd[1]);
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
        default: {
            printf("invalid command: %s", cmd[0]);
        }
        }
        ++bufIdx;
        free(cmd);
    }
}