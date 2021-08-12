#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef union {
	uint32_t w;
	uint8_t b[4];
} split_4Byte_t ;

int main(int argc, char *argv[])
{
    FILE *lBinFileReadPtr = (FILE *)NULL;
    FILE *lPrivateBank0FileWritePtr = (FILE *)NULL;
    FILE *lPrivateBank1FileWritePtr = (FILE *)NULL;
    FILE *lCol0FileWritePtr = (FILE *)NULL;
    FILE *lCol1FileWritePtr = (FILE *)NULL;
    FILE *lCol2FileWritePtr = (FILE *)NULL;
    FILE *lCol3FileWritePtr = (FILE *)NULL;

    long int lBinFileSize = 0;
    long int lReadByteCount = 0;
    uint8_t lData = 0;
    uint32_t i = 0, j=0;

    uint32_t lCol0FileStartOffset = 0;
    uint32_t lCol1FileStartOffset = 0;
    uint32_t lCol2FileStartOffset = 0;
    uint32_t lCol3FileStartOffset = 0;

    uint32_t lCol0FileEndOffset = 0;
    uint32_t lCol1FileEndOffset = 0;
    uint32_t lCol2FileEndOffset = 0;
    uint32_t lCol3FileEndOffset = 0;

    split_4Byte_t l4ByteData;

    l4ByteData.w = 0;
    if(argc < 2 )
    {
        printf("Usage: bin2ilram <input.bin>\n");
    }
    else
    {
        printf("Converting %s.\n", argv[1]);

        lBinFileReadPtr = fopen(argv[1],"rb");  // r for read, b for binary
        lPrivateBank0FileWritePtr = fopen ("privateBank0.mem","w");
        lPrivateBank1FileWritePtr = fopen ("privateBank1.mem","w");
        lCol0FileWritePtr = fopen ("col0.mem","w");
        lCol1FileWritePtr = fopen ("col1.mem","w");
        lCol2FileWritePtr = fopen ("col2.mem","w");
        lCol3FileWritePtr = fopen ("col3.mem","w");

        if(  ( lBinFileReadPtr ) && ( lPrivateBank0FileWritePtr ) && ( lPrivateBank1FileWritePtr ) && ( lCol0FileWritePtr )
            && (lCol1FileWritePtr ) && (lCol2FileWritePtr) && (lCol3FileWritePtr)
        )
        {
            fseek(lBinFileReadPtr, 0, SEEK_END); // seek to end of file
            lBinFileSize = ftell(lBinFileReadPtr); // get current file pointer
            fseek(lBinFileReadPtr, 0, SEEK_SET); // seek back to beginning of file
            printf("File [%s] is of %ld bytes\n",argv[1], lBinFileSize);

            lCol0FileStartOffset = 0x00010000 + 0;
            lCol1FileStartOffset = 0x00010000 + 4;
            lCol2FileStartOffset = 0x00010000 + 8;
            lCol3FileStartOffset = 0x00010000 + 12;

            lCol0FileEndOffset = lBinFileSize - 16;
            lCol1FileEndOffset = lBinFileSize - 12;
            lCol2FileEndOffset = lBinFileSize - 8;
            lCol3FileEndOffset = lBinFileSize - 4;

            for(i=0; i<(2048/4); i++)
                fprintf(lPrivateBank0FileWritePtr,"00000000\n");

            for(i=0; i<(32768-2048);)
            {
                for(j=0; j< 4; j++ )
                {
                    fread(&lData, sizeof(lData), 1, lBinFileReadPtr);
                    lReadByteCount++;
                    l4ByteData.b[j] = lData;
                }
                i+=4;
                fprintf(lPrivateBank0FileWritePtr, "%08X\n",l4ByteData.w);
                fflush(lPrivateBank0FileWritePtr);
            }

            fseek(lBinFileReadPtr, 32768, SEEK_SET); //
            for(i=0; i<32768; )
            {
                for(j=0; j< 4; j++ )
                {
                    fread(&lData, sizeof(lData), 1, lBinFileReadPtr);
                    lReadByteCount++;
                    l4ByteData.b[j] = lData;
                }
                i+= 4;
                fprintf(lPrivateBank1FileWritePtr, "%08X\n",l4ByteData.w);
                fflush(lPrivateBank1FileWritePtr);
            }

            while( lCol0FileStartOffset <= lCol0FileEndOffset )
            {
                fseek(lBinFileReadPtr, lCol0FileStartOffset, SEEK_SET);
                for( i=0; i<4; i++ )
                {
                    fread(&lData, sizeof(lData), 1, lBinFileReadPtr);
                    lReadByteCount++;
                    l4ByteData.b[i] = lData;
                }
                fprintf(lCol0FileWritePtr, "%08X\n",l4ByteData.w);
                fflush(lCol0FileWritePtr);

                lCol0FileStartOffset += 16;
            }

            while( lCol1FileStartOffset <= lCol1FileEndOffset )
            {
                fseek(lBinFileReadPtr, lCol1FileStartOffset, SEEK_SET);
                for( i=0; i<4; i++ )
                {
                    fread(&lData, sizeof(lData), 1, lBinFileReadPtr);
                    lReadByteCount++;
                    l4ByteData.b[i] = lData;
                }
                fprintf(lCol1FileWritePtr, "%08X\n",l4ByteData.w);
                fflush(lCol1FileWritePtr);

                lCol1FileStartOffset += 16;
            }

            while( lCol2FileStartOffset <= lCol2FileEndOffset )
            {
                fseek(lBinFileReadPtr, lCol2FileStartOffset, SEEK_SET);
                for( i=0; i<4; i++ )
                {
                    fread(&lData, sizeof(lData), 1, lBinFileReadPtr);
                    lReadByteCount++;
                    l4ByteData.b[i] = lData;
                }
                fprintf(lCol2FileWritePtr, "%08X\n",l4ByteData.w);
                fflush(lCol2FileWritePtr);

                lCol2FileStartOffset += 16;
            }


            while( lCol3FileStartOffset <= lCol3FileEndOffset )
            {
                fseek(lBinFileReadPtr, lCol3FileStartOffset, SEEK_SET);
                for( i=0; i<4; i++ )
                {
                    fread(&lData, sizeof(lData), 1, lBinFileReadPtr);
                    lReadByteCount++;
                    l4ByteData.b[i] = lData;
                }
                fprintf(lCol3FileWritePtr, "%08X\n",l4ByteData.w);
                fflush(lCol3FileWritePtr);

                lCol3FileStartOffset += 16;
            }

            fclose(lBinFileReadPtr);
            fclose(lPrivateBank0FileWritePtr);
            fclose(lPrivateBank1FileWritePtr);
            fclose(lCol0FileWritePtr);
            fclose(lCol1FileWritePtr);
            fclose(lCol2FileWritePtr);
            fclose(lCol3FileWritePtr);


            printf("[DONE] Read %ld / %ld bytes \n", lReadByteCount, lBinFileSize);
        }
        else
        {
            printf("FILE access error\n");
        }
    }

    return 0;
}

