cd work4
~/work4/ $ valgrind ./u
==834== Memcheck, a memory error detector
==834== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==834== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==834== Command: ./u
==834==
word: cat:
==834== Conditional jump or move depends on uninitialised value(s)
==834==    at 0x42554D: load (u.c:297)
==834==    by 0x425A16: main (u.c:340)
==834==  Uninitialised value was created by a heap allocation
==834==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==834==    by 0x425137: load (u.c:290)
==834==    by 0x425A16: main (u.c:340)
==834==
* Count malloc: 4
lvl 0 0 w:. . c . . . . . . . . . . . . . . . . . . . . . . . .
lvl 1 0 w:a ==834== Conditional jump or move depends on uninitialised value(s)
==834==    at 0x4228FE: unload (u.c:54)
==834==    by 0x425A20: main (u.c:349)
==834==  Uninitialised value was created by a heap allocation
==834==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==834==    by 0x425137: load (u.c:290)
==834==    by 0x425A16: main (u.c:340)
==834==
. . . . . . . . . . . . . . . . . . . . . . . . . .
==834== Conditional jump or move depends on uninitialised value(s)
==834==    at 0x42264A: unload (u.c:50)
==834==    by 0x425A20: main (u.c:349)
==834==  Uninitialised value was created by a heap allocation
==834==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==834==    by 0x425137: load (u.c:290)
==834==    by 0x425A16: main (u.c:340)
==834==
lvl 2 0 w:. . . . . . . . . . . . . . . . . . . t . . . . . . .
TRUE
lvl 3 1 N:==834== Conditional jump or move depends on uninitialised value(s)
==834==    at 0x4232CE: unload (u.c:78)
==834==    by 0x425A20: main (u.c:349)
==834==  Uninitialised value was created by a heap allocation
==834==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==834==    by 0x425137: load (u.c:290)
==834==    by 0x425A16: main (u.c:340)
==834==
. . . . . . . . . . . . . . . . . . . . . . . . . . .
freed0 lvl 3 |lvl 2 0 N:. . . . . . . . . . . . . . . . . . . t . . . . . . .
freed0 lvl 2 |lvl 1 0 N:a . . . . . . . . . . . . . . . . . . . . . . . . . .
freed0 lvl 1 |lvl 0 0 N:. . c . . . . . . . . . . . . . . . . . . . . . . . .
freed0 lvl 0 |BREAK1!Word counts: 1
==834==
==834== HEAP SUMMARY:
==834==     in use at exit: 32 bytes in 1 blocks
==834==   total heap usage: 7 allocs, 6 frees, 5,576 bytes allocated
==834==
==834== LEAK SUMMARY:
==834==    definitely lost: 0 bytes in 0 blocks
==834==    indirectly lost: 0 bytes in 0 blocks
==834==      possibly lost: 0 bytes in 0 blocks
==834==    still reachable: 32 bytes in 1 blocks
==834==         suppressed: 0 bytes in 0 blocks
==834== Reachable blocks (those to which a pointer was found) are not shown.
==834== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==834==
==834== For counts of detected and suppressed errors, rerun with: -v
==834== ERROR SUMMARY: 204 errors from 4 contexts (suppressed: 0 from 0)

--------

word: cat:
* Count malloc: 4
lvl 0 0 w:. . c . . . . . . . . . . . . . . . . . . . . . . . .
lvl 1 0 w:a . . . . . . . . . . . . . . . . . . . . . . . . . .
lvl 2 0 w:. . . . . . . . . . . . . . . . . . . t . . . . . . .
TRUE
lvl 3 1 N:. . . . . . . . . . . . . . . . . . . . . . . . . . .
lvl 2 0 N:. . . . . . . . . . . . . . . . . . . t . . . . . . .
lvl 1 0 N:a . . . . . . . . . . . . . . . . . . . . . . . . . .
lvl 0 0 N:. . c . . . . . . . . . . . . . . . . . . . . . . . .
BREAK1!Word counts: 1

work4/ $ valgrind ./u > wo_free_car.txt
==504== Memcheck, a memory error detector
==504== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==504== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==504== Command: ./u
==504==
==504== Conditional jump or move depends on uninitialised value(s)
==504==    at 0x4254DD: load (u.c:297)
==504==    by 0x4259A6: main (u.c:340)
==504==  Uninitialised value was created by a heap allocation
==504==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==504==    by 0x4250C7: load (u.c:290)
==504==    by 0x4259A6: main (u.c:340)
==504==
==504== Conditional jump or move depends on uninitialised value(s)
==504==    at 0x4228BE: unload (u.c:54)
==504==    by 0x4259B0: main (u.c:349)
==504==  Uninitialised value was created by a heap allocation
==504==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==504==    by 0x4250C7: load (u.c:290)
==504==    by 0x4259A6: main (u.c:340)
==504==
==504== Conditional jump or move depends on uninitialised value(s)
==504==    at 0x42260A: unload (u.c:50)
==504==    by 0x4259B0: main (u.c:349)
==504==  Uninitialised value was created by a heap allocation
==504==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==504==    by 0x4250C7: load (u.c:290)
==504==    by 0x4259A6: main (u.c:340)
==504==
==504== Conditional jump or move depends on uninitialised value(s)
==504==    at 0x42328E: unload (u.c:78)
==504==    by 0x4259B0: main (u.c:349)
==504==  Uninitialised value was created by a heap allocation
==504==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==504==    by 0x4250C7: load (u.c:290)
==504==    by 0x4259A6: main (u.c:340)
==504==
==504==
==504== HEAP SUMMARY:
==504==     in use at exit: 928 bytes in 5 blocks
==504==   total heap usage: 7 allocs, 2 frees, 5,576 bytes allocated
==504==
==504== LEAK SUMMARY:
==504==    definitely lost: 0 bytes in 0 blocks
==504==    indirectly lost: 0 bytes in 0 blocks
==504==      possibly lost: 0 bytes in 0 blocks
==504==    still reachable: 928 bytes in 5 blocks
==504==         suppressed: 0 bytes in 0 blocks
==504== Reachable blocks (those to which a pointer was found) are not shown.
==504== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==504==
==504== For counts of detected and suppressed errors, rerun with: -v
==504== ERROR SUMMARY: 204 errors from 4 contexts (suppressed: 0 from 0)
~/work4/ $