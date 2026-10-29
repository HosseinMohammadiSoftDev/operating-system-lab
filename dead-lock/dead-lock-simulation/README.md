# Deadlock

A **Deadlock** occurs when two or more processes or threads are permanently blocked, each waiting for a resource held by another.

## Coffman Conditions

Four necessary conditions must hold simultaneously for a deadlock to occur:

### 1. Mutual Exclusion
At least one resource is non-shareable and can only be used by one process or thread at a time.

### 2. Hold and Wait
A process holds at least one resource while waiting to acquire additional resources held by other processes.

### 3. No Preemption
Resources cannot be forcibly taken from a process. They must be released voluntarily by the process holding them.

### 4. Circular Wait
A circular chain of processes exists where each process waits for a resource held by the next process in the chain.

## Example

```text
Thread 1: Holds Lock A → Waits for Lock B
Thread 2: Holds Lock B → Waits for Lock A

Result: Deadlock
```

## Deadlock Prevention

A deadlock can be prevented by ensuring that at least one of the four Coffman conditions cannot hold.

**Note:** All four conditions are necessary for deadlock. Eliminating any one of them prevents deadlock.
