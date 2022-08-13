#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "models/message.h"
#include "models/node.h"
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

void encryptString(const char *original, char *encrypted);
bool writeMessage(Message *message, const char *filename);
Message *readMessage(const char *filename);
#endif