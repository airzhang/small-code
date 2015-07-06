#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//the type of operation
enum operation_type{
        STR_CMP,
        STR_ADD,
        STR_SUB,
        NUM_CMP, 
        NUM_ADD,
        NUM_SUB
};


/**
 **Function name: str_cmp 
 **Description  : compare two string, and print the D-value of two string
 **Input        : two string 
 **        
 **Return Value : 0 if success
 **Revision Date: 2015/05/07
 **/
int str_cmp (const char* str1, const char* str2)
{
        if ((NULL == str1) || (NULL == str2))
        {
                printf ("The String You Input is Empty !!\n");
                goto OUT;
        }

        while (*str1 == *str2)
        {
                if ('\0' == *str1)
                {
                        goto OUT;
                }
                str1++;
                str2++;
        }

        printf("%d\n", (*str1 - *str2));

OUT:
        return 0;
}
  

/**
 **Function name: str_add 
 **Description  : add a string to the end of another and print it  
 **Input        : two string 
 **        
 **Return Value : 0 if success
 **Revision Date: 2015/05/07
 **/
int str_add (const char* str1, const char* str2) 
{
        //malloc a space for the add result
        char *add_result = (char *) malloc (strlen(str1) + strlen(str2) + 1);
        if (add_result == NULL)
        {
                printf ("Malloc Failed !!!!\n");   
                goto OUT;
        }
        char *head_tmp = add_result;

        if ((NULL == str1) || (NULL == str2))
        {
                printf ("The String You Input is Empty !!\n");
                goto OUT;
        }

        //move the position to the end of str1
        while ('\0' != *str1)
        {
               *head_tmp++ = *str1++; 
        }

        //add str2 to the end of str1
        while ('\0' != (*head_tmp++ = *str2++))
        {
                ;
        }

        printf ("%s\n", add_result);

OUT:
        free (add_result);
        return 0;
}
#if 0
int str_sub (const char* str1, const char* str2)
{
        char* sub_result = (char*) malloc (strlen(str1) - strlen(str2) + 1);
        int ret = 0;

        if (sub_result == NULL)
        {
                printf ("Malloc Failed !!!!\n");   
                ret = 1;
        }
        char* head_tmp = sub_result;
        const char *head_str2 = str2;

        if ((NULL == str1) || (NULL == str2))
        {
                printf ("The String You Input is Empty !!\n");
                goto OUT;
        }

        while ('\0' != *str1)
        {
                str2 = head_str2;
                while ('\0' != *str2)        
                {
                        if (*str1 == *str2)               
                        {
                                break; 
                        }
                        if ('\0' != *(str2 + 1))
                        {
                                *head_tmp++ = *str1;
                                break;
                        }
                        str2++;
                }
                str1++;
        }

        printf ("%s\n", sub_result);

OUT:
        free (sub_result);
        return ret;
}
#endif


/**
 **Function name: str_sub 
 **Description  : delete a string from another, and print it after delelte
 **Input        : two string 
 **        
 **Return Value : 0 if success
 **Revision Date: 2015/05/07
 **/
int str_sub (const char* str1, const char* str2)
{
        int str1_len = strlen(str1);
        int str2_len = strlen(str2);

        //malloc space for sub result
        char* sub_result = (char*) malloc (str1_len > str2_len ? str1_len : str2_len);
        int pos_str1 = 0;           //the index of str1
        int pos_str2 = 0;           //the index of str2
        int pos_result = 0;         //the index of sub_result
        int content_str1;           //the temp value to stroe the content of str1
        
        if (sub_result == NULL)
        {
                printf ("Malloc Failed !!!!\n");   
                goto OUT;
        }
        if ((NULL == str1) || (NULL == str2))
        {
                printf ("The String You Input is Empty !!\n");
                goto OUT;
        }

        while (*(str1 + pos_str1) != '\0')
        {
                content_str1 = *(str1 + pos_str1);

                if (content_str1 == *(str2 + pos_str2))
                {
                        *(sub_result + pos_result) = content_str1;
                        pos_result++;

                        //before move to the end of str2
                        if (pos_str2 < str2_len - 1)
                        {
                                pos_str2++;
                        }

                        //when move to the end of str2
                        else if (pos_str2 = str2_len - 1)
                        {
                                pos_str2 = 0;
                                //all of the str2 is same with the part of str1
                                //move the position to before and throw the same string
                                pos_result -= str2_len;
                        }
                }
                else
                {
                        *(sub_result + pos_result) = content_str1;
                        pos_result++;
                }
                pos_str1++;
        }
        
        printf ("%s\n", sub_result);

OUT:
        free(sub_result);
        return 0;
}


