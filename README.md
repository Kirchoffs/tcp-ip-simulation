# Notes
## Run
```
>> make
>> make test
```

## C Programming Notes
### Commands
#### Compile & Run
```
>> clang -o glue_doubly_linked_list_test glue_doubly_linked_list.c glue_doubly_linked_list_test.c
>> ./glue_doubly_linked_list_test
```


### Macro
#### Offset of Field
```c
#define OFFSET(struct_name, field_name) (size_t)&((struct_name *)0)->field_name
```

### size_t
- On 32-bit systems, `size_t` is often unsigned int or `unsigned long` (both 4 bytes).
- On 64-bit systems, `size_t` is typically `unsigned long` (8 bytes on Linux) or `unsigned long long` or `unsigned __int64` on Windows.

### __int64 and unsigned __int64
`__int64` and `unsigned __int64` is not part of standard C.

- Microsoft Visual C++ (MSVC): `__int64` and `unsigned __int64` are Microsoft extensions.
- It’s used in Windows API headers and code targeting MSVC.
- Equivalent to `long long` or `unsigned long long` in most other compilers.

## Glued Data Structures
### Doubly Linked List (DLL)
#### Traditional Way
```c
typedef struct Node_ {
    void *data;
    struct Node_ *left;
    struct Node_ *right;
} Node;

typedef struct DoublyLinkedList_ {
    Node *head;
    int (*key_match)(void *, void *);
    int (*comparison_fn)(void *, void *);
} DoublyLinkedList;
```

#### Glue Based Way
```c
typedef struct Node_ {
    struct Node_ *left;
    struct Node_ *right;
} Node;

typedef struct DoublyLinkedList_ {
    Node *head;
    int (*key_match)(void *, void *);
    int (*comparison_fn)(void *, void *);
    unsigned int offset;
} DoublyLinkedList;

#define OFFSET(struct_name, field_name) (size_t)&((struct_name *)0)->field_name
```

```c
// Application data uses the glued node to stick itself to the doubly linked list 
typedef struct AppData_ {
    char id[15];
    unsigned int ttl;
    char description[75];
    unsigned int user_id;
    Node glue;
} AppData;

void print_app_data_details(Node *glue) {
    AppData *app_data = (AppData *)((char *)glue - OFFSET(AppData, glue));
    printf("ID: %s\n", app_data->id);
    printf("TTL: %u\n", app_data->ttl);
    printf("Description: %s\n", app_data->description);
    printf("User ID: %u\n", app_data->user_id);
}

AppData *app_data = get_app_data();
print_app_data_details(&app_data->glue);

void iterate_and_print_app_data(DoublyLinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        print_app_data_details(current);
        current = current->right;
    }
}
```

## Makefile Notes
### General Simplified Makefile Structure
```makefile
CC = gcc
CFLAGS = -Wall -g

OBJS = x.o y.o z.o

x.o: x.c
    $(CC) $(CFLAGS) -c x.c -o x.o

y.o: y.c
    $(CC) $(CFLAGS) -c y.c -o y.o

z.o: z.c
    $(CC) $(CFLAGS) -c z.c -o z.o

target.o: target.c
    $(CC) $(CFLAGS) -c target.c -o target.o

target: target.o $(OBJS)
    $(CC) $(CFLAGS) -o target target.o $(OBJS)

clean:
    rm -f *.o target
```

### Miscellaneous
#### $@
- Represents the target name of the rule.

#### $^
- Represents all the prerequisites of the rule.

#### @
- Suppresses the command output when executing the rule.

#### make
If you run `make` without any arguments, it will look for a file named `Makefile` or `makefile` in the current directory and execute the first target defined in that file.
