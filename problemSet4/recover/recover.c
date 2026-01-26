#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

bool is_file_header(uint8_t buffer[BLOCK_SIZE])
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            ((buffer[3] & 0xf0) == 0xe0));
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        return 1;
    }

    char filename[9];
    uint8_t buffer[BLOCK_SIZE];
    int image_no = 0;
    FILE *imageFile = NULL;
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        if (is_file_header(buffer))
        {
            if (imageFile != NULL)
                fclose(imageFile);

            sprintf(filename, "%03i.jpg", image_no++);
            imageFile = fopen(filename, "w");
            if (imageFile == NULL)
            {
                fclose(card);
                return 1;
            }
        }
        if (imageFile != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, imageFile);
        }
    }

    if (imageFile != NULL)
        fclose(imageFile);

    fclose(card);
    return 0;
}
