#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int vspace_mb, page_kb;
    unsigned int virtual_address;
    unsigned int virtual_space_bytes;
    unsigned int page_size_bytes;
    unsigned int num_pages;
    unsigned int page_number, offset;
    unsigned int *page_table;

    if (argc != 4)
    {
        printf("Usage: %s <VirtualSpace_MB> <PageSize_KB> <VirtualAddress>\n", argv[0]);
        return 1;
    }

    vspace_mb = atoi(argv[1]);
    page_kb = atoi(argv[2]);
    virtual_address = atoi(argv[3]);

    virtual_space_bytes = vspace_mb * 1024 * 1024;
    page_size_bytes = page_kb * 1024;

    if (virtual_address >= virtual_space_bytes)
    {
        printf("Invalid Virtual Address\n");
        return 1;
    }

    num_pages = virtual_space_bytes / page_size_bytes;

    page_table = (unsigned int *)malloc(num_pages * sizeof(unsigned int));

    for (unsigned int i = 0; i < num_pages; i++)
        page_table[i] = i;   // Identity mapping

    page_number = virtual_address / page_size_bytes;
    offset = virtual_address % page_size_bytes;

    if (page_number >= num_pages)
    {
        printf("Page Table Miss!\n");
    }
    else
    {
        printf("Physical Address = <%u, %u>\n",
               page_table[page_number], offset);
    }

    free(page_table);
    return 0;
}
