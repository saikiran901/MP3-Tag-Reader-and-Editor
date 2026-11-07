#include "mp3_header.h"

void view(struct MP3 *mp3)
{
    
 mp3->org_mp3_fptr = fopen(mp3->mp3_filename, "rb");
 if(mp3->org_mp3_fptr == NULL)
 {
    printf("Unable to open the file.\n");
    return;
 }
 char header[10];

if(fread(header, 1, 10, mp3->org_mp3_fptr) != 10)
{
    printf("Unable to read ID3 header.\n");
    fclose(mp3->org_mp3_fptr);
    return;
}

int tag_size = 0;

for(int i = 6; i < 10; i++)
{
    tag_size = (tag_size << 7) | (header[i] & 0x7F);
}
 printf("----------------------------------------------------------------\n");
    printf("              MP3 Tag Reader ID3v2 View           \n");
     printf("----------------------------------------------------------------\n");
int processed_size = 0;    
while(processed_size < tag_size)
{
 char tag[5];
     if(fread(tag, 1, 4, mp3->org_mp3_fptr)!=4)
      {
         break;
      }
        tag[4]= '\0';
        if(tag[0]=='\0')
        {
            break;
        }

        int frame_size;
        if(fread(&frame_size, 1, 4, mp3->org_mp3_fptr)!=4)
        {
            break;
        }
        toggle_endianess(mp3, &frame_size);



// Skip 2 bytes of frame flags
fseek(mp3->org_mp3_fptr, 2, SEEK_CUR);
 
// Identify frame ID
   if(strcmp(tag, "APIC") == 0)
{
    fseek(mp3->org_mp3_fptr, frame_size, SEEK_CUR);

    processed_size += 10 + frame_size;

    continue;
}

tag_to_name(tag);
printf(" : ");

if(strcmp(tag, "COMM") == 0)
{
    fseek(mp3->org_mp3_fptr, 5, SEEK_CUR);

    int comment_size = frame_size - 5;

    char comment[comment_size + 1];

    fread(comment, 1, comment_size, mp3->org_mp3_fptr);

    comment[comment_size] = '\0';

    printf("%s", comment);
}
else
{
    print_tag_data(mp3->org_mp3_fptr, frame_size);
}

// Read and print frame content
//print_tag_data(mp3->org_mp3_fptr, frame_size);

printf("\n");
processed_size += 10 + frame_size;
    
}
printf("----------------------------------------------------------------\n");
    fclose(mp3->org_mp3_fptr);
   
}

    


void tag_to_name(char *tag)
{
    
    if(strcmp(tag, "TPE1")== 0)
    {
        printf("Artist");
    }
    else if(strcmp(tag, "TALB")==0)
    {
        printf("Album");
    }
    else if(strcmp(tag, "TIT2")==0)
    {
        printf("Title");
    }
    else if(strcmp(tag, "TYER")==0)
    {
        printf("Year");
    }
    else if(strcmp(tag, "TCON")==0)
    {
        printf("Content type");
    }
    else if(strcmp(tag, "COMM")==0)
    {
        printf("Comments");
    }
    else if(strcmp(tag, "APIC") == 0)
   {
         printf("Album Art");
   }
    else
    {
        printf("Unknown tag");
    }
    
}

 void print_tag_data(FILE *org_mp3_fptr, int size)
{
    if(size <= 1)
    return;
    char encoding;
    fread(&encoding, 1, 1, org_mp3_fptr);
    char content[size];
    fread(content, 1, size-1, org_mp3_fptr);
    content[size-1]='\0';
    printf("%s\n",content);

   
}