/**
 **Function name: num_cmp 
 **Description  : compare two number and print the larger one
 **Input        : two double number 
 **        
 **Return Value : 0 if success
 **Revision Date: 2015/05/07
 **/
int num_cmp (const double str1, const double str2)
{
        printf ("%f\n", str1 > str2 ? str1 : str2);
        return 0;
}


/**
 **Function name: num_add 
 **Description  : add two number and print the result
 **Input        : two number 
 **        
 **Return Value : 0 if success
 **Revision Date: 2015/05/07
 **/
int num_add (const double str1, const double str2)
{
        printf ("%f\n", str1 + str2);
        return 0;
}


/**
 **Function name: num_sub 
 **Description  : subtract two num and print the result which is positive number
 **Input        : two number 
 **        
 **Return Value : 0 if success
 **Revision Date: 2015/05/07
 **/
int num_sub (const double str1, const double str2)
{
        if (str2 > str1)
        {
                printf ("%f\n", str2 - str1);
        }
        else
        {
                printf ("%f\n", str1 - str2);       
        }
        return 0;
}


/**
 **Function name: check_type 
 **Description  : check the input string and judge the string is number or string,
 **               then judge which kind of operation was input
 **Input        : three string, one of them is an operation 
 **        
 **Return Value : 0 if success
 **Revision Date: 2015/05/07
 **/
int check_type (const char* str1, const char* str2, const char* type)
{
        int type_num = 99;

        //invert the string to float num
        double str1_to_i = atof(str1);
        double str2_to_i = atof(str2);

        char i_to_str1[100] = {0};
        char i_to_str2[100] = {0};

        if ((NULL == str1) || (NULL == str2))
        {
                printf ("The String You Input is Empty !!\n");
                goto OUT;
        }

        //invert the float num back to string
        gcvt(str1_to_i, strlen(str1), i_to_str1);
        gcvt(str2_to_i, strlen(str2), i_to_str2);

        //the new string will equl with the input if it's number
        if (0 == strcmp(str1, i_to_str1))
        {
                if (0 == strcmp(type, "cmp"))
                {
                        type_num = NUM_CMP;
                }
                else if (0 == strcmp(type, "+"))
                {
                        type_num = NUM_ADD;
                }
                else if (0 == strcmp(type, "-"))
                {
                        type_num = NUM_SUB;
                }
                else
                {
                        printf("Wrong Operation Type !! \n");
                        type_num = -1;
                }
        }
        else
        {
                if (0 == strcmp(type, "cmp"))
                {
                        type_num = STR_CMP;
                }
                else if (0 == strcmp(type, "+"))
                {
                        type_num = STR_ADD;        
                }
                else if (0 == strcmp(type, "-"))
                {
                        type_num = STR_SUB;
                }
                else
                {
                        printf("Wrong Operation Type !! \n");
                        type_num = -1;
                }
        }

OUT:
        return type_num;
}


/**
 **Function     : caculate the input string according the specific operation 
 **        
 **Return Value : 0 if success
 **Revision Date: 2015/05/07
 **/
int main ()
{
        char input_1[100] = {0};
        char input_2[100] = {0};        
        char operation[5] = {0};
        int check_result;

//        while (1)
        {
                printf ("\n");
                printf ("STRING 1 :  "); 
                gets (input_1);
                printf ("STRING 2 :  "); 
                gets (input_2);
                printf ("OPERATION:  ");
                gets (operation);
                
                check_result = check_type(input_1, input_2, operation);
                switch (check_result)
                {
                        case STR_CMP:
                                str_cmp(input_1, input_2);
                                break;
                        case STR_ADD:
                                str_add(input_1, input_2);
                                break;
                        case STR_SUB:
                                str_sub(input_1, input_2);
                                break;
                        case NUM_CMP:
                                num_cmp(atof(input_1), atof(input_2));
                                break;
                        case NUM_ADD:
                                num_add(atof(input_1), atof(input_2));
                                break;
                        case NUM_SUB:
                                num_sub(atof(input_1), atof(input_2));
                                break;
                        case -1:
                                break;
                }
        }

        return 0;
}
