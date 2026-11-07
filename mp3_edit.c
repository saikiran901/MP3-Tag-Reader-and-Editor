#include "mp3_header.h"
#include<stdlib.h>

void edit(struct MP3 *mp3)
{
    mp3->org_mp3_fptr=fopen(mp3->mp3_filename, "rb");
    if(mp3->org_mp3_fptr == NULL)
    {
        printf("Unable to open the Original file.\n");
        return;
    }
    mp3->dup_mp3_fptr = fopen("temp.mp3", "wb");

    if(mp3->dup_mp3_fptr == NULL)
    {
        printf("Unable to create Temporary file.\n");
        fclose(mp3->org_mp3_fptr);
        return;
    }

    char header[10];
    if(fread(header, 1, 10, mp3->org_mp3_fptr)!=10)
    {
        printf("Unable to Read ID3 header.\n");
        return;
    }
    if(fwrite(header, 1, 10, mp3->dup_mp3_fptr)!=10)
    {
        printf("Unable to write ID3 header.\n");
        return;
    }

    int tag_size =0;
   
    int i;
    for(i=6; i<10; i++)
    {
         tag_size = (tag_size << 7) | (header[i] & 0x7F);
    }

 int processed_size = 0;
 int new_tag_size = 0;
 int found = 0;
    while(processed_size < tag_size)
{
 
    char tag[5];
    if(fread(tag, 1, 4, mp3->org_mp3_fptr)!=4)
    {
        return;
    }
    tag[4]='\0';

    if(tag[0]== '\0')
    {
        break;
    }
    if(fwrite(tag, 1, 4, mp3->dup_mp3_fptr)!=4)
    {
        return;
    }

    unsigned char size_bytes[4];
    unsigned char flags[2];
    
    int frame_size;
    int match =0;
    if(fread(size_bytes, 1, 4, mp3->org_mp3_fptr)!=4)
    {
        printf("Unable to read the size bytes.\n");
        return;
    }
    memcpy(&frame_size, size_bytes, 4);

    if(fread(flags, 1, 2, mp3->org_mp3_fptr)!=2)
    {
        printf("Unable to read the frame falgs.\n");
        return;
    }
    toggle_endianess(mp3, &frame_size);


    if(strcmp(mp3->edit_option, "-a") == 0 &&
   strcmp(tag, "TPE1") == 0)
   {
    match = 1;
   }

   else if(strcmp(mp3->edit_option, "-A")== 0 &&
    strcmp(tag, "TALB")==0)
    {
        match = 1;
    }
    
    else if(strcmp(mp3->edit_option, "-t")== 0 &&
    strcmp(tag, "TIT2")== 0)
    {
        match = 1;
    }

    else if(strcmp(mp3->edit_option, "-y")== 0 &&
    strcmp(tag, "TYER")== 0)
    {
        match = 1;
    }

    else if(strcmp(mp3->edit_option, "-C")== 0 &&
    strcmp(tag, "TCON")== 0)
    {
        match = 1;
    }

    else if(strcmp(mp3->edit_option, "-c")== 0 &&
    strcmp(tag, "COMM")== 0)
    {
        match = 1;
    }



   if(match == 1)
{
     if(strcmp(tag, "COMM") == 0)
    {
        unsigned char prefix[5];
 fread(prefix, 1, 5, mp3->org_mp3_fptr);
   fseek(mp3->org_mp3_fptr, frame_size - 5, SEEK_CUR);
   
    int new_size =5+strlen(mp3->new_content) ;
   
 int temp_size=new_size;
   
toggle_endianess(mp3, &temp_size);
if(fwrite(&temp_size, 1, 4, mp3->dup_mp3_fptr)!=4)
{
    printf("Unable to write the new frame size.\n");
    return;
}

if(fwrite(flags, 1, 2, mp3->dup_mp3_fptr) != 2)
{
    printf("Unable to write frame flags\n");
    return;
}
fwrite(prefix, 1, 5, mp3->dup_mp3_fptr); 
fwrite(mp3->new_content, 1, strlen(mp3->new_content), mp3->dup_mp3_fptr);

 new_tag_size += 10 + new_size;
}

     else
    {
        // Skip old frame content
        fseek(mp3->org_mp3_fptr, frame_size, SEEK_CUR);

        int new_size = strlen(mp3->new_content) + 1;

        int temp_size = new_size;

        toggle_endianess(mp3, &temp_size);

        fwrite(&temp_size, 1, 4, mp3->dup_mp3_fptr);
        fwrite(flags, 1, 2, mp3->dup_mp3_fptr);

        char encoding = 0;

        fwrite(&encoding, 1, 1, mp3->dup_mp3_fptr);

        fwrite(mp3->new_content, 1, strlen(mp3->new_content),
               mp3->dup_mp3_fptr);

        new_tag_size += 10 + new_size;
    }

    found = 1;
}

else
{
if(fwrite(size_bytes, 1, 4, mp3->dup_mp3_fptr)!=4)
    {
        printf("Unable to write the size bytes.\n");
        return;
    }
    

    if(fwrite(flags, 1, 2, mp3->dup_mp3_fptr)!=2)
    {
        printf("Unable to write the frame falgs.\n");
        return;
    }

    char *buffer= malloc(frame_size);
    if(buffer == NULL)
    {
        printf("Malloc allocation failed.\n");
        return;
    }
    if(fread(buffer, 1, frame_size, mp3->org_mp3_fptr)!= frame_size)
    {
        printf("Unable to read frame content.\n");
        free(buffer);
        return;
    }
    new_tag_size += 10 + frame_size;

    if(fwrite(buffer, 1, frame_size, mp3->dup_mp3_fptr)!= frame_size)
    {
        printf("Unable to write the frame content.\n");
        free(buffer);
        return;
    }
    free(buffer);

}
processed_size += 10 + frame_size;
}

char buffer[8192];
int bytes;
fseek(mp3->org_mp3_fptr, 10 + tag_size, SEEK_SET);
while((bytes = fread(buffer, 1, sizeof(buffer),
                     mp3->org_mp3_fptr)) > 0)
{
    fwrite(buffer, 1, bytes, mp3->dup_mp3_fptr);
}

int temp = new_tag_size;

for(int i = 9; i >= 6; i--)
{
    header[i] = temp & 0x7F;
    temp >>= 7;
}

fseek(mp3->dup_mp3_fptr, 6, SEEK_SET);

fwrite(header + 6, 1, 4, mp3->dup_mp3_fptr);

fclose(mp3->org_mp3_fptr);
fclose(mp3->dup_mp3_fptr);



if(remove(mp3->mp3_filename) != 0)
{
    printf("Unable to remove original file.\n");
    return;
}

if(rename("temp.mp3", mp3->mp3_filename) != 0)
{
    printf("Unable to rename temporary file.\n");
    return;
}

printf("MP3 tag edited successfully.\n");
printf("Now Just open your view chart.\n");

}

