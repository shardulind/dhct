bool isHashSmallerThanOrEqualTo(char h1[40], char h2[40])
{
        unsigned short int index = 0;
        while(index < 40)
        {
                if(h1[index] < h2[index])       return true;
                else if(h1[index]> h2[index])   return false;
                else if(h1[index] == h2[index])
                        index++;
        }

        return 1;
}

