#include "filehandler.h"
void encryptString(const char *original, char *encrypted)
{
    int length = strlen(original);
    for (int i = 0; i < length; i++)
    {
        char temp[5];
        sprintf(temp, "%d", (int)original[i]);
        strcat(encrypted, temp);
    }
}

bool writeMessage(Message *message, const char *filename)
{

    char dbpath[300];
    sprintf(dbpath, "../database/%s", filename);
    FILE *fp = fopen(dbpath, "wb");
    if (fp)
    {
        size_t flag = fwrite(message, sizeof(Message), 1, fp);
        fclose(fp);
        if (flag == 0)
        {
            printf("failed to write binary file");
            return false;
        }

        return true;
    }
    printf("failed to open %s ", dbpath);
    return false;
}

Message *readMessage(const char *filename)
{
    char dbpath[300];
    sprintf(dbpath, "../database/%s", filename);
    FILE *fp = fopen(dbpath, "rb");
    if (fp)
    {
        Message *message = newMessage("\0", "\0");
        size_t flag = fread(message, sizeof(Message), 1, fp);
        fclose(fp);
        if (flag == 0)
        {
            printf("failed to read binary file");
            return NULL;
        }
        return (message);
    }
    printf("failed to open %s ", dbpath);
    return NULL;
}
