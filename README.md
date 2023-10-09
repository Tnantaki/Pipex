# Pipex
**Pipex** is the program that works like a pipe `|` syntax in the command line.

### Mandatory
The program will take 4 argument to be executed as follows :
```c
./pipex file1 cmd1 cmd2 file2
```

⚠️ It must behave like this command on Shell
```c
< file1 cmd1 | cmd2 > file2 
```

### Bonus
-   Part 1 : The program must handle multiple pipes.
```c
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
⚠️ It must behave like this command on Shell
```c
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```

-   Part 2 :  Support `«` and `»`, When the first parameter is "here_doc".
```c
$> ./pipex here_doc LIMITER cmd1 cmd2 file
```
⚠️ It must behave like this command on Shell
```c
cmd << LIMITER | cmd1 >> file
```
