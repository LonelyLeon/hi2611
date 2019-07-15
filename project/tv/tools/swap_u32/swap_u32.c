/** @file
* @brief ��ת32λ����, ���������׼���
*
* @author �
* @date 2013-09-03 �: �����ļ�
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    unsigned long s = 0;
    unsigned long d;

    if(argc > 1)
        s = strtoul(argv[1], NULL, 0);

    d = (s << 24) | ((s << 8) & 0x00FF0000) | ((s >> 8) & 0x0000FF00) | (s >> 24);

    fprintf(stdout, "%lu", d);

    return 0;
}
