
# Readers–Writers Problem (Readers’ Priority)

## Problem Description

The Readers–Writers problem is a classical synchronization problem concerned with controlling
concurrent access to a shared data resource. The system consists of two types of processes or
threads: **readers** and **writers**. Readers only read the shared data and do not modify it, whereas
writers modify the shared data.

In the **readers’ priority version** of the problem, the synchronization mechanism is designed
such that **readers are given preference over writers**. If one or more readers are currently
reading the shared resource, any arriving reader is allowed to start reading immediately, even if
writers are waiting. Writers are permitted to access the shared resource only when there are **no
active readers**.

## Problem Definition

Given a shared resource accessed by **multiple reader and writer** processes, design a
synchronization mechanism that allows:

1. Multiple readers to read the shared resource concurrently.
2. Writers to have exclusive access to the shared resource.
3. No reader to access the resource while a writer is writing.
4. No writer to access the resource while any reader is reading.
5. Readers to be given priority over writers, such that writers may be forced to wait as long
    as there is at least one active reader.

This version of the problem may result in **writer starvation** , which is an accepted characteristic
of readers-priority solutions.


## Constraints

```
 Multiple readers may access the shared resource simultaneously.
 Only one writer may access the shared resource at any time.
 Writers must wait if there is at least one active reader.
 Readers do not wait if other readers are active.
 Mutual exclusion must be ensured for updates to shared control variables.
```
## Input Format

```
 An integer R , representing the number of reader processes/threads.
 An integer W , representing the number of writer processes/threads.
```
## Expected Output Behavior

```
 Multiple reader processes may display reading messages concurrently.
 Writer messages must not overlap with any reader messages.
 Writers may experience indefinite waiting if readers continue to arrive.
 The shared resource must remain consistent and free from race conditions.
```
## Sample Input

### 10 10

## Sample Output

Reader 4 is reading value 0

Reader 5 is reading value 0

Reader 6 is reading value 0

Reader 7 is reading value 0

Reader 8 is reading value 0


Reader 9 is reading value 0

Reader 1 is reading value 0

Reader 3 is reading value 0

Reader 2 is reading value 0

Reader 10 is reading value 0

Writer 1 is writing value 1

Writer 2 is writing value 2

Writer 3 is writing value 3

Writer 4 is writing value 4

Writer 5 is writing value 5

Writer 6 is writing value 6

Writer 7 is writing value 7

Writer 8 is writing value 8

Writer 9 is writing value 9

Writer 10 is writing value 10



