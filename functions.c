#include "mp3_header.h"

int validate_cla(int argc, char *argv[], struct MP3 *mp3)
{
    if( argc == 1 )
    {
	printf("------------------------------------------------------------------------------\n");
	printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
	printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
	printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
	printf("To get help pass like : ./a.out --help\n");
	printf("------------------------------------------------------------------------------\n");
	return 0;
    }

    if( (strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h")==0) || (strcmp(argv[1], "-help") == 0))
    {
	printf("------------------------------->HELP<-----------------------------------------\n");
	printf("1. -v -> to view mp3 file contents\n");
	printf("2. -e -> to edit mp3 file contents\n");
	printf("\t\t2.1. -t -> to edit song title\n");
	printf("\t\t2.2. -a -> to edit artist name\n");
	printf("\t\t2.3. -A -> to edit album name\n");
	printf("\t\t2.4. -y -> to edit year\n");
	printf("\t\t2.5. -C -> to edit content\n");
	printf("\t\t2.6. -c -> to edit comment\n");
	printf("------------------------------------------------------------------------------\n");
	return 0; 
    }

    if(!strcmp(argv[1], "-v"))
    {
	if(argc == 3)
	{
		if(strrchr(argv[2], '.') != NULL && strcmp(strrchr(argv[2], '.'), ".mp3")==0)
		{
		mp3->mp3_filename=argv[2];
		return VIEW;
		}
		else
		{
			printf("ERROE-> Invalid extension.\n");
			return 0;
		}
	}	
	
	else
	{
		printf("ERROR-> Arguments must be 3 only.\n");
		return 0;
	}
}
    

    if(!strcmp(argv[1], "-e"))
    {
	if(argc == 5)
	{
		if(strcmp(argv[2], "-t")!=0 &&
		   strcmp(argv[2], "-a")!=0 &&
		   strcmp(argv[2], "-A")!=0 &&
		   strcmp(argv[2], "-y")!=0 &&
		   strcmp(argv[2], "-C")!=0 &&
		   strcmp(argv[2], "-c")!=0)
		   {
			printf("ERROR-> Invalid editing Operation.\n");
			return 0;
		   }
	
if(strrchr(argv[4], '.') != NULL && strcmp(strrchr(argv[4], '.'), ".mp3")==0)
		{
		mp3->mp3_filename=argv[4];
		mp3->edit_option = argv[2];
		mp3->new_content = argv[3];
		return EDIT;
    	}
		else
		{
			printf("ERROR-> Invalid mp3 file extension.\n");
			return 0;
		}
	}
	else
	{
		printf("Error-> Arguments must be 5 only.\n");
		return 0;
	}
}
}
void toggle_endianess(struct MP3 *mp3, int *size)
{
	*size = ((*size & 0x000000FF) << 24) |
			((*size & 0x0000FF00) << 8)  |
			((*size & 0x00FF0000) >> 8)  |
			((*size & 0xFF000000) >> 24);

}

