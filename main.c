#include <stdio.h>
#include <stdlib.h>

int length = 4, width = 2;

struct LandData
{
    int typeofland;
    float numofvisits;
    int height;
    int trail;
};

struct LandData* WriteNewData()
{
    int i, j;
    FILE *land;

    struct LandData *arr = (struct LandData*)malloc(length* width* sizeof(struct LandData));

        if((land = fopen("file.bin", "wb")) == NULL)
        {
        printf("Unable to open file!\n");
        exit(1);
        }else printf("Opened file successfully.\n");

        for (i = 0; i < length ; i++){
            for (j = 0; j < width; j++){
                printf("choose 0-plant, 1 -land, 2 - water, 3 - road, 4 - building: ");
                scanf("%d", &(arr + i*width + j)->typeofland);
                printf("choose height: ");
                scanf("%d",&(arr + i*width + j)->height);
                printf("visits per day: ");
                scanf("%f", &(arr + i*width + j)->numofvisits);
            }
        }
        fwrite(arr, sizeof(struct LandData), length*width, land);
        if(fclose(land)!=0)
        {
            perror("Error on file closing after writing");
            exit(2);
        }

    return (arr);
}

struct LandData* WriteRandomData()
{
    int i, j;
    FILE *land;

    struct LandData *arr = (struct LandData*)malloc(length* width* sizeof(struct LandData));

            if((land = fopen("file.bin", "wb")) == NULL)
            {
                printf("Unable to open file!\n");
                exit(1);
            }else printf("Opened file successfully.\n");
            for (i = 0; i < length ; i++){
                for (j = 0; j < width; j++){
                ((arr + i*width + j)->height) = rand() % 10;
                ((arr + i*width + j)->typeofland) = rand() % 5;
                ((arr + i*width + j)->numofvisits)= ((float)rand()/RAND_MAX)*(float)(20.0);
                }
            }
        fwrite(arr, sizeof(struct LandData), length*width, land);
        if(fclose(land)!=0)
        {
            perror("Error on file closing after writing");
            exit(2);
        }

    return (arr);
}


struct LandData* CheckFile()
{
    int op;
    FILE *land;

    struct LandData *arr = (struct LandData*)malloc(length* width* sizeof(struct LandData));

    if((land=fopen("file.bin","rb+"))==NULL)
    {
        perror("Can't open File");
        exit(1);
    }

    if((fread(arr,sizeof(struct LandData),1,land))!= 1)
    {
        printf("Error file is empty!\nPlease choose 1 to enter new data or  2 to reproduce random data:");
        scanf("%d", &op);
        switch(op)
        {
        case 1: WriteNewData(arr); break;
        case 2:WriteRandomData(arr); break;
        }
    }
    else
    {
        printf("press 1 to read data in the file press 2 to create new data press 3 to randomize data: ");
        scanf("%d", &op);
        switch(op)
        {
        case 1: break;
        case 2:WriteNewData(arr); break;
        case 3:WriteRandomData(arr); break;
        }
    }
    return(arr);
}


void DisplayingMap(struct LandData *arr)
{
    FILE* land;

    if((land=fopen("file.bin","rb"))==NULL)
    {
        perror("Can't open File");
        exit(1);
    }

    fread(arr, sizeof(struct LandData), length*width, land);

    printf("\n     ");
    for (int i=0 ; i<width; i++)
    printf("%d| ", i);
    printf("\n");

    for (int i = 0; i < length ; i++) {
    printf(" %d| ", i);
    for (int j = 0; j < width; j++)
    printf(" %d ", (arr + i*width + j)->height);
    printf("\n");
    }

    if(fclose(land)!=0)
    {
        perror("Error on file closing after reading");
        exit(2);
    }
}

void DisplayType(struct LandData *arr)
{
    int altlength, altwidth, op;
    FILE* land;

    if((land=fopen("file.bin","rb"))==NULL)
    {
        perror("Can't open File");
        exit(1);
    }

    fread(arr, sizeof(struct LandData), length*width, land);


        printf("\n1.Display Map with types\n2.Display specific type \n3.Display all types\nChoose operation: ");
        scanf("%d",&op);
        switch(op){

        case 1:
            printf("\n     ");
            for (int i=0 ; i<width; i++)
            printf("%d| ", i);
            printf("\n");
            for (int i = 0; i < length ; i++) {
            printf(" %d| ", i);
            for (int j = 0; j < width; j++)
            printf(" %d ", (arr + i*width + j)->typeofland);
            printf("\n");
            }break;
        case 2:
            printf("Choose altitude to display type:\n");
            scanf("%d %d", &altlength, &altwidth);
            if(((arr+ altlength*width +altwidth)->typeofland)==0)
            printf("PLANT");
            else if(((arr+ altlength*width +altwidth)->typeofland)==1)
            printf("WASTELAND");
            else if(((arr+ altlength*width +altwidth)->typeofland)==2)
            printf("WATER");
            else if(((arr+ altlength*width +altwidth)->typeofland)==3)
            printf("ROAD");
            else if(((arr+ altlength*width +altwidth)->typeofland)==4)
            printf("BUILDING");
            else printf("Error no such altitudes");
            break;
        case 3:
            for (int i = 0; i < length ; i++){
                for (int j = 0; j < width; j++){
                    printf("For altitudes %d %d = ", i, j);
                    if(((arr + i*width + j)->typeofland)==0)
                    printf("PLANT\n");
                    else if(((arr + i*width + j)->typeofland)==1)
                    printf("LAND\n");
                    else if(((arr + i*width + j)->typeofland)==2)
                    printf("WATER\n");
                    else if(((arr + i*width + j)->typeofland)==3)
                    printf("ROAD\n");
                    else if(((arr + i*width + j)->typeofland)==4)
                    printf("BUILDING\n");
                    }
                }
        default:printf("No such operation\n");
        }
    if(fclose(land)!=0)
    {
        perror("Error on file closing after reading");
        exit(2);
    }

}

