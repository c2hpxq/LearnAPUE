#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buffer {
    void *buf;
    size_t size;
    size_t offset;
};

int readfn(void *cookie, char *buf, int size) {
    if (size<=0)
        return 0;
    struct buffer *b = (struct buffer*) cookie;
    if (b->offset+size>b->size) 
        size = b->size - b->offset;
    b->offset += size;
    memmove(buf, b->buf, size);
    return size;
}

int max(int a, int b) {
    return a>b?a:b;
}

int writefn(void *cookie, const char *buf, int size) {
    if (size<=0)
        return 0;
    struct buffer *b = (struct buffer*) cookie;
    if (b->offset+size>b->size) {
        b->size = max(b->offset+size, b->size*2);
        b->buf = realloc(b->buf, b->size);
    }
    b->offset += size;
    memmove(b->buf, buf, size);
    return size;
}

fpos_t seekfn(void *cookie, fpos_t off, int whence) {
    struct buffer *b = (struct buffer*) cookie;
    switch (whence) {
        case SEEK_CUR:
            b->offset += off;
            break;
        case SEEK_SET:
            b->offset = off;
            break;
        case SEEK_END:
            b->offset = b->size + off;
            break;
    }
    return b->offset;
}

int closefn(void *cookie) {
    struct buffer *b = (struct buffer*) cookie;
    free(b->buf);
    free(cookie);
    return 0;
}

FILE *myfmemopen(void *restrict buf, size_t size, const char *restrict type) {
    struct buffer *fp = (struct buffer *)malloc(sizeof(struct buffer));
    if (buf==NULL)
        buf = malloc(size);
    fp->buf = buf;
    fp->size = size;
    fp->offset = 0;
    // for simplicity, ignore type now
    return funopen(fp, readfn, writefn, seekfn, closefn);
}

int main() {
    FILE *fp = myfmemopen(NULL, 100, "w+");
    fprintf(fp, "secret n=%d", 100);
    fseek(fp, 0, SEEK_SET);
    char buf[100];
    fscanf(fp, "%s", buf);
    puts(buf);
    fscanf(fp, "%s", buf);
    puts(buf);

    return 0;
}