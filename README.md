# Tiny Tracer

A simple application using **ptrace(2)** to capture the stderr of a process.

## How to use it

### Compilation

```sh
gcc -o tiny-tracer.out ./src/tracer.c
```

### Running an example

```sh
python tracee/asd.py & #This would output a PID
./tiny-tracer <pid_of_asd.py>
```

## References

[My seminal question on StackOverflow](http://stackoverflow.com/43854398/read-the-stderr-of-a-process-using-ptrace2)
