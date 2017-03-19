Katerina Chinnappan
CruzID: kachinna
PA 2

README FILE

-----LIST.C-----
Creating a doubly linked list creating a List ADT.

-----LIST.H-----
Contains the prototypes for List functions

-----LISTCLIENT.C-----
Provided already, test the List ADT.

-----LEX.C-----
Client module which sorts any given input file
and outpus the sorted input into a file.

-----MAKEFILE-----
Provided already, used to compile the program into a JAR

--Valgrind - Lex --
-bash-4.2$ valgrind --leak-check=yes Lex in1 out1
==5454== Memcheck, a memory error detector
==5454== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==5454== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==5454== Command: Lex in1 out1
==5454==
==5454==
==5454== HEAP SUMMARY:
==5454==     in use at exit: 0 bytes in 0 blocks
==5454==   total heap usage: 8 allocs, 8 frees, 1,288 bytes allocated
==5454==
==5454== All heap blocks were freed -- no leaks are possible
==5454==
==5454== For counts of detected and suppressed errors, rerun with: -v
==5454== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

--Valgrind - ListClient --
-bash-4.2$ valgrind --leak-check=yes ListClient
==5889== Memcheck, a memory error detector
==5889== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==5889== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==5889== Command: ListClient
==5889==
1234567891011121314151617181920
2019181716151413121110987654321
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
12345-167891112131415-21617181920
21
0
==5889==
==5889== HEAP SUMMARY:
==5889==     in use at exit: 0 bytes in 0 blocks
==5889==   total heap usage: 65 allocs, 65 frees, 1,584 bytes allocated
==5889==
==5889== All heap blocks were freed -- no leaks are possible
==5889==
==5889== For counts of detected and suppressed errors, rerun with: -v
==5889== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