void Pathway(struct LandData *arr)
{
    int op, y;
    int altlength, altwidth, prevl, prevw, startl, startw;
    FILE* land;

    if((land=fopen("file.bin","wb+"))==NULL)
    {
        perror("Can't open File");
        exit(1);
    }


    do
    {
        printf("1 for continue -1 to exit\n");
        scanf("%d", &op);
        switch(op){
        case 1:
        if(y!=1){
            printf("Choose starting point: ");
            scanf("%d %d", &startl,&startw);
            if(((arr+ startl*width +startw)->typeofland)==2){
            printf("Error cant walk on water!\n");break;}
            else if(((arr+ startl*width +startw)->typeofland)==4){
            printf("Error cant walk on building!\n");break;}
            else if(startl > length || startw > width){
            printf("Error choose valid altitudes!\n");break;}
            else{
            (arr+ startl*width +startw)->trail = 3;
            (arr+ startl*width +startw)->typeofland = 3;

            prevl = startl;
            prevw = startw;
            y = 1;
            }
            fwrite(arr, sizeof(struct LandData), length*width, land);

            if(fclose(land)!=0)
            {
                perror("Error on file closing after reading");
                exit(2);
            }
        }
        else{
        if((land=fopen("file.bin","wb+"))==NULL)
        {
        perror("Can't open File");
        exit(1);
        }

        printf("Choose altitudes: ");
        scanf("%d %d", &altlength,&altwidth);
                if(((arr+ altlength*width +altwidth)->typeofland)==2){
                printf("Error cant walk on water!\n");
                break;}
                else if(((arr+ altlength*width +altwidth)->typeofland)==4){
                printf("Error cant walk on building!\n");
                break;}
                else if(altlength > length || altwidth > width){
                printf("Error choose valid altitudes!\n");
                break;}
                else if((altlength > prevl+1 || altwidth > prevw+1)||(altlength < prevl-1 || altwidth < prevw-1)){
                printf("Error can't skip steps!\n");
                break;}
                else
                {
                    (arr+ altlength*width +altwidth)->trail = 3;
                    (arr+ altlength*width +altwidth)->typeofland = 3;
                    prevl = altlength;
                    prevw = altwidth;
                }
                fwrite(arr, sizeof(struct LandData), length*width, land);
                if(fclose(land)!=0)
                {
                    perror("Error on file closing after reading");
                    exit(2);
                }
       }
        break;
        case -1:
        for (int i = 0; i < length ; i++) {
            for (int j = 0; j < width; j++){
                if (((arr + i*width + j)->trail)!=3)
                (arr + i*width + j)->trail = 0;
                else continue;
            }
        }
        printf("Built Path:\n     ");

        for (int i=0 ; i<width; i++)
        printf("%d| ", i);
        printf("\n");

        for (int i = 0; i < length ; i++)
        {
            printf(" %d| ", i);
            for (int j = 0; j < width; j++)
            printf(" %d ", (arr + i*width + j)->trail);
            printf("\n");
        }break;
        default:printf("No such operation\n");
    }
    }while (op!=-1);


}

void Jumps(struct LandData *arr)
{
    int column = 4;
    int sum;

    for (int i = 0; i <= length - column; i++) {
        for (int j = 0; j < width; j++)
        {
            sum = 0;
            for(int next = 0; next < column; next++)
            sum += (((arr+ i*width +j)->typeofland)==1);
            if(sum == 4)
            {
                printf("suitable coordinates: %d %d \n",  i ,j);
            }
        }
    }

}

int main() {
    FILE *fptr;

    if((fptr = fopen("measurments.bin", "wb")) == NULL)
    {
        printf("Unable to open file!\n");
        exit(1);
    }
    fwrite(&length,sizeof(int),1,fptr);
    fwrite(&width,sizeof(int),1,fptr);

    fclose(fptr);

    struct LandData *arr =CheckFile();
    int op;
    do
    {
        printf("\nMenu:\n1.Display of map\n2. Display of type \n3.Build a path \n4.Jumps\n5.Exit\nChoose operation:");
        scanf("%d",&op);
        switch(op)
        {
            case 1:DisplayingMap(arr);break;
            case 2:DisplayType(arr);break;
            case 3:Pathway(arr);break;
            case 4:Jumps(arr);break;
            case 5:printf("Goodbye!\n");break;
            default:printf("No such operation\n");
        }
    }while(op!=5);

   free(arr);
   return 0;
}
