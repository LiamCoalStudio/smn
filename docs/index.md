# SMN Programming Language

## Documentation

[readme.md](https://github.com/LiamCoal/smn/blob/master/readme.md)

## Downloads

[Releases Page](https://github.com/LiamCoal/smn/releases)

## Examples

_Print Line_

```
/language: cpp/#

uses simon.io;
end uses;

main;
    println "cat";
end func;
```

_Stack_

```
/language: cpp/#

uses simon;
uses simon.io;
end uses;

main;
    start_stack;
    push 'a';
    println pop();
end func;
```

_Classes_

```
/language: cpp/#

uses simon.io;
end uses;

class Printer;
    func void, print;
        println "i am printer";
    end func;
end class;

main;
    newvar Printer, printer;
    printer.print;
end func;
```

_Interfaces_

```
/language: cpp/#

uses simon.io;
end uses;

interface IPrinter;
    func print;
    func print1;
end interface;

class Printer, IPrinter;
    func print;
        print "cat = ";
    end func;

    func print1;
        println "meow";
    end func;
end class;

main;
    newvar Printer, printer;
    printer.print;
    printer.print1;
end func;
```

_Test_

```
/language: cpp/#
/test/#

main;
    assert 1 == 1, "1 is 1";
end func;
```
